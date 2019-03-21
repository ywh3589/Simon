

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
/*
void bingoGameStart(int*); 
void printRecord(int*); 
void init(int*); 
int checkBingo(int*); 
void printBingoBoard(int*); 
void inputNum(int*, int*); 
void randNum(int*, int*); 
*/

int main() 
{
	//int menu; 
	//int record[3] = { 0 }; 
	//int bingo[25];
	//int i, j;


	printf(1, "----------------------\n");
	printf(1, "%d | %d | %d | %d | %d | %d |\n", 10 , 20, 30, 40, 50, 60);
	printf(1, "----------------------\n");
	
	printf(1, "%d | %d | %d | %d | %d | %d |\n", 10 , 20, 30, 40, 50, 60);
	printf(1, "----------------------\n");
	
	printf(1, "%d | %d | %d | %d | %d | %d |\n", 10 , 20, 30, 40, 50, 60);
	printf(1, "----------------------\n");
	
	printf(1, "%d | %d | %d | %d | %d | %d |\n", 10 , 20, 30, 40, 50, 60);
	printf(1, "----------------------\n");
	
	printf(1, "%d | %d | %d | %d | %d | %d |\n", 10 , 20, 30, 40, 50, 60);
	printf(1, "----------------------\n");
	
	/*
	for (i = 0; i < 5; i++)	//5X5 Çà¿­À» Ãâ·ÂÇÏ±â À§ÇÑ Çà ¹Ýº¹
	{
		for (j = 0; j < 5; j++)	//5X5 Çà¿­À» Ãâ·ÂÇÏ±â À§ÇÑ ¿­ ¹Ýº¹
			if (bingo[(i * 5) + j] == 35)	//¸¸¾à ÇöÀç Ãâ·ÂÇÒ ¼ýÀÚ°¡ Ã¼Å©µÈ °ÍÀÌ¸é
				printf(1, "%c #", 5);	//Ä­ ¸ð¾ç°ú #À» Ãâ·ÂÇÑ´Ù. (¦¢ # ÀÌ·± ¸ð¾ç)
			else	//¾Æ´Ñ °æ¿ì Ä­ ¸ð¾ç°ú ÇØ´ç ¼ýÀÚ¸¦ Ãâ·ÂÇÑ´Ù.(2ÀÚ¸® Â÷Áö = %2d) (¦¢ 3 ÀÌ·± ¸ð¾ç)
				printf(1, "%c%2d", 5, bingo[(i * 5) + j]);
		printf(1, "%c\n", 5);	//ÇÑ ÁÙÀÇ ³¡ ¹®ÀÚ¸¦ Ãâ·Â ÇÑ µÚ¿¡ °³ÇàÇÑ´Ù.(¦¢ ÀÌ°Í)
		if (i != 4)	//¸¶Áö¸· ÇàÀÌ ¾Æ´Ñ µ¿¾È¿¡´Â °è¼Ó Áß°£ ÁÙÀ» Ãâ·ÂÇÑ´Ù. (¦§ ¦¡ ¦« ¦© ÀÌ·± ¸ð¾çµé)
			printf(1, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 25, 6, 6, 16, 6, 6, 16, 6, 6, 16, 6, 6, 16, 6, 6, 23);
	}
	*/
	//¸Ç ¹ØÁÙ Ä­À» ±×·ÁÁØ´Ù.
	
	/*
	while (1) 
	{
		printf("1. bingo start\n");
		printf("2. record\n");
		printf("3. exit\n");
		
		scanf_s("%d", &menu); 
		//get으로 바꿔서 if문 돌린다.... 
		switch (menu) 
		{
		case 1:
			bingoGameStart(record);
			break;
		case 2:
			printRecord(record);
			break;
		case 3:
			return 0;
		default:
			break;
		}
		system("pause"); 
		system("cls"); 
	}
	return 0;
	*/
	exit();
}









