//tictactoe.cc – DO alter this file.  
//Add your functions above runGame().
//NOTE that I have commented out the functions so it will compile.  You
//MUST uncomment these as you complete them for the game to work and for
//testing.

#include <stdio.h>
#include "tictactoe.h"

void clearBoard(gameData_t* c)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			c -> board[i][j] = ' ';
		}
	}

	return;
}

void getPlayerInfo(gameData_t* g)
{
	printf("Player 1 enter your name: ");
	scanf("%s", g -> name1);
	printf("Player 1 enter your age: ");
	scanf("%d", &g -> age1);
	printf("\n");
	printf("Player 2 enter your name: ");
	scanf("%s", g -> name2);
	printf("Player 2 enter your age: ");
	scanf("%d", &g -> age2);
	return;
}

void printPlayerInfo(gameData_t x)
{
	printf("Player 1 is %s age %d and will be Xs\n", x.name1, x.age1);
	printf("Player 2 is %s age %d and will be 0s\n", x.name2, x.age2);
	return;
}

void printTurnHeader(gameData_t x, char c)
{
	for (int i = 0; i < 50; i++)
	{
		if (i != 49)
		{
			printf("-");
		}
		else
		{
			printf("-\n");
		}
	}

	if (c == 'X')
	{
		printf("---------- %s's Turn --------------------\n", x.name1);
		printf("---------- You are Xs --------------------\n");
	}
	else
	{
		printf("---------- %s's Turn --------------------\n", x.name2);
		printf("---------- You are Os --------------------\n");
	}
	
	for (int i = 0; i < 50; i++)
	{
		if (i != 49)
		{
			printf("-");
		}
		else
		{
			printf("-\n");
		}
	}
	
	return;
}

void printBoard(gameData_t x)
{
	printf("    C1  C2  C3\n");
	printf("R1  %c | %c | %c \n", x.board[0][0], x.board[0][1], x.board[0][2]);
	printf("   -----------\n");
	printf("R2  %c | %c | %c \n", x.board[1][0], x.board[1][1], x.board[1][2]);
	printf("   -----------\n");
	printf("R3  %c | %c | %c \n", x.board[2][0], x.board[2][1], x.board[2][2]);
	return;
}

void getMove(gameData_t *gameData, char character) 
{
	if (character == 'X') 
	{
		printf("%s, please enter your move in the form RXCY: ", gameData->name1);
	}
	else if (character == 'O') 
	{
		printf("%s, please enter your move in the form RXCY: ", gameData->name2);
	}

	char mv[5];
	scanf("%4s", mv);

	while ((mv[0] != 'r' && mv[0] != 'R') || (mv[2] != 'C' && mv[2] != 'c')) 
	{
		printf("Input must be in the form RxCy. Try again: ");
		mv[0] = '\0';
		scanf("%4s", mv);
	}

	while ((mv[1] < 49 || mv[1] > 51) || (mv[3] < 49 || mv[3] > 51)) 
	{
		printf("Row and column must be in the range 1 to 3. Try again: ");
		mv[0] = '\0';
		scanf("%4s", mv);
	}

	char r = mv[1];
	char c = mv[3];

	while ((gameData -> board[r-49][c-49] == 'X') || (gameData -> board[r-49][c-49] == 'O')) 
	{
		printf("That space is taken. Try again: ");
		mv[0] = '\0';
		scanf("%4s", mv);
		r = mv[1];
		c = mv[3];
	}

	gameData -> board[r-49][c-49] = character;
}

int checkWin(gameData_t x, char c)
{
	int won = 0;
	if (x.board[0][0] == c && x.board[0][1] == c && x.board[0][2] == c) 
	{
		won = 1;
	}
	else if (x.board[1][0] == c && x.board[1][1] == c && x.board[1][2] == c) 
	{
		won = 1;
	}
	else if (x.board[2][0] == c && x.board[2][1] == c && x.board[2][2] == c) 
	{
		won = 1;
	}
	else if (x.board[0][0] == c && x.board[1][0] == c && x.board[2][0] == c) 
	{
		won = 1;
	}
	else if (x.board[0][1] == c && x.board[1][1] == c && x.board[2][1] == c) 
	{
		won = 1;
	}
	else if (x.board[0][2] == c && x.board[1][2] == c && x.board[2][2] == c) 
	{
		won = 1;
	}
	else if (x.board[0][0] == c && x.board[1][1] == c && x.board[2][2] == c) 
	{
		won = 1;
	}
	else if (x.board[0][2] == c && x.board[1][1] == c && x.board[2][0] == c) 
	{
		won = 1;
	}

	return won;
}

int checkTie(gameData_t x)
{
	int flag;
	int spaces = 0;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(x.board[i][j] == ' ')
			{
				spaces ++;
			}
		}
	}   
	if (spaces > 0)
	{
		flag = 0;
	}
	else
	{
		flag = 1;
	}
	return flag;
}

void runGame() {

	gameData_t gameData;

	int win = 0;
	int tie = 0;  
	char turn = 'X';

	//Set board to all spaces.
	clearBoard(&gameData);

	//Get both players name and age
	getPlayerInfo(&gameData);

	//Show the player info
	printf("\n");
	printPlayerInfo(gameData);
	printf("\n");

	while (!win && !tie) {
		//int count = 0;

		printTurnHeader(gameData, turn); 
		printBoard(gameData);
		getMove(&gameData, turn);    

		//Check for win
		win = checkWin(gameData, turn);        
		if (win == 1) {
			printf("--------------------------------------------------\n");      
			if (turn == 'X') {        
				printf("---------- %s WINS! --------------------\n", gameData.name1);
			} else {        
				printf("---------- %s WINS! --------------------\n", gameData.name2);
			}
			printf("--------------------------------------------------\n");      
			printBoard(gameData);
			printf("\n");
		} else {
			tie = checkTie(gameData);        
			if (tie == 1) {
				printf("--------------------------------------------------\n");      
				printf("---------- TIE GAME! --------------------\n");
				printf("--------------------------------------------------\n");      
				printBoard(gameData);
			}
		}

		//Toggle turn so other player goes next.
		if (turn == 'X') turn = 'O';
		else turn = 'X';
	}
}






