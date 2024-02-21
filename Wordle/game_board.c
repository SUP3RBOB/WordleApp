#include "game_board.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define BACKSPACE 8
#define ENTER 13

GameBoard* CreateGameBoard() {
	GameBoard* board = malloc(sizeof(GameBoard));
	if (board == NULL) {
		fprintf(stderr, "Not enough memory to create game board\n");
		return NULL;
	}

	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			board->grid[i][j] = '0';
		}
	}

	board->currentRow = 0;
	board->currentColumn = 0;

	return board;
}

void SetCharacterAtCurrentPosition(GameBoard* gameBoard, char c) {
	int row = gameBoard->currentRow;
	int col = gameBoard->currentColumn;

	gameBoard->grid[col][row] = c;
}

char GetCharacterAtCurrentPosition(GameBoard* gameBoard) {
	int row = gameBoard->currentRow;
	int col = gameBoard->currentColumn;

	return gameBoard->grid[col][row];
}

bool NextRow(GameBoard* gameBoard) {
	if (gameBoard == NULL) {
		fprintf(stderr, "Cannot go to the next row, game board doesn't exist\n");
		return false;
	}

	gameBoard->currentRow++;
	gameBoard->currentColumn = 0;
	
	return true;
}

bool GetInputs(GameBoard* gameBoard) {
	if (gameBoard == NULL) {
		fprintf(stderr, "Unable to get keyboard input, game board doesn't exist\n");
		return false;
	}

	int keyInput = _getch();

	if (keyInput == ENTER) {
		NextRow(gameBoard);
		return true;
	}

	if (keyInput == BACKSPACE) {
		if (gameBoard->currentColumn > 0) {
			gameBoard->currentColumn--;
		}

		SetCharacterAtCurrentPosition(gameBoard, '0');

		RefreshBoard(gameBoard);
		return true;
	}

	if (gameBoard->currentColumn >= BOARD_WIDTH) {
		return true;
	}

	SetCharacterAtCurrentPosition(gameBoard, (char)keyInput);
	RefreshBoard(gameBoard);
	gameBoard->currentColumn++;

	return true;
}

void RefreshBoard(GameBoard* gameBoard) {
	system("cls");

	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			printf("%c", gameBoard->grid[j][i]);
		}
		printf("\n");
	}
}

bool DestroyGameBoard(GameBoard* gameBoard) {
	if (gameBoard == NULL) {
		fprintf(stderr, "Unable to free game board, game board doesn't exist\n");
		return false;
	}

	free(gameBoard);

	return true;
}
