#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

#define BUF_SIZE 256 
#define MAX_LINE_NUMBER 128
#define MAX_LINE_LENGTH 128 
#define NULL 0


char* strcat_n(char* dest, char* src, int len);
int getLineNumber(char *text[]);
void show_text(char *text[], int lineNum);
void com_ins(char *text[], int n, char *extra);
void com_mod(char *text[], int n, char *extra);
void com_del(char *text[], int n);
void com_help();
void com_save(char *text[], char *path);
void com_exit(char *text[], char *path);
int stringtonumber(char* src);

int changed = 0;
int auto_show = 1;


char text[MAX_LINE_NUMBER][MAX_LINE_LENGTH] = {};
char buffer[MAX_LINE_NUMBER * MAX_LINE_LENGTH] = {}; 

int main(int argc, char *argv[]){

	if(argc == 1)
	{
		printf(1, "Usage : please input the command as [editor file_name]\n");
		exit();
	}

/*
	char *text[MAX_LINE_NUMBER] = {};
	text[0] = malloc(MAX_LINE_LENGTH);
	memset(text[0], 0, MAX_LINE_LENGTH);
  */


//	int line_number = 0;
 
	int fd = open(argv[1], O_RDONLY | O_CREATE);
 
    if(fd < 0){
        printf(1, "error\n");
        exit();        
        }
    
    char buf[BUF_SIZE] = {}; 
    
    read(fd, buf, BUF_SIZE);

    int length = strlen(buf);
    printf(1, "length is %d\n", length);

    int bi = 0;
    int lineNumber = 0; 

    for(; bi < length; bi++){
        if(buf[bi] == '\n')
            lineNumber++; 
    }

    printf(1, "Line num is %d\n", lineNumber);
//
//string to table
//
//

int ai = 0;
int aj = 0;
int ak = 0;
int aa = 0;
int ab = 0;

for(; ai < lineNumber; ai++){ 


    for(aj = aa; aj < aa+MAX_LINE_LENGTH; aj++){
        if(buf[aj] == '\n'){
            ab = aj-aa;
            break;
        }
    }

    for(ak = 0; ak < ab+1; ak++){
        text[ai][ak] = buf[aa];
        aa++;
    }
    text[ai][ak+1] = '\0';

   // aa += 1;

}    
int a;
//   showing part
        printf(1,"---- current status----------\n");
        for(a = 0; a < lineNumber; a++){
            printf(1, "%d:  %s", a+1, text[a]); 
        }
        printf(1,"-----------------------------\n");
//  -------------------------------------------------------

//   printf(1, "%s\n", buf);
    
    close(fd);

 //  com_help();

    char input[MAX_LINE_LENGTH];
 	memset(input, 0, MAX_LINE_LENGTH);
    //getting input
   
/*
    char *text_exm[] = {"I LOVE YOU", "I LOVE YOU2","i LHAVTE"};
    
    int lineNum = getLineNumber(text_exm);
  
    printf(1, "line number is %d\n", lineNum);
    show_text(text_exm, lineNum);
*/  

 //   int a = 0 ;
 //   int b = 0;

/*
char example[MAX_LINE_NUMBER][MAX_LINE_LENGTH] = {};
    for(a = 0; a < MAX_LINE_NUMBER; a++){
        strcpy(example[a], "dfkdjfkdkjfjasd;fjksad;fjkasdjf;kasdfsfkkgagadh haj;sdfsfkajafa;f"); 
        
    }


    for(a = 0; a < MAX_LINE_NUMBER; a++){
        printf(1, "%s\n", example[a]); 
    
    }

*/

//char text[MAX_LINE_NUMBER][MAX_LINE_LENGTH] = {};


    int lineNum = 0;
//int a;
while(1){
        gets(input, MAX_LINE_LENGTH);


//command should go here            
       if(strcmp(input, "exit\n") == 0)
        break;
       else if(strcmp(input, "show_text\n") ==0){
       
       }
       else if(strcmp(input, "save\n") == 0){
       
       }
       
       //general input
        lineNum++;
        strcpy(text[lineNum-1], input);
   


//   showing part
        printf(1,"---- current status----------\n");
        for(a = 0; a < lineNum; a++){
            printf(1, "%s", text[a]); 
        }
        printf(1,"-----------------------------\n");
//  -------------------------------------------------------
  
  
    }
    
printf(1, "183\n");

int ti = 0;
int tj = 0;
int tk = 0;
int ta = 0;
int tb = 0;
//char buffer[1024] ={};

for(ti = 0 ; ti < lineNum; ti++){
    for(tj = 0 ; tj < MAX_LINE_LENGTH; tj++){
        if(text[ti][tj] == '\n'){
            tb = tj;
            break;
        } 
   }
   for(tk= 0; tk < tb+1; tk++){
    buffer[ta] = text[ti][tk];
    ta++;
   }  

} 

printf(1, "buffer \n");
printf(1, "%s", buffer);
   
   int m = 0;
    for(m = 1 ; m < lineNum+1; m++){
       printf(1, "line_%d : %s", m, text[m-1]); 
    }
    
    
    
    exit();




}
 

char* strcat_n(char* dest, char* src, int len)
{
	if (len <= 0)
		return dest;
	int pos = strlen(dest);
	if (len + pos >= MAX_LINE_LENGTH)
		return dest;
	int i = 0;
	for (; i < len; i++)
		dest[i+pos] = src[i];
	dest[len+pos] = '\0';
	return dest;
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

int getLineNumber(char *text[])
{
	int i = 0;
    int LineNumber = 0;
	
    char* p = text[0]; 
    int size = sizeof(text[0]);
    int size_p = sizeof(p);
    printf(1, "szie %d and psize %d\n", size, size_p);
    for(i = 0; i < 100; i++){
        if(*p == '\n')
            LineNumber++; 
            
        p++;
      }
	return LineNumber;
}

int stringtonumber(char* src)
{
	int number = 0; 
	int i=0;
	int pos = strlen(src);
	for(;i<pos;i++)
	{
		if(src[i]==' ') break;
		if(src[i]>57||src[i]<48) return -1;
		number=10*number+(src[i]-48);
	}
	return number;
}
/*
void com_ins(char *text[], int n, char *extra)
{
	if (n < 0 || n > getLineNumber(text) + 1)
	{
		printf(1, "invalid line number\n");
		return;
	}
	char input[MAX_LINE_LENGTH] = {};
	if (*extra == '\0')
	{
		printf(1, "please input content:\n");
		gets(input, MAX_LINE_LENGTH);
		input[strlen(input)-1] = '\0';
	}
	else
		strcpy(input, extra);
	int i = MAX_LINE_NUMBER - 1;
	for (; i > n; i--)
	{
		if (text[i-1] == NULL)
			continue;
		else if (text[i] == NULL && text[i-1] != NULL)
		{
			text[i] = malloc(MAX_LINE_LENGTH);
			memset(text[i], 0, MAX_LINE_LENGTH);
			strcpy(text[i], text[i-1]);
		}
		else if (text[i] != NULL && text[i-1] != NULL)
		{
			memset(text[i], 0, MAX_LINE_LENGTH);
			strcpy(text[i], text[i-1]);
		}
	}
	if (text[n] == NULL)
	{
		text[n] = malloc(MAX_LINE_LENGTH);
		if (text[n-1][0] == '\0')
		{
			memset(text[n], 0, MAX_LINE_LENGTH);
			strcpy(text[n-1], input);
			changed = 1;
			if (auto_show == 1)
				show_text(text);
			return;
		}
	}
	memset(text[n], 0, MAX_LINE_LENGTH);
	strcpy(text[n], input);
	changed = 1;
	if (auto_show == 1)
		show_text(text);
}
*/
/*
void com_mod(char *text[], int n, char *extra)
{
	if (n <= 0 || n > getLineNumber(text) + 1)
	{
		printf(1, "invalid line number\n");
		return;
	}
	char input[MAX_LINE_LENGTH] = {};
	if (*extra == '\0')
	{
		printf(1, "please input content:\n");
		gets(input, MAX_LINE_LENGTH);
		input[strlen(input)-1] = '\0';
	}
	else
		strcpy(input, extra);
	memset(text[n-1], 0, MAX_LINE_LENGTH);
	strcpy(text[n-1], input);
	changed = 1;
	if (auto_show == 1)
		show_text(text);
}
*/
/*
void com_del(char *text[], int n)
{
	if (n <= 0 || n > getLineNumber(text) + 1)
	{
		printf(1, "invalid line number\n");
		return;
	}
	memset(text[n-1], 0, MAX_LINE_LENGTH);
	int i = n - 1;
	for (; text[i+1] != NULL; i++)
	{
		strcpy(text[i], text[i+1]);
		memset(text[i+1], 0, MAX_LINE_LENGTH);
	}
	if (i != 0)
	{
		free(text[i]);
		text[i] = 0;
	}
	changed = 1;
	if (auto_show == 1)
		show_text(text);
}
*/
void com_help()
{
	printf(1, "****************************************\n");
	printf(1, "instructions for use:\n");
	printf(1, "ins-n, insert a line after line n\n");
	printf(1, "mod-n, modify line n\n");
	printf(1, "del-n, delete line n\n");
	printf(1, "ins, insert a line after the last line\n");
	printf(1, "mod, modify the last line\n");
	printf(1, "del, delete the last line\n");
	printf(1, "show, enable show current contents after executing a command.\n");
	printf(1, "hide, disable show current contents after executing a command.\n");
	printf(1, "save, save the file\n");
	printf(1, "exit, exit editor\n");
    printf(1, "****************************************\n");
}

void com_save(char *text[], char *path)
{
	unlink(path);
	int fd = open(path, O_WRONLY|O_CREATE);
	if (fd == -1)
	{
		printf(1, "save failed, file can't open:\n");
		exit();
	}
	if (text[0] == NULL)
	{
		close(fd);
		return;
	}
	write(fd, text[0], strlen(text[0]));
	int i = 1;
	for (; text[i] != NULL; i++)
	{
		printf(fd, "\n");
		write(fd, text[i], strlen(text[i]));
	}
	close(fd);
	printf(1, "saved successfully\n");
	changed = 0;
	return;
}

void com_exit(char *text[], char *path)
{
	while (changed == 1)
	{
		printf(1, "save the file? y/n\n");
		char input[MAX_LINE_LENGTH] = {};
		gets(input, MAX_LINE_LENGTH);
		input[strlen(input)-1] = '\0';
		if (strcmp(input, "y") == 0)
			com_save(text, path);
		else if(strcmp(input, "n") == 0)
			break;
		else
		printf(2, "wrong answer?\n");
	}
	int i = 0;
	for (; text[i] != NULL; i++)
	{
		free(text[i]);
		text[i] = 0;
	}
	exit();
}
