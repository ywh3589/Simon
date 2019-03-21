#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char* argv[]){

	int fd, fileSize;

	if(argc < 2) {
		 printf(1, "\\    /\\\n");

    printf(1, " )  ( ')\n");

    printf(1, "(  /  )\n");

    printf(1, " \\(__)|\n\n");
      printf(2, "Usage: filesize filename \n");
      exit();
  }

	if((fd = open(argv[1], O_RDONLY)) == -1){
		printf(1, "ERROR: open failed\n");
		exit();
	}

	

	if((fileSize = cLseek(fd, 0, SEEK_END)) == -1){
		printf(1, "ERROR: lseek failed\n");
		exit();
	}
	
			printf(1, "%Z");
	 printf(1, "\\    /\\\n");

    printf(1, " )  ( ')\n");

    printf(1, "(  /  )\n");

    printf(1, " \\(__)|\n\n");

	printf(1, "%s's size is %d\n", argv[1], fileSize);
	close(fd);

	exit();
}
