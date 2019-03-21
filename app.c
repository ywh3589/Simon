#include "types.h"
#include "stat.h"
#include "user.h"


#define BUFSIZE 256

void showProgram();

char inputbuffer[BUFSIZE];
int main(int argc, char*argv[])
{
   

    
for(;;){

 printf(1, "%Z");
//https://rightbellboy.tistory.com/50?category=731489
    printf(1, "|\\_/|\n");
    printf(1, "|q p|   /}\n");
    printf(1, "( 0 )\"\"\"\\\n");
    printf(1, "|\"^\"`    |\n");
    printf(1, "||_/=\\\\__|\n");
    printf(1, "Hi, I am Sidog!\n");
    printf(1, "Type in name program you want to launch\n");
    printf(1, "if you want to quit, type exit and enter!\n");



showProgram();



char* pro[2] = {};



    gets(inputbuffer, sizeof(inputbuffer));


  if(strcmp(inputbuffer,"exit\n") == 0) 
    {
        exit();
    }

     int pid = fork();
   
        if(pid == -1){
            printf(1, "failed\n");
           exit();
        }
        else if(pid == 0){

            inputbuffer[strlen(inputbuffer)-1] = '\0';
            strcpy(pro[0], inputbuffer);
            char* ddd[2] = {pro[0], "\0"};
            exec(ddd[0], ddd);
            exit();
        }

            wait();


}

}


void showProgram(){
printf(1, "\n------------------------------------------\n");
printf(1, "1. phonebook; store your 10 favorite people\n");
printf(1, "2. typeWriter; write the letter you want to keep\n");
printf(1, "3. bingo; play bingo with Sidog\n");
printf(1, "4. dailyRiddle; solve the question which Scidog asks you\n");



}