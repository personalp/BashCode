#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

#include <sys/types.h>

       int main()
       {
           FILE *stream;
           char *line = NULL;
           size_t len = 0;
           ssize_t nread;
	char* word;
	const char delimiter[2] = ";";	

	// read data from the file bashCommmands.txt and store in stream
           stream = fopen ("bashCommands.txt", "r");
	// if stream is null, can't open the file exit
           if (stream == NULL) {
               perror("fopen");
               exit(0);
           }
		
    while ((nread = getline(&line, &len, stream)) != -1) {
	              printf("Retrieved line of length %zu:\n", nread);
	            printf("the line read is:%s", line);

			
			fwrite(line, nread, 1, stdout);

			int i=0, j=0;
			//divide a string by a delimiter and read it while the line is not empty

			pid_t cpid,w;
			int status;
	                
			// fork() and execute each command in the child's process

				cpid = fork();
			if(cpid<0){

				printf("ERROR forking, child process failed");
			}
			
				if(cpid == 0){

					word= strtok(line,delimiter);
					while(word!=NULL){
							
						printf("the word read is:%s",word);
						
						word= strtok(NULL,delimiter);
						
						execv("/home/larissaba/Documents/SummerBashCode",word);
						//exit(0);

					}

				}else{
				
				        do {
		                   w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
		                   if (w == -1) {
		                       perror("waitpid");
		                       exit(0);
		                   }

		                   if (WIFEXITED(status)) {
		                       printf("exited, status=%d\n", WEXITSTATUS(status));
		                   } else if (WIFSIGNALED(status)) {
		                       printf("killed by signal %d\n", WTERMSIG(status));
		                   } else if (WIFSTOPPED(status)) {
		                       printf("stopped by signal %d\n", WSTOPSIG(status));
		                   } else if (WIFCONTINUED(status)) {
		                       printf("continued\n");
		                   }
		               } while (!WIFEXITED(status) && !WIFSIGNALED(status));
		               exit(1);
		           }
		 

		}
			

          // free(line);
           fclose(stream);
           //exit(0);
//	return(0);
       }
