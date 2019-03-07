#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
  printf(1, "\n");
  printf(1, "NOTE: [] -> optional parameter, () -> required parameter\n\n");
  printf(1, "command      -  will display a list value shell commands\n");
  printf(1, "echo [text]  -  will output the text that follows the command\n");
  printf(1, "ps [-l]      -  will display a list of running processes\n");
  printf(1, "ls           -  will display a list of files in the current directory\n");
  printf(1, "kill [pid]   -  will cease a process with pid provided\n");  
  printf(1, "clear        -  will clear the terminal of its current text\n");
  printf(1, "renice (nice) (pid) (priority)\n");
  printf(1, "             -  will change priority of a currently executing process\n");
  printf(1, "\n");

  exit();
}
