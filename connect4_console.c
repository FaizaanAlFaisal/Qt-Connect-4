#include <stdio.h>
#include <stdlib.h>


int board[8][8] = { 0 };  //0 = empty spot, 1 = p1 piece, 2 = p2 piece

int col0_pos = 7, col1_pos = 7, col2_pos = 7, col3_pos = 7, col4_pos = 7, col5_pos = 7,
col6_pos = 7, col7_pos = 7; //which row is currently available on each column

int turnCount = 1;
int playerTurn = 1;
int columnSelected;
int whichWin=0;

void moves(int player, int column);
void togglePlayer();
int wincheck(int column);

void main() {
	
	int win, columnPicked;

	while (1) {

		printf("Player %d, please choose a column (0-7) to place a piece in: ", playerTurn);
		scanf_s("%d", &columnPicked);

		while (columnPicked < 0 || columnPicked > 7) {
				printf("Invaild column! Please pick a valid column from 0-7.\n");
				scanf_s("%d", &columnPicked);
		}

		moves(playerTurn, columnPicked);


		printf("\n\n");
		printf("Turn: %d\n", turnCount);
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				
				if (board[i][j] == 0) printf("0 ");
				else if (board[i][j] == 1) {
					printf("\033[0;31m");
					printf("# ");
					printf("\033[0m");
				}
				else if (board[i][j] == 2) {
					printf("\033[0;32m");
					printf("# ");
					printf("\033[0m");
				}
			}
			printf("\n");
		}

		win = wincheck(columnPicked);
		if (win == 1) {
			printf("\033[0;31m \tPlayer 1 has won!\n\033[0m");
			break;
		}
		if (win == 2) {
			printf("\033[0;32m \tPlayer 2 has won!\n\033[0m");
			break;
		}
		if (win == 3) {
			printf("The board is filled and the players have tied. \n");
			break;
		}

		togglePlayer();
		turnCount++;
		printf("\n\n\n\n");
	}
}


void moves(int player, int column) {

	//updates board state to place a "piece" in desired column, by desired player
	//uses global variables which save bottom most row available on each column to place a piece

	switch (column) {

		case 0:
			if (col0_pos > -1) {
				board[col0_pos][column] = player;
				--col0_pos;
			}
			break;


		case 1:
			if (col1_pos > -1) {
				board[col1_pos][column] = player;
				--col1_pos;
			}
			break;

		case 2:
			if (col2_pos > -1) {
				board[col2_pos][column] = player;
				--col2_pos;
			}
			break;


		case 3:
			if (col3_pos > -1) {
				board[col3_pos][column] = player;
				--col3_pos;
			}
			break;


		case 4:
			if (col4_pos > -1) {
				board[col4_pos][column] = player;
				--col4_pos;
			}
			break;


		case 5:
			if (col5_pos > -1) {
				board[col5_pos][column] = player;
				--col5_pos;
			}
			break;


		case 6:
			if (col6_pos > -1) {
				board[col6_pos][column] = player;
				--col6_pos;
			}
			break;


		case 7:
			if (col7_pos > -1) {
				board[col7_pos][column] = player;
				--col7_pos;
			}
			break;

		default:
			break;
	}
}

void togglePlayer() { //toggles playerTurn from 1 to 2, and 2 to 1

	if (playerTurn == 1) playerTurn = 2;
	else if (playerTurn == 2) playerTurn = 1;
}

int wincheck(int column) {
	
	int p1Count = 0, p2Count = 0;

	int row; //determine row on which piece was just placed
	switch (column) {
	
		case 0:
			row = col0_pos + 1;
			break;

		case 1:
			row = col1_pos + 1;
			break;

		case 2:
			row = col2_pos + 1;
			break;

		case 3:
			row = col3_pos + 1;
			break;

		case 4:
			row = col4_pos + 1;
			break;

		case 5:
			row = col5_pos + 1;
			break;

		case 6:
			row = col6_pos + 1;
			break;

		case 7:
			row = col7_pos + 1;
			break;
	}


	int minRowCheck = row, maxRowCheck = row, minColCheck = column, maxColCheck = column;

	//for a 4-in-a-row, we must check sequences of pieces in each diagonal, vertical and horizontal

	if (minRowCheck - 3 >= 0) minRowCheck -= 3; //ensure check values remain within board confines
	else minRowCheck = 0;

	if (maxRowCheck + 3 <= 7) maxRowCheck += 3;
	else maxRowCheck = 7;

	if (minColCheck - 3 >= 0) minColCheck -= 3;
	else minColCheck = 0;

	if (maxColCheck + 3 <= 7) maxColCheck += 3;
	else maxColCheck = 7;


	//using row and column, check two diagonals, horizontal and vertical for win/4 in a row
	
	//vertical win check:
	for (int rowCheck = minRowCheck; rowCheck <= maxRowCheck; rowCheck++) { 

		if (board[rowCheck][column] == 1) { //sequence counter
			p1Count++; //if check spot has 1, increment p1count
			p2Count = 0; //and set p2count to 0
		}
		if (board[rowCheck][column] == 2) {
			p2Count++; //if check spot has 2, increment p2count
			p1Count = 0; //and set p1count to 0
		}
		if (board[rowCheck][column] == 0) {
			p1Count = 0; //if spot has 0, set both p1 and p2 count to 0
			p2Count = 0;
		}
		if (turnCount == 28) {
			printf("vertical checks:\n");
			printf("p1: %d, p2: %d\n", p1Count, p2Count);
		}

		
		if (p1Count >= 4) { 
			printf("\n vertical win.\n");
			return 1; 
		} //if 4 have been connected, return 1 for p1 and 2 for p2
		if (p2Count >= 4) { 
			printf("\n vertical win.\n");
			return 2; }
	}

	p1Count = 0;
	p2Count = 0;

	//horizontal win check:
	for (int columnCheck = minColCheck; columnCheck <= maxColCheck; columnCheck++) {

		if (board[row][columnCheck] == 1) { 
			p1Count++;
			p2Count = 0;
		}
		if (board[row][columnCheck] == 2) {
			p2Count++;
			p1Count = 0;
		}
		if (board[row][columnCheck] == 0) {
			p1Count = 0;
			p2Count = 0;
		}

		if (turnCount == 28) {
			printf("horizontal checks:\n");
			printf("p1: %d, p2: %d\n", p1Count, p2Count);
		}

		if (p1Count >= 4) {
			printf("\n horizontal win.\n");
			return 1;
		} //if 4 have been connected, return 1 for p1 and 2 for p2
		if (p2Count >= 4) {
			printf("\n horizontal win.\n");
			return 2;
		}
	}

	p1Count = 0;
	p2Count = 0;


	int leftRowBLTR = row, rightRowBLTR = row, leftColBLTR = column, rightColBLTR = column; //Diagonal check var - bottom left to top right
	int leftRowTLBR = row, rightRowTLBR = row, leftColTLBR = column, rightColTLBR = column; //Diagonal check var - top left to bottom right
	int i = 0;

	//initialize the BLTR diagonal left side variable checks:
	while (leftRowBLTR < 7 && leftColBLTR > 0 && i < 3) {
		leftRowBLTR++;
		leftColBLTR--;
		i++;
	}
	i = 0;
	//initialize right-side BLTR variable checks:
	while (rightRowBLTR > 0 && rightColBLTR < 7 && i < 3) {
		rightRowBLTR--;
		rightColBLTR++;
		i++;
	}
	i = 0;
	//initialize left-side TLBR variable checks:
	while (leftRowTLBR > 0 && leftColTLBR > 0 && i < 3) {
		leftRowTLBR--;
		leftColTLBR--;
		i++;
	}
	i = 0;
	//initialize right-side TLBR variable checks:
	while (rightRowTLBR < 7 && rightColTLBR < 7 && i < 3) {
		rightRowTLBR++;
		rightColTLBR++;
		i++;
	}
	i = 0;

	//run check for 4 connected pieces for BLTR diagonal:
	for (int rowCheck = leftRowBLTR, colCheck = leftColBLTR; rowCheck >= rightRowBLTR && colCheck <= rightColBLTR; rowCheck--, colCheck++) {
		
		if (board[rowCheck][colCheck] == 1) {
			p1Count++;
			p2Count = 0;
		}
		if (board[rowCheck][colCheck] == 2) {
			p2Count++;
			p1Count = 0;
		}
		if (board[rowCheck][colCheck] == 0) {
			p1Count = 0;
			p2Count = 0;
		}
		if (turnCount == 28) {
			printf("bltr checks: \n");
			printf("p1: %d, p2: %d\n", p1Count, p2Count);
		}
		if (p1Count >= 4) {
			printf("\n bltr win.\n");
			printf("leftrow: %d \t", leftRowBLTR);
			printf("rightrow: %d \t", rightRowBLTR);
			printf("leftcol: %d \t", leftColBLTR);
			printf("rightcol: %d\n", rightColBLTR);
			printf("p2count: %d", p2Count);
			printf("p1count: %d", p1Count);
			return 1;
		} //if 4 have been connected, return 1 for p1 and 2 for p2
		if (p2Count >= 4) {
			printf("\n bltr win.\n");
			printf("leftrow: %d \t", leftRowBLTR);
			printf("rightrow: %d \t", rightRowBLTR);
			printf("leftcol: %d \t", leftColBLTR);
			printf("rightcol: %d\n", rightColBLTR);
			printf("p2count: %d", p2Count);
			printf("p1count: %d", p1Count);
			return 2;
		}
	}

	p1Count = 0;
	p2Count = 0;

	//run check for 4 connected pieces in TLBR diagonal:
	for (int rowCheck = leftRowTLBR, colCheck = leftColTLBR; rowCheck <= rightRowTLBR && colCheck <= rightColTLBR; rowCheck++, colCheck++) {

		if (board[rowCheck][colCheck] == 1) {
			p1Count++;
			p2Count = 0;
		}
		if (board[rowCheck][colCheck] == 2) {
			p2Count++;
			p1Count = 0;
		}
		if (board[rowCheck][colCheck] == 0) {
			p1Count = 0;
			p2Count = 0;
		}

		if (p1Count >= 4) {
			printf("\n tlbr win.\n");
			return 1;
		} //if 4 have been connected, return 1 for p1 and 2 for p2
		if (p2Count >= 4) {
			printf("\n tlbr win.\n");
			return 2;
		}
	}
	if (turnCount == 65) return 3;
	return 0; //return 0 if 4 have not been connected
}