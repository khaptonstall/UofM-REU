//============================================================================
// Name        : tic-tac-toe-minimax.cpp
// Author      : Kyle Haptonstall
// Version     : 1.0
// Copyright   :
// Description : Example of minimax w/ and w/o alpha-beta pruning in tic-tac-toe
//============================================================================

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>

using namespace std;

typedef pair<int,int> bestMove;
#define inf 1<<20
char board[9] = {'_','_','_','_','_','_','_','_','_'};

//Method declarations
bestMove minimax( char board[], bool maximizingPlayer);
bestMove alphaBeta(char board[], int alpha, int beta, bool maximizingPlayer);
vector<int> moves(char board[]);
int hasWon(char board[]);
void printBoard();



int main() {

	for(int i = 0; i < 9; i++){

		vector<int> movesLeft = moves(board);

		if(hasWon(board) == 10){
			cout << "You won!" << '\n';
			return 0;
		}
		else if(hasWon(board) == -10){
			cout << "The CPU has won! How sad." << '\n';
			return 0;
		}
		else if(hasWon(board) == 0 && movesLeft.empty()){
			cout << "Draw";
			return 0;
		}

		if(i % 2 == 0){ //Player 1

			//Block of code for user vs CPU
			int userInput;
			printBoard();

			cout << "Enter a position for your X (1-9): " << '\n';
			cin >> userInput;

			while (board[userInput - 1] != '_'){
				cout << "Enter a position that is not already taken." << '\n';
				cin >> userInput;
			}

			board[userInput - 1] = 'X';


			//Block of code for CPU vs. CPU
			//best currMax = minimax(board, true);
			//board[currMax.second] = 'X';
			//printBoard();

		}else{ //Player 2
			bestMove currMin = alphaBeta(board, -inf, inf, false);
			//bestMove currMin = minimax( board, false);
			board[currMin.second] = 'O';
			printBoard();
		}
	}
	return 0;
}


bestMove alphaBeta( char board[], int alpha, int beta, bool maximizingPlayer){
		int pos;
		int bestMax = -inf;
		int bestMin = inf;

		vector<int> movesLeft = moves(board);

		//Check for win/lose/draw state
		if(hasWon(board) == 10){
			return bestMove(10,-1); //X's wins
		}else if(hasWon(board) == -10){
			return bestMove(-10,-1); //O's wins
		}else if(movesLeft.empty()){
			return bestMove(0,-1); //Draw
		}

		for(int i = 0; i < 9; i++){
			if(board[i] == '_'){
				if(maximizingPlayer){
					board[i] = 'X';
					int val = max(bestMax, alphaBeta(board,alpha, beta, false).first);
					board[i] = '_';
					if(val > bestMax){
						bestMax = val;
						pos = i;
					}

					alpha = max(val, alpha);
					//"Prune" branch
					if(beta <= alpha){
						break;
					}
				}else{
					board[i] = 'O';
					int val = min(bestMin, alphaBeta(board, alpha, beta, true).first);
					board[i] = '_';
					if(val < bestMin){
						bestMin = val;
						pos = i;
					}
					beta = min(val, beta);
					//Prune branch
					if(beta <= alpha){
						break;
					}
				}
			}
		}
		if(maximizingPlayer){
			return bestMove (alpha, pos);
		}else{
			return bestMove(beta, pos);
		}
}

bestMove minimax( char board[], bool maximizingPlayer){
	int pos;
	int bestMax = -inf;
	int bestMin = inf;
	vector<int> movesLeft = moves(board);

	//Check for win/lose/draw state
	if(hasWon(board) == 10){
		return bestMove(10,-1); //X's wins
	}else if(hasWon(board) == -10){
		return bestMove(-10,-1); //O's wins
	}else if(movesLeft.empty()){
		return bestMove(0,-1); //Draw
	}

	for(int i = 0; i < 9; i++){

		if(board[i] == '_'){
			if(maximizingPlayer){
				board[i] = 'X';
				int val = max(bestMax, minimax(board, false).first);
				board[i] = '_';

				if(val > bestMax){
					bestMax = val;
					pos = i;
				}
			}else{
				board[i] = 'O';
				int val = min(bestMin, minimax(board, true).first );
				board[i] = '_';
				if(val < bestMin){
					bestMin = val;
					pos = i;
				}
			}
		}
	}
	if(maximizingPlayer){
		return bestMove (bestMax, pos);
	}else{
		return bestMove(bestMin, pos);
	}
}

vector<int> moves(char board[]){
	vector<int> availMoves;
	for(int i = 0; i < 9; i++){
		if(board[i] == '_'){
			availMoves.push_back(i);
		}
	}
	return availMoves;
}

//Determine if there is a winning state on the board
int hasWon(char board[]){
	if((board[0] == 'X' && board[1] == 'X' && board[2] == 'X') ||
		   (board[3] == 'X' && board[4] == 'X' && board[5] == 'X') ||
		   (board[6] == 'X' && board[7] == 'X' && board[8] == 'X') ||
		   (board[0] == 'X' && board[3] == 'X' && board[6] == 'X') ||
		   (board[1] == 'X' && board[4] == 'X' && board[7] == 'X') ||
		   (board[2] == 'X' && board[5] == 'X' && board[8] == 'X') ||
		   (board[0] == 'X' && board[4] == 'X' && board[8] == 'X') ||
		   (board[2] == 'X' && board[4] == 'X' && board[6] == 'X')){
			return 10;
		}
	else if((board[0] == 'O' && board[1] == 'O' && board[2] == 'O') ||
		   (board[3] == 'O' && board[4] == 'O' && board[5] == 'O') ||
     	   (board[6] == 'O' && board[7] == 'O' && board[8] == 'O') ||
		   (board[0] == 'O' && board[3] == 'O' && board[6] == 'O') ||
		   (board[1] == 'O' && board[4] == 'O' && board[7] == 'O') ||
		   (board[2] == 'O' && board[5] == 'O' && board[8] == 'O') ||
		   (board[0] == 'O' && board[4] == 'O' && board[8] == 'O') ||
		   (board[2] == 'O' && board[4] == 'O' && board[6] == 'O')){
			return  -10;
	}else{
		return 0;
	}
}

void printBoard(){
		cout << "**************" << '\n';
		printf ("* %c | %c | %c * \n", board[0], board[1], board[2]);
		printf ("* %c | %c | %c * \n", board[3], board[4], board[5]);
		printf ("* %c | %c | %c * \n", board[6], board[7], board[8]);
		cout << "**************" << '\n' << '\n';
}
