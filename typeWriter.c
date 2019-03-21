



//At first typeWriter was just a experimental program to test on gets() function on xv6 but it got upgraded with file system interaction with functions used in editor. 
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

#define BUF_SIZE 256
#define MAX_LINE_NUMBER 256
#define MAX_LINE_LENGTH 256

void textToString(int );
void cSave(char*, int);



char text[MAX_LINE_NUMBER][MAX_LINE_LENGTH] = {};
char fileWriteBuf[BUF_SIZE] = {}; 
char input[MAX_LINE_LENGTH] ={};

int main(int argc, char *argv[]){


//checking out the usage.
  
	if(argc > 1)
	{
		printf(1, "Usage : please just type typeWriter! \n");
		exit();
	}
      
//typeWriter instruction

   printf(1, "%Z");
  printf(1, "|\\_/|\n");
    printf(1, "|q p|   /}\n");
    printf(1, "( 0 )\"\"\"\\\n");
    printf(1, "|\"^\"`    |\n");
    printf(1, "||_/=\\\\__|\n");
  printf(1, "********************************************************************************");
  printf(1, "Welcome to Simon typeWriter ~~                                                 *");
  printf(1, "Write a letter to someone you love feeling like you are using type writer!     *");
  printf(1, "You can see the letter you wrote using editor program, thank you!              *");
  printf(1, "instructions for use:                                                          *");      
  printf(1, "save, save the letter                                                          *");
  printf(1, "exit, exit the program                                                         *");
  printf(1, "********************************************************************************\n");
//input buffer
 //	memset(input, 0, MAX_LINE_LENGTH);
    //getting input
   
    printf(1, "********************************************************************************");
    printf(1, "																				*");
    printf(1, "  Dear My Love                                                                 *");
    printf(1, "                                                                               *\n");
	
strcpy(text[0], "Dear My Love\n");
int lineNumber = 1;

while(1){

   

    printf(1, "                                                                               *");
    printf(1, "\n");
    gets(input, MAX_LINE_LENGTH);
   
    
    printf(1, "                                                                               *");
	//printf(1, "********************************************************************************");

       if(strcmp(input, "exit\n") == 0){
       			break;
       }
       else if(strcmp(input, "save\n") == 0){
       //writing on the file
       	//at first making into string and save in the file.
       		//char* openfile = argv[1];
       		

       		cSave("loveLetter", lineNumber);
       	
       }

    strcpy(text[lineNumber], input);
    lineNumber++;


}
  
    
    exit();

}
 


void textToString(int lineNumber)
{
//after filling the table with input, we have to change the "text" table to string to store in the file. 
//table to string logic ; refactoring needed
	int ti = 0;
	int tj = 0;
	int tk = 0;
	int ta = 0;
	int tb = 0;
	for(ti = 0 ; ti < lineNumber; ti++){
	    for(tj = 0 ; tj < MAX_LINE_LENGTH; tj++){
	        if(text[ti][tj] == '\n'){
	            tb = tj;
	            break;
	        } 
	   }
	   for(tk= 0; tk < tb+1; tk++){
	    fileWriteBuf[ta] = text[ti][tk];
	    ta++;
	   }  

	} 

	fileWriteBuf[ta+1] = '\0';

}




void cSave(char* openfile, int lineNumber)
{
	int newFd = open(openfile, O_RDWR | O_CREATE);
    if(newFd < 0){
    	     	printf(1, "file oen error in save\n");
       	exit();   
    }
  
       	
    memset(fileWriteBuf, 0, sizeof(fileWriteBuf));
    textToString(lineNumber);

    if(write(newFd, fileWriteBuf, sizeof(fileWriteBuf)) == -1){
       	printf(1, "error; can not write in the file\n"); 
    }

    printf(1, "file save success\n");

    close(newFd);
}


