#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
  printf(1, "\n");
  printf(1, "NOTE: [] -> optional parameter, () -> required parameter\n\n");
  printf(1, "command      	-  will display a list value shell commands\n");
  printf(1, "echo [text]  	-  will output the text that follows the command\n");
  printf(1, "ps [-l]      	-  will display a list of running processes\n");
  printf(1, "ls           	-  will display a list of files in the current directory\n");
  printf(1, "kill [pid]   	-  will cease a process with pid provided\n");  
  printf(1, "clear        	-  will clear the terminal of its current text\n");
  printf(1, "app          	-  will lead to app program which can launch other applications\n");
  printf(1, "editor [filename] -  will open editor program with file whose name is filename\n");
  printf(1, "filesystemtest    -  will test file system and make a new file named testfile\n");
  printf(1, "filesize [filename] -  will return the size of file whose name is filename\n");
  printf(1, "filecopy [srcfile] [desfile] - will copy srcfile to desfile; if there is no desfile, then it will be newly made\n");
  
  
  
  
  
  
  printf(1, "\n");

  exit();
}
