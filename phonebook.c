#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


#define MAX_PEOPLE 10
#define BUFSIZE 256

struct phone {
	char name[MAX_PEOPLE];
	char number[MAX_PEOPLE];
	int age;
};

void phone_sort(struct phone[], int);
void phone_print(struct phone[], int);
////id phone_save(struct phone[], );
char inputbuffer[BUFSIZE];

int main(int argc, char* argv[]){

printf(1, "%Z");
  printf(1, "|\\_/|\n");
    printf(1, "|q p|   /}\n");
    printf(1, "( 0 )\"\"\"\\\n");
    printf(1, "|\"^\"`    |\n");
    printf(1, "||_/=\\\\__|\n");


 printf(1, "Ok! Let's make some phone number list here!\n");
printf(1, "Are you ready!, right now Unfortunately, you can only store 10 people!\n");
printf(1, "So think about your 10 most important people!\n");
	printf(1, "if you want to stop then input quit\n\n");

	int i, j;
	int count;
	int length;
	struct phone table[MAX_PEOPLE];


	for(i = 0; i < MAX_PEOPLE; i++){
		 
		 printf(1, "\ninput name : ");
		 gets(inputbuffer, sizeof(inputbuffer));
		 length = strlen(inputbuffer);
		 for(j = 0 ; j < length; j++){
		 	if(inputbuffer[j] == '\n'){
		 		inputbuffer[j] = '\0';
		 		break;
		 	}
		 }
		 strcpy(table[i].name, inputbuffer);
		 if(strcmp(table[i].name, "quit") == 0)
		 	break;
		 memset(inputbuffer, 0, sizeof(inputbuffer));

		 
		 printf(1, "input phone number : "); 
		 gets(inputbuffer, sizeof(inputbuffer));
		 length = strlen(inputbuffer);
		 for(j = 0 ; j < length; j++){
		 	if(inputbuffer[j] == '\n'){
		 		inputbuffer[j] = '\0';
		 		break;
		 	}
		 }
		 strcpy(table[i].number, inputbuffer);
		  if(strcmp(table[i].number, "quit") == 0)
		 	break;
		 memset(inputbuffer, 0, sizeof(inputbuffer));

		 
		 printf(1, "input age : "); 
		 gets(inputbuffer, sizeof(inputbuffer));
		 length = strlen(inputbuffer);
		 for(j = 0 ; j < length; j++){
		 	if(inputbuffer[j] == '\n'){
		 		inputbuffer[j] = '\0';
		 		break;
		 	}
		 }
		  if(strcmp(inputbuffer, "quit") == 0)
		 	break;
		 table[i].age = atoi(inputbuffer);
		
		memset(inputbuffer, 0, sizeof(inputbuffer));

		 
	}

	count = i;

	phone_sort(table, count);
	phone_print(table, count);

while(1){
	printf(1, "Do you want to save this as a file?;phonebook.txt\n");
	printf(1, "then type yes if you dont want type no\n");
	gets(inputbuffer, sizeof(inputbuffer));
	
	if(strcmp(inputbuffer, "no\n") == 0)
		 	break;
	else if(strcmp(inputbuffer, "yes\n") == 0){
		printf(1, "Unfortunately, right now save function does not work.\n");
		printf(1, "Sorry, it will be built soon\n");
		printf(1, "Please Use editor to edit file now\n");
		printf(1, "Thanks for your usage\n");
		break;
		//save logic should be added 
		/*
	int newFd = open("phonebook.txt", O_RDWR | O_CREATE);
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
}
*/
	}
}
	exit();
}

void phone_sort(struct phone table[], int count){

	int i, j;
	struct phone temp;

	for(i = 0 ; i < count - 1; i++){
		for(j = 0 ; j < count; j++){
			if(strcmp(table[i].name, table[j].name) == 1){
				temp = table[i];
				table[i] = table[j];
				table[j] = temp;
			}
		}
	}
}


void phone_print(struct phone table[], int count){
	int i;
	printf(1, "\n-------------------------------------\n");
	printf(1, "%s   %s          %s\n", "name", "phone number", "age");
	printf(1, "\n-------------------------------------\n");
	for(i = 0 ; i < count; i++)
		printf(1,"%s   %s          %d\n", table[i].name, table[i].number, table[i].age);
	printf(1, "\n-------------------------------------\n");
}



