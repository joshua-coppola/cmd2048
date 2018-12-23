#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

void display ( int  *data[4] ) {
	for ( int i = 0; i < 4; ++i ) {
		for ( int j = 0; j < 4; ++j ) {
			if(j != 0)
				printf("|");
			if(data[i][j] == 0)
				printf("\t");
			else
				printf("%d\t" , data[i][j] );
		}
		if(i != 3)
			printf("\n________________________________\n");
	}
}

int spawn ( int *data[4] ) {
	int done = 0;
	while ( done == 0 ) {
		int row = rand() % 4;
		int col = rand() % 4;
		if ( data[row][col] == 0 ) {
			data[row][col] = ((rand() % 2) + 1) * 2;
			++done;
		}
	}
}

int game_over_status ( int *data[4] ) {
	int matches = 0;
	for ( int i = 0; i < 3; ++i ) {
		for ( int j = 0; j < 4; ++j ) {
			if( data[i][j] == data[i+1][j] || data[i][j] == 0 )
				++matches;
		}
	}
	for ( int i = 0; i < 4; ++i ) {
		for ( int j = 0; j < 3; ++j ) {
			if( data[i][j] == data[i][j+1] || data[i][j] == 0 )
				++matches;
		}
	}
	if ( data[3][3] == 0 )
		++matches;
	if ( matches == 0 )
		return 1;
	return 0;
}

int user_input() {
	char input;
	int done = 0;
	while (done == 0) {
		input = getchar();
		if ( input == 'a' ) { //left
			++done;
			return 0;	
		}
		if ( input == 'e' ) { //right
			++done;
			return 1;	
		}
		if ( input == ',' ) { //up
			++done;
			return 2;	
		}
		if ( input == 'o' ) { //down
			++done;
			return 3;	
		}
	}
};

int left(int *board[4] ) {
	int changes = 0;
	for( int i = 0; i < 4; ++i) {
		if (board[i][0] == 0 && board[i][1] != 0){
			board[i][0] = board[i][1];
			board[i][1] = board[i][2];
			board[i][2] = board[i][3];
			board[i][3] = 0;
			++changes;
		}
		if (board[i][0] == 0 && board[i][1] == 0 && board[i][2] != 0){
			board[i][0] = board[i][2];
			board[i][1] = board[i][3];
			board[i][3] = 0;
			board[i][2] = 0;
			++changes;
		}
		if (board[i][0] == 0 && board[i][1] == 0 && board[i][2] == 0 && board[i][3] != 0){
			board[i][0] = board[i][3];
			board[i][3] = 0;
			++changes;
		}
		if (board[i][0] != 0 && board[i][1] == 0 && board[i][2] != 0){
			board[i][1] = board[i][2];
			board[i][2] = board[i][3];
			board[i][3] = 0;
			++changes;
		}
		if (board[i][0] != 0 && board[i][1] == 0 && board[i][2] == 0 && board[i][3] != 0){
			board[i][1] = board[i][3];
			board[i][3] = 0;
			++changes;
		}
		if (board[i][0] != 0 && board[i][1] != 0 && board[i][2] == 0 && board[i][3] != 0){
			board[i][2] = board[i][3];
			board[i][3] = 0;
			++changes;
		}
		if (board[i][0] != 0 && board[i][0] == board[i][1] && (board[i][2] == 0 && board[i][3] == 0 || board[i][2] != board[i][3] )) {
			board[i][0] *= 2;
			board[i][1] = board[i][2];
			board[i][2] = board[i][3];
			board[i][3] = 0;
			++changes;
		}
		if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][2] != 0 && board[i][2] == board[i][3] ) {
			board[i][0] *= 2;
			board[i][1] = (board[i][2]) * 2;
			board[i][2] = 0;
			board[i][3] = 0;
			++changes;
		}
		if (board[i][0] != 0 && board[i][1] != 0 && board[i][1] == board[i][2] && (board[i][3] == 0 || board[i][3] != 0)) {
			board[i][1] *= 2;
			board[i][2] = board[i][3];
			board[i][3] = 0;
			++changes;
		}
		if (board[i][0] != 0 && board[i][1] != 0 && board[i][2] != 0 && board[i][2] == board[i][3]) {
			board[i][2] *= 2;
			board[i][3] = 0;
			++changes;
		}
	}
	if( changes == 0 )
		return 1;
	return 0;
}

int right(int *board[4] ) {
	int changes;
	for( int i = 0; i < 4; ++i) {
		if (board[i][3] == 0 && board[i][2] != 0){
			board[i][3] = board[i][2];
			board[i][2] = board[i][1];
			board[i][1] = board[i][0];
			board[i][0] = 0;
			++changes;
		}
		if (board[i][3] == 0 && board[i][2] == 0 && board[i][1] != 0){
			board[i][3] = board[i][1];
			board[i][2] = board[i][0];
			board[i][0] = 0;
			board[i][1] = 0;
			++changes;
		}
		if (board[i][3] == 0 && board[i][2] == 0 && board[i][1] == 0 && board[i][0] != 0){
			board[i][3] = board[i][0];
			board[i][0] = 0;
			++changes;
		}
		if (board[i][3] != 0 && board[i][2] == 0 && board[i][1] != 0){
			board[i][2] = board[i][1];
			board[i][1] = board[i][0];
			board[i][0] = 0;
			++changes;
		}
		if (board[i][3] != 0 && board[i][2] == 0 && board[i][1] == 0 && board[i][0] != 0){
			board[i][2] = board[i][0];
			board[i][0] = 0;
			++changes;
		}
		if (board[i][3] != 0 && board[i][2] != 0 && board[i][1] == 0 && board[i][0] != 0){
			board[i][1] = board[i][0];
			board[i][0] = 0;
			++changes;
		}
		if (board[i][3] != 0 && board[i][3] == board[i][2] && (board[i][1] == 0 && board[i][0] == 0 || board[i][1] != board[i][0] )) {
			board[i][3] *= 2;
			board[i][2] = board[i][1];
			board[i][1] = board[i][0];
			board[i][0] = 0;
			++changes;
		}
		if (board[i][3] != 0 && board[i][3] == board[i][2] && board[i][1] != 0 && board[i][1] == board[i][2] ) {
			board[i][3] *= 2;
			board[i][2] = (board[i][1]) * 2;
			board[i][1] = 0;
			board[i][0] = 0;
			++changes;
		}
		if (board[i][3] != 0 && board[i][2] != 0 && board[i][2] == board[i][1] && (board[i][0] == 0 || board[i][0] != 0)) {
			board[i][2] *= 2;
			board[i][1] = board[i][0];
			board[i][0] = 0;
			++changes;
		}
		if (board[i][3] != 0 && board[i][2] != 0 && board[i][1] != 0 && board[i][1] == board[i][0]) {
			board[i][1] *= 2;
			board[i][0] = 0;
			++changes;
		}
	}
	if ( changes == 0 )
		return 1;
	return 0;
}

int up(int *board[4] ) {
	int changes = 0;
	for( int i = 0; i < 4; ++i) {
		if (board[0][i] == 0 && board[1][i] != 0){
			board[0][i] = board[1][i];
			board[1][i] = board[2][i];
			board[2][i] = board[3][i];
			board[3][i] = 0;
			++changes;
		}
		if (board[0][i] == 0 && board[1][i] == 0 && board[2][i] != 0){
			board[0][i] = board[2][i];
			board[1][i] = board[3][i];
			board[3][i] = 0;
			board[2][i] = 0;
			++changes;
		}
		if (board[0][i] == 0 && board[1][i] == 0 && board[2][i] == 0 && board[3][i] != 0){
			board[0][i] = board[3][i];
			board[3][i] = 0;
			++changes;
		}
		if (board[0][i] != 0 && board[1][i] == 0 && board[2][i] != 0){
			board[1][i] = board[2][i];
			board[2][i] = board[3][i];
			board[3][i] = 0;
			++changes;
		}
		if (board[0][i] != 0 && board[1][i] == 0 && board[2][i] == 0 && board[3][i] != 0){
			board[1][i] = board[3][i];
			board[3][i] = 0;
			++changes;
		}
		if (board[0][i] != 0 && board[1][i] != 0 && board[2][i] == 0 && board[3][i] != 0){
			board[2][i] = board[3][i];
			board[3][i] = 0;
			++changes;
		}
		if (board[0][i] != 0 && board[0][i] == board[1][i] && (board[2][i] == 0 && board[3][i] == 0 || board[2][i] != board[3][i] )) {
			board[0][i] *= 2;
			board[1][i] = board[2][i];
			board[2][i] = board[3][i];
			board[3][i] = 0;
			++changes;
		}
		if (board[0][i] != 0 && board[0][i] == board[1][i] && board[2][i] != 0 && board[2][i] == board[3][i] ) {
			board[0][i] *= 2;
			board[1][i] = (board[2][i]) * 2;
			board[2][i] = 0;
			board[3][i] = 0;
			++changes;
		}
		if (board[0][i] != 0 && board[1][i] != 0 && board[1][i] == board[2][i] && (board[3][i] == 0 || board[3][i] != 0)) {
			board[1][i] *= 2;
			board[2][i] = board[3][i];
			board[3][i] = 0;
			++changes;
		}
		if (board[0][i] != 0 && board[1][i] != 0 && board[2][i] != 0 && board[2][i] == board[3][i]) {
			board[2][i] *= 2;
			board[3][i] = 0;
			++changes;
		}
	}
	if( changes == 0 )
		return 1;
	return 0;
}

int down(int *board[4] ) {
	int changes = 0;
	for( int i = 0; i < 4; ++i) {
		if (board[3][i] == 0 && board[2][i] != 0){
			board[3][i] = board[2][i];
			board[2][i] = board[1][i];
			board[1][i] = board[0][i];
			board[0][i] = 0;
			++changes;
		}
		if (board[3][i] == 0 && board[2][i] == 0 && board[1][i] != 0){
			board[3][i] = board[1][i];
			board[2][i] = board[0][i];
			board[0][i] = 0;
			board[1][i] = 0;
			++changes;
		}
		if (board[3][i] == 0 && board[2][i] == 0 && board[1][i] == 0 && board[0][i] != 0){
			board[3][i] = board[0][i];
			board[0][i] = 0;
			++changes;
		}
		if (board[3][i] != 0 && board[2][i] == 0 && board[1][i] != 0){
			board[2][i] = board[1][i];
			board[1][i] = board[0][i];
			board[0][i] = 0;
			++changes;
		}
		if (board[3][i] != 0 && board[2][i] == 0 && board[1][i] == 0 && board[0][i] != 0){
			board[2][i] = board[0][i];
			board[0][i] = 0;
			++changes;
		}
		if (board[3][i] != 0 && board[2][i] != 0 && board[1][i] == 0 && board[0][i] != 0){
			board[1][i] = board[0][i];
			board[0][i] = 0;
			++changes;
		}
		if (board[3][i] != 0 && board[3][i] == board[2][i] && (board[1][i] == 0 && board[0][i] == 0 || board[1][i] != board[0][i] )) {
			board[3][i] *= 2;
			board[2][i] = board[1][i];
			board[1][i] = board[0][i];
			board[0][i] = 0;
			++changes;
		}
		if (board[3][i] != 0 && board[3][i] == board[2][i] && board[1][i] != 0 && board[1][i] == board[0][i] ) {
			board[3][i] *= 2;
			board[2][i] = (board[1][i]) * 2;
			board[1][i] = 0;
			board[0][i] = 0;
			++changes;
		}
		if (board[3][i] != 0 && board[2][i] != 0 && board[2][i] == board[1][i] && (board[0][i] == 0 || board[0][i] != 0)) {
			board[2][i] *= 2;
			board[1][i] = board[0][i];
			board[0][i] = 0;
			++changes;
		}
		if (board[3][i] != 0 && board[2][i] != 0 && board[1][i] != 0 && board[1][i] == board[0][i]) {
			board[1][i] *= 2;
			board[0][i] = 0;
			++changes;
		}
	}
	if( changes == 0 )
		return 1;
	return 0;
}

void turn( int *board[4] ) {
	spawn(board);
	if(game_over_status(board)) {
		system("clear");
		display(board);
		printf("\nGame Over\n");
		return;
	}
	int done = 0;
	while( done == 0) {
		system("clear");
		display(board);
		int direction = user_input();
		if (direction == 0){
			if(!left(board))
				++done;
		}
		if (direction == 1){
			if(!right(board))
				++done;
		}
		if (direction == 2){
			if(!up(board))
				++done;
		}
		if (direction == 3){
			if(!down(board))
				++done;
		}
	}
	turn(board);
};

int main() {
	int * grid[4];
	for ( int i = 0; i < 4; ++i ) {
		grid[i] = malloc(sizeof(int[4]));
	}
	srand(time(NULL));
	static struct termios oldt, newt;
	tcgetattr( STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON);
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);
	turn(grid);
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
	return 0;
}
