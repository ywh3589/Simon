#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUFSIZE 256

int main(){

//file descriptor
	int fd;

int writefilesize, readfilesize;

	char writeBuffer[BUFSIZE] = {};
	char readBuffer[BUFSIZE] = {};
	
	strcpy(writeBuffer, "one\ntwo\nthree\nfour\nfive\nsix\nseven\neight\nnine\nten\n"); 
	
//test file openin test
	fd = open("testfile", O_CREATE | O_RDWR);

	
	if(fd < 0){
		     printf(1, "%Z");
   printf(1, "\\    /\\\n");

    printf(1, " )  ( ')\n");

    printf(1, "(  /  )\n");

    printf(1, " \\(__)|\n\n");

		printf(1, "Uh, failed in creating file\n");
	}


	writefilesize = write(fd, writeBuffer, sizeof(writeBuffer) );
	if(writefilesize != sizeof(writeBuffer)){
		     printf(1, "%Z");
   printf(1, "\\    /\\\n");

    printf(1, " )  ( ')\n");

    printf(1, "(  /  )\n");

    printf(1, " \\(__)|\n\n");

		printf(1, "Uh, failed in writing in file\n");
	}


	readfilesize = read(fd, readBuffer, sizeof(readBuffer) );
	if(readfilesize != sizeof(readBuffer)){
		     printf(1, "%Z");
   printf(1, "\\    /\\\n");

    printf(1, " )  ( ')\n");

    printf(1, "(  /  )\n");

    printf(1, " \\(__)|\n\n");

		printf(1, "Uh, failed in rading from file\n");
	}

	if(strcmp(writeBuffer, readBuffer) != 0){
		     printf(1, "%Z");
   printf(1, "\\    /\\\n");

    printf(1, " )  ( ')\n");

    printf(1, "(  /  )\n");

    printf(1, " \\(__)|\n\n");
    	printf(1, "Could not pass the test\n");
	}



     printf(1, "%Z");
   printf(1, "\\    /\\\n");

    printf(1, " )  ( ')\n");

    printf(1, "(  /  )\n");

    printf(1, " \\(__)|\n\n");
    printf(1, "Calm down, filesystem does work!\n");


    exit();
}