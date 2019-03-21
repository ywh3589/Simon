#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


#define MAX 1024

int main(int argc, char *argv[]){

	int fd1, fd2, count;
	char buf[MAX];

	if(argc < 3) {
     printf(1, "\\    /\\\n");

    printf(1, " )  ( ')\n");

    printf(1, "(  /  )\n");

    printf(1, " \\(__)|\n\n");
      printf(2, "Usage: filecopy [src filename] [des filename] \n");
      exit();
  }

  if((fd1=open(argv[1], O_RDONLY)) == -1){
  	printf(1, "ERROR: file open failed\n");
  	exit();
  }

  if((fd2=open(argv[2], O_WRONLY | O_CREATE)) == -1){
  	printf(1, "ERROR: file open failed\n");
  	exit();
  }

  while((count=read(fd1, buf, MAX)) > 0){

  	if(write(fd2, buf, count) != count){
  		printf(1, "ERROR: file write failed\n");
  		exit();		
  	}
  }




      printf(1, "%Z");
   printf(1, "\\    /\\\n");

    printf(1, " )  ( ')\n");

    printf(1, "(  /  )\n");

    printf(1, " \\(__)|\n\n");

    printf(1, "file %s has been successfully copied as %s\n", argv[1], argv[2]);

  close(fd1);
  close(fd2);

  exit();
}