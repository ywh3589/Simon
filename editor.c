#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

#define BUF_SIZE 256
#define MAX_LINE_NUMBER 256
#define MAX_LINE_LENGTH 256
#define NULL 0


void textToString(int );
int getLineNumber(char*);
void showText(int );
void cHelp();
void cSave(char*, int);


char text[MAX_LINE_NUMBER][MAX_LINE_LENGTH] = {};
char temp_text[MAX_LINE_NUMBER][MAX_LINE_LENGTH] = {};
char fileWriteBuf[BUF_SIZE] = {}; 
char fileReadBuf[BUF_SIZE] = {}; 

int main(int argc, char *argv[]){


//checking out the usage.
	if(argc == 1)
	{
		printf(1, "Usage : please input the command as [editor file_name]\n");
		exit();
	}

//opening file, if it does not exist, it makes a new file.  
	int fd = open(argv[1], O_RDWR | O_CREATE);
 
    if(fd < 0){
        printf(1, "error\n");
        exit();        
        }
    
    
//reading file, and getting the number of lines in the file.    
    read(fd, fileReadBuf, BUF_SIZE);

	int lineNumber = getLineNumber(fileReadBuf);
  
	close(fd);

// logig for string to table; refactoring needed.

int ai = 0;
int aj = 0;
int ak = 0;
int aa = 0;
int ab = 0;

for(; ai < lineNumber; ai++){ 

    for(aj = aa; aj < aa+MAX_LINE_LENGTH; aj++){
        if(fileReadBuf[aj] == '\n'){
            ab = aj-aa;
            break;
        }
    }

    for(ak = 0; ak < ab+1; ak++){
        text[ai][ak] = fileReadBuf[aa];
        aa++;
    }
    text[ai][ak+1] = '\0';
}    

	
//   showing part; checking the readbuff is well transformed into "text" 2D array. 
		//showText(lineNumber);
//  -------------------------------------------------------

      
//editor instruction
 printf(1, "%Z");
    //https://j0n9m1n1.com/87
   
    printf(1, "\\    /\\\n");

    printf(1, " )  ( ')\n");

    printf(1, "(  /  )\n");

    printf(1, " \\(__)|\n\n");
 
   cHelp();

//input buffer
    char input[MAX_LINE_LENGTH];
 	memset(input, 0, MAX_LINE_LENGTH);
    //getting input
   

while(1){
        gets(input, MAX_LINE_LENGTH);


//command should go here            
       if(strcmp(input, "exit\n") == 0){
       			break;
       }
       else if(strcmp(input, "show\n") ==0){
       // showing current text
       			showText(lineNumber);
       			continue;
       }
       else if(strcmp(input, "help\n") ==0){
       //showing instruction
       			cHelp();
       			continue;
       }
       else if(strcmp(input, "save\n") == 0){
       //writing on the file
       	//at first making into string and save in the file.
       		char* openfile = argv[1];
       		cSave(openfile, lineNumber);
       		continue;
       }

       else if(input[0] == 'i' && input[1] == 'n' && input[2] == 's'){
       //숫자 받는 로직 짜야겠네....
       		int lineToIns = atoi(&input[4]);
       		if((lineToIns <=0) || (lineToIns > lineNumber))
       		{
       			printf(1, "usage; invalid line number, the line number should in between 1 and %d\n", lineNumber);
       			continue;
       		}
			

			//gets(input, MAX_LINE_LENGTH);


       		int ia = 0;
       		int ib = 0;
       		//Copying to temp_text
       		for(ia = lineToIns-1; ia < lineNumber; ia++)
       		{
       			for(ib = 0; ib < MAX_LINE_LENGTH; ib++){
       				temp_text[ia][ib] = text[ia][ib];
       			}

       		}

 
       		gets(input, MAX_LINE_LENGTH);
       		strcpy(text[lineToIns-1], input);

       		for(ia = lineToIns-1; ia < lineNumber; ia++)
       		{
       			for(ib = 0; ib < MAX_LINE_LENGTH; ib++){
       				text[ia+1][ib] = '\0';
       			}

       		}	

       		for(ia = lineToIns-1; ia < lineNumber+1; ia++)
       		{
       			for(ib = 0; ib < MAX_LINE_LENGTH; ib++){
       				text[ia+1][ib] = temp_text[ia][ib];
       			}

       		}	

       		lineNumber++;
  
       		continue;


       }
       else if(input[0] == 'd' && input[1] == 'e' && input[2] == 'l'){
	       	int lineToDel = atoi(&input[4]);
	       	if((lineToDel <=0) || (lineToDel > lineNumber))
       		{
       			printf(1, "usage; invalid line number, the line number should in between 1 and %d\n", lineNumber);
       			continue;
       		}
       
       
       		int ia = 0;
       		int ib = 0;
       		//Copying to temp_text
       		for(ia = lineToDel; ia < lineNumber; ia++)
       		{
       			for(ib = 0; ib < MAX_LINE_LENGTH; ib++){
       				temp_text[ia][ib] = text[ia][ib];
       			}

       		}

       		for(ia = lineToDel; ia < lineNumber; ia++)
       		{
       			for(ib = 0; ib < MAX_LINE_LENGTH; ib++){
       				text[ia][ib] = '\0';
       			}

       		}	

       		for(ia = lineToDel; ia < lineNumber; ia++)
       		{
       			for(ib = 0; ib < MAX_LINE_LENGTH; ib++){
       				text[ia-1][ib] = temp_text[ia][ib];
       			}

       		}	

       		lineNumber--;
 	
        	continue;
       }
       else if(input[0] == 'm' && input[1] == 'o' && input[2] == 'd'){
       		int lineToMod = atoi(&input[4]);
       		if((lineToMod <=0) || (lineToMod > lineNumber))
       		{
       			printf(1, "usage; invalid line number, the line number should in between 1 and %d\n", lineNumber);
       			continue;
       		}
       		
       		int i = 0;
       		for(; i < MAX_LINE_LENGTH; i++)
       			text[lineToMod-1][i] = '\0';

    		gets(input, MAX_LINE_LENGTH);

       		strcpy(text[lineToMod-1], input);
       		continue;
       }
       //general input
       // lineNumber++;
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



void showText(int lineNumber)
{
		int a;
//   showing part
        printf(1,"---- current text------------------------------\n");
        for(a = 0; a < lineNumber; a++){
            printf(1, "%d:  %s", a+1, text[a]); 
        }
        printf(1,"------------------------------------------------\n");
//  -------------------------------------------------------

}



void show_text(char *text[], int lineNum)
{
	printf(1, "****************************************\n");
	printf(1, "the contents of the file are:\n");
	int j = 0;
	for (; j < lineNum ; j++)
		printf(1, "line_%d : %s\n", j+1, text[j]);

	printf(1, "****************************************\n");
}

int getLineNumber(char *text)
{
	 int length = strlen(text);
   // printf(1, "length is %d\n", length);

    int bi = 0;
    int lineNumber = 0; 

    for(; bi < length; bi++){
        if(text[bi] == '\n')
            lineNumber++; 
    }

   // printf(1, "Line num is %d\n", lineNumber);
	return lineNumber;
}

void cHelp()
{
	printf(1, "****************************************\n");
	printf(1, "Welcome to Simon editor~, I am Sicat again to help you!\n\n");
	printf(1, "what you typed, automatically, will be appended to the end of the file.\n");
	printf(1, "instructions for use:\n");
	printf(1, "ins n, insert a line after line n\n");
	printf(1, "mod n, modify line n\n");
	printf(1, "del n, delete line n\n");
	printf(1, "show, showing the current text.\n");
    printf(1, "help, showing the instruction, again.\n");
	printf(1, "save, save the file\n");
	printf(1, "exit, exit editor\n");
    printf(1, "****************************************\n");
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


