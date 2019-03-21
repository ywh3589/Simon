
// original source : https://blog.naver.com/lyw94k/220863458807
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUFSIZE 256

void bingoGameStart(int*); 
void printRecord(int*); 
void init(int*); 

int checkBingo(int*); 
void printBingoBoard(int*); 
void inputNum(int*, int*); 
void randNum(int*, int*, int *); 



//https://github.com/joonlim/xv6/blob/master/random.c

int rand(void)

{

  // Take from http://stackoverflow.com/questions/1167253/implementation-of-rand

  static unsigned int z1 = 12345, z2 = 12345, z3 = 12345, z4 = 12345;

  unsigned int b;

  b  = ((z1 << 6) ^ z1) >> 13;

  z1 = ((z1 & 4294967294U) << 18) ^ b;

  b  = ((z2 << 2) ^ z2) >> 27; 

  z2 = ((z2 & 4294967288U) << 2) ^ b;

  b  = ((z3 << 13) ^ z3) >> 21;

  z3 = ((z3 & 4294967280U) << 7) ^ b;

  b  = ((z4 << 3) ^ z4) >> 12;

  z4 = ((z4 & 4294967168U) << 13) ^ b;



  return (z1 ^ z2 ^ z3 ^ z4) / 2;

}

// Return a random integer between a given range.

int randomrange(int lo, int hi)

{

  if (hi < lo) {

    int tmp = lo;

    lo = hi;

    hi = tmp;

  }

  int range = hi - lo + 1;

  return rand() % (range) + lo;

}



char gameRecord[2][BUFSIZE] = {};


int main() 
{


	char input[BUFSIZE];

	memset(input, 0, sizeof(input));

	
	//int menu; 

	int record[3] = { 0 }; 
	while (1) 
	{
		printf(1, "%Z");
  	printf(1, "|\\_/|\n");
    printf(1, "|q p|   /}\n");
    printf(1, "( 0 )\"\"\"\\\n");
    printf(1, "|\"^\"`    |\n");
    printf(1, "||_/=\\\\__|\n");

printf(1, "Ok! Let's play some bingo game with me!\n");
printf(1, "Are you ready?, \n\n");
	
		printf(1, "1. bingo start, if you want to start type start and enter\n");
		printf(1, "2. record, if you want to see the record, type record and enter\n");
		printf(1, "3. exit, if you want to stop then type quit and enter!\n");
		
		 gets(input, sizeof(input));
	
		//get으로 바꿔서 if문 돌린다.... 
		if(strcmp(input, "start\n") == 0){
			bingoGameStart(record);
		}
		else if(strcmp(input, "record\n") == 0)
		{
			printRecord(record);
		}	
		else if(strcmp(input, "exit\n") == 0)
		{
			//save
			



			
			break;
		}
	}
		
	printf(1, "%Z");
  	printf(1, "|\\_/|\n");
    printf(1, "|q p|   /}\n");
    printf(1, "( 0 )\"\"\"\\\n");
    printf(1, "|\"^\"`    |\n");
    printf(1, "||_/=\\\\__|\n");
	printf(1, "exiting bingo game ~~~~\n");
	

	exit();
}


void bingoGameStart(int *record)
{
	int userBingo[25]; 
	int comBingo[25]; 
	int userCount; 
	int comCount; 
	int isTurn = 0; 
			
	init(userBingo); 
	init(comBingo); 

	while (1) 
	{




		userCount = checkBingo(userBingo); 
		comCount = checkBingo(comBingo); 
		printBingoBoard(userBingo); 
		printf(1, "USER : %d line bingo\n", userCount);
		printf(1, "SIDOG : %d line bingo\n", comCount);
		
		if ((userCount >= 5 && isTurn) || (userCount >= 5 && comCount < 5))
		{
			printf(1, "you made %d bingos and won!!\n", userCount);
			record[0]++; 
			record[1]++; 
			sleep(500);
			break; 
		}
		else if (comCount >= 5)
		{
			printf(1, "Sidog made %d bingos and won.\n", comCount);
			record[0]++;
			record[2]++; 
			sleep(500);
		
			break;
		}
		
		isTurn = !isTurn;
		if (isTurn) 
			inputNum(userBingo, comBingo);
		else 
			randNum(userBingo, comBingo, record);
		
	}

}




void printRecord(int *record)
{


/*
	int fd = open("bingoRecord", O_RDWR | O_CREATE);
 
    if(fd < 0){
        printf(1, "error\n");
        exit();        
        }
    
    
//reading file, and getting the number of lines in the file.    
    read(fd, recordRead, BUFSIZE);
  
	close(fd);

char win[BUFSIZE] = {};
char loss[BUFSIZE] = {};

int i = 0;
int j = 0;
int a = 0;
for(i = 0; i < BUFSIZE; i++){
	if( strcmpt(recordRead[i], '\n') == 0)
	{
		for(j = 0; j < i; j++)
			win[j] = recordRead[j];
	}
		for(j = i+1; j < BUFSIZE; j++){
			if(strcmp(recordRead[j], '\n') == 0)
				break;
			loss[a] = recordRead[j];
			a++;
		}
	
}

int winNum = atoi(win);
int lossNum = atoi(loss);

printf(1, "win number is %d\n", winNum);
printf(1, "loss number is %d\n", lossNum);


*/


	if (record[0])
	{
		printf(1, "\n********** RECORD **********\n");
		printf(1, " WIN : %d LOSS : %d \n", record[1], record[2]);
	}
	else{
		printf(1, "You do not have record, yet.\n");
		
	}

	sleep(300);
	

	sleep(3000);
}




void init(int *bingo)
{
	int i; 
	int src, des; 
	int temp; 
	

	for (i = 0; i < 25; i++) 
		bingo[i] = i + 1; 
		

	for(i = 0; i < 200 ; i++){
		src = randomrange(0, 24); 
		
		des = randomrange(0, 24); 
		
		temp = bingo[src]; 
		bingo[src] = bingo[des]; 
		bingo[des] = temp; 
	}
}


void printBingoBoard(int *bingo)
{

	int i, j;
	printf(1, "%Z");
		
	printf(1, "---------------------------\n");

for(i = 0; i < 5; i++){
	for(j = 0; j < 5; j++){

	printf(1, "|");
		if(bingo[(i*5) + j] == 35)
			printf(1, "X|");
		else
			printf(1, "%d|", bingo[(i*5) + j]);

	
	}
		printf(1, "\n");
	printf(1, "---------------------------\n");
}



}


int checkBingo(int *bingo)
{
	int bingoCheck[12] = { 0 };
	int count = 0;	
	int i, j;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (bingo[i * 5 + j] == 35)
				bingoCheck[i]++;
			if (bingo[j * 5 + i] == 35)
				bingoCheck[i + 5]++;
		}
		for (j = i; j <= i; j++)
			if (bingo[i * 5 + j] == 35)
				bingoCheck[10]++;
	}
	for (i = 4; i >= 0; i--)
		for (j = 4 - i; j >= 4 - i; j--)
			if (bingo[i * 5 + j] == 35)
				bingoCheck[11]++;
	for (i = 0; i < 12; i++)
		if (bingoCheck[i] == 5)
			count++;
	return count;
}


void inputNum(int *userBingo, int *comBingo)
{
	int i;
	int num;	
	int isCheck;	
	char input[BUFSIZE];

	while (1)	
	{
		memset(input, 0, sizeof(input));
		isCheck = 0;	
		printf(1, "Please, type the number(1~25) and press enter!");
		
		 gets(input, sizeof(input));


		 num = atoi(input);
		 printf(1, "the input number is %d\n", num);


		if (num < 1 || num > 25)	
			printf(1, "Type in number betwwen 1 ~ 25\n");	
		else	
		{
			for (i = 0; i < 25; i++)	
			{
				if (userBingo[i] == num)	
				{
					userBingo[i] = 35;	
					isCheck = 1;	
				}
				if (comBingo[i] == num)	
				{
					comBingo[i] = 35;	
				}
			}
			if (isCheck)	
				break;	
			else	
				printf(1, "Already processed number.\n");	
		}
	}
}


void randNum(int *userBingo, int *comBingo, int *record)
{
	int i;
	int num= 0;	
	int isCheck;	
	printf(1, "Sidog's turn.\n");	
	sleep(100);	
	
	int level = 0;
	int winNum = record[1];
	if((winNum > 1) && (winNum < 2)){
		level = 1;
	}
	if(winNum >= 2){
		level = 2;
	}


	while (1)	
	{

	if(level == 0){
		isCheck = 0;	
		num = rand() % 25 + 1;	
		for (i = 0; i < 25; i++)	
		{
			if (userBingo[i] == num)	
			{
				userBingo[i] = 35;	
				isCheck = 1;	
			}
			if (comBingo[i] == num)	
			{
				comBingo[i] = 35;	
			}
		}

	}	
	else if(level == 1){
		isCheck = 0;	
		
		//num = rand() % 25 + 1;	
		for (i = 0; i < 25; i++)	
		{
			if (userBingo[i] == 35)	
			{
				userBingo[i+1] = 35;	
				isCheck = 1;
				num = i + 1;	
			}
			if (comBingo[i] == 35)	
			{
				comBingo[i+1] = 35;	
			}
		}

	}	
		else if(level == 2){
		isCheck = 0;	
		//num = rand() % 25 + 1;	
		for (i = 0; i < 25; i++)	
		{
			if ((userBingo[i] == 35) && (userBingo[i+1] == 35))	
			{
				userBingo[i+2] = 35;	
				isCheck = 1;
				num = i+2;	
			}
			if ((comBingo[i] == 35) && (comBingo[i+1] == 35))	
			{
				comBingo[i+2] = 35;	
			}
			
			else{
				userBingo[12] = 35;
				comBingo[12] = 35;
				isCheck = 1;
				num = 12;
			}
		}


	}





		if (isCheck)	
			break;	
	}
	printf(1, "The number Sidog chose : %d\n", num);	
	sleep(150);	
}
