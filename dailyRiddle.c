#include "types.h"
#include "stat.h"
#include "user.h"

#define BUFSIZE 256


int main(void)
{
     int childpid;
     int pipes1[2], pipes2[2], length;
     char read_buffer[BUFSIZE], write_buffer[BUFSIZE], answer_buffer[BUFSIZE];


     if(pipe(pipes1) == -1 || pipe(pipes2) == -1){
        printf(1, "ERROR: pipe failed");
        exit();
     }

 if((childpid = fork()) == -1)
        {
                printf(1, "fork error\n");
                exit();
        }
//children
        if(childpid == 0)
        {
                close(pipes1[0]);
                close(pipes2[1]);

                strcpy(write_buffer, "What's that?\n");
                write(pipes1[1], write_buffer, strlen(write_buffer));
              //  sleep(10);

        if((length= read(pipes2[0], read_buffer, BUFSIZE)) == -1){
                printf(1, "read failed\n");
                exit();
        }

       printf(1, "\\    /\\\n");

    printf(1, " )  ( ')\n");

    printf(1, "(  /  )\n");

    printf(1, " \\(__)|\n\n");


                printf(1, "%Z");

            sleep(300);
            printf(1, "Sidog : do you know this logo?\n\n ");
    //https://splug.tistory.com/89
    printf(1, "       _.-;;-._\n");
    printf(1, "'-..-'|   ||   |\n");
    printf(1, "'-..-'|_.-;;-._|\n");
    printf(1, "'-..-'|   ||   |\n");
    printf(1, "'-..-'|_.-''-._|\n\n");


        printf(1, "Sicat : Ummm... Let me think...\n");
        
        printf(1, "Can you get to know faster?, if you know the answer, type in and please help me!\n");
        gets(answer_buffer, sizeof(answer_buffer));


        sleep(500);


        
        printf(1, "Sidog : The answer is : %s\n", read_buffer);
        sleep(500);
        if(strcmp(answer_buffer, read_buffer) == 0){
            printf(1, "Sicat : Thanks! you were right!\n");
            sleep(500);
        }

        }

        else
        {
                close(pipes1[1]);
        close(pipes2[0]);

        if((length = read(pipes1[0], read_buffer, BUFSIZE)) == -1){
            printf(1, "ERROR: read failed");
            exit();
        }

        sleep(100);
            printf(1, "%Z");


    printf(1, "|\\_/|\n");
    printf(1, "|q p|   /}\n");
    printf(1, "( 0 )\"\"\"\\\n");
    printf(1, "|\"^\"`    |\n");
    printf(1, "||_/=\\\\__|\n");

        printf(1, "Sidog : Hi, I have a question for you!\n");

    
        printf(1, "Sicat : %s\n", read_buffer);

        sleep(100);
    

        strcpy(write_buffer, "Windows\n");

        write(pipes2[1], write_buffer, strlen(write_buffer));

        wait();
        }
        exit();


   
     exit();
}
