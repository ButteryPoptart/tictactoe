#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// helper functions
void intro_text();
void reset_board();
void display_gameboard();
void validate_choice();
void evaluate_tie();
void evaluate_win();
void reset_game();

// params
vector<char> board;
int turn = 0;
char player;
bool tie = 0;
bool win = 0;
char champ;
int x_wins = 0;
int o_wins = 0;
char continue_choice = 'y';
int move_choice;

// main
int main() {
	intro_text();
	while (tolower(continue_choice) == 'y') {
		reset_board();
		display_gameboard();
		while (!win && !tie) {
			player = (turn % 2 == 0) ? 'X' : 'O'; // determine player turn
			validate_choice();
			board[move_choice - 1] = player; // mark move on board
			display_gameboard();
			evaluate_tie();
			evaluate_win();
			turn++; // switch turns
		}
		reset_game();
	}
	return 0;
}

void intro_text() {
	cout << "Tic-Tac-Toe!\n\n"
		<< "Rules: X starts first! Type 1-9 to input your move! The game will automatically alternate turns.\n"
		<< "This is the gameboard. It is sorted like a numpad: \n\n"
		<< "7  |  8  |  9\n"
		<< "4  |  5  |  6\n"
		<< "1  |  2  |  3\n"
		<< "\nThree X's or O's wins!\n"
		<< "Let's Begin!\n";
}

void reset_board() {
	board.clear();
	for (int i = 0; i <= 8; i++) {
		board.push_back('-');
	}
}

void display_gameboard() {
	cout << '\n' << board[6] << "  |  " << board[7] << "  |  " << board[8] << '\n'
		<< board[3] << "  |  " << board[4] << "  |  " << board[5] << '\n'
		<< board[0] << "  |  " << board[1] << "  |  " << board[2] << "\n\n";
}

void validate_choice() {
	while (true) {
		// validate data type
		while (true) {
			cout << player << ", it is your turn! Choose a place (1-9): ";
			if (cin >> move_choice) {
				break;
			}
			else {
				cout << "\nPlease enter a position 1-9!\n\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		// validate legal move
		if (move_choice < 1 || move_choice > 9) {
			cout << "\nPlease choose a possible section of the board!\n\n";
			continue;
		}
		else if (board[move_choice - 1] != '-') {
			cout << "\nSelect an unoccupied section of the board!\n\n";
			continue;
		}
		else {
			break;
		}
	}
}

void evaluate_tie() {
	int tie_check = 0;
	for (int i = 0; i <= 8; i++) {
		if (board[i] != '-') {
			tie_check++;
		}
	}
	if (tie_check == 9) {
		tie = 1;
	}
	else {
		tie_check = 0;
	}
}

void evaluate_win() {
	if ((board[0] == player && board[1] == player && board[2] == player) || (board[3] == player && board[4] == player && board[5] == player) || (board[6] == player && board[7] == player && board[8] == player) ||
		(board[0] == player && board[3] == player && board[6] == player) || (board[1] == player && board[4] == player && board[7] == player) || (board[2] == player && board[5] == player && board[8] == player) ||
		(board[0] == player && board[4] == player && board[8] == player) || (board[2] == player && board[4] == player && board[6] == player)) {
		win = 1;
		champ = player;
		(champ == 'X') ? x_wins++ : o_wins++;
	}
}

void reset_game() {
	// explain game reset
	if (win == 1) {
		cout << champ << " is victorious!\n";
	}
	else if (tie == 1) {
		cout << "There are no more possible moves! Tie game :/\n";
	}

	cout << "SCORE -> X: " << x_wins << "   O: " << o_wins;
	turn = 0;
	tie = 0;
	win = 0;
	cout << "\nPlay another game? (y/n): ";
	cin >> continue_choice;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}