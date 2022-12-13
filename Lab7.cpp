/*
Dakota Kunz
C++
Due: December 12th, 2022
Description: Create the game of battleships
*/
#include <iostream>
#include <iomanip>

using namespace std;
const int boardsize = 10; const int depth = 6;
typedef char board[boardsize][boardsize][depth];

//Precondition: Library iostream
//Postcondition: introduces the game
void header();

//Precondition: library iostream
//Postcondition: creates a 2D array using the water character
void ini(board Board);

//Precondition: libaray iostream, library iomanip
//Postcondition: Outputs teh actual grid that was creaded in ini()
void outputboard(board Board, int player);

//Precondition: library iostream
//Postcondition: allows placement of ships and validiates them
void uships(board Board, int& shipsize);

//Precondition: library iostream
//Postcondition: randomly selects ships for computer and places them
void cships(board Board);

//Precondition: library iostream
//Postcondition: user can guess a spot and will check if its a hit or micc
void guess(board board, int& player, bool& game);

//Precondition:library iostream
//Postcondition: computer is able to guess randomly and will check if its a hit or miss
void guessCom(board Board);

//Precondition: library iostream
//Postcondition: Schecks and tells user which ships have been destroyed
void gameStatus(board Board);

//Precondition: library iostream
//Postcondition: checks if all ships are destroyed and can end game
void gameOver(board Board, bool& game);

//Precondition:library iostream
//Postcondition: validates direction and places #
void ifprint(int& shipSize, int direction, board Board, int yPlacement, int xPlacement, int shipType);

int main()
{ //runs whole program
	int shipSize = 0;
	board Board;
	bool again = true;
	bool game = true;
	int player = 0;
	int yPlacementcom;

	header();

	do {
		ini(Board);
		uships(Board, shipSize);
		cships(Board);
		do {
			gameStatus(Board);
			guess(Board, player, game);
			gameOver(Board, game);
			if (!game) {
				break;
			}
			guessCom(Board);
			gameOver(Board, game);
			if (!game) {
				break;
			}
		} while (game);
	} while (again);

	return 0;
}

void gameOver(board Board, bool& game) {
	//will end game is ships are all gone

	int carrier = 0; int battleship = 0;
	int cruiser = 0; int submarine = 0;
	int destroyer = 0;

	int comcarrier = 0; int combattleship = 0;
	int comcruiser = 0; int comsubmarine = 0;
	int comdestroyer = 0;

	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (Board[y][x][4] == '5') {
				carrier++;
			}
			else if (Board[y][x][4] == '4') {
				battleship++;
			}
			else if (Board[y][x][4] == '3') {
				cruiser++;
			}
			else if (Board[y][x][4] == '2') {
				submarine++;
			}
			else if (Board[y][x][4] == '1') {
				destroyer++;
			}
		}
	}
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (Board[y][x][5] == '5') {
				comcarrier++;
			}
			else if (Board[y][x][5] == '4') {
				combattleship++;
			}
			else if (Board[y][x][5] == '3') {
				comcruiser++;
			}
			else if (Board[y][x][5] == '2') {
				comsubmarine++;
			}
			else if (Board[y][x][5] == '1') {
				comdestroyer++;
			}
		}
	}
	if (carrier == 0 && battleship == 0 && cruiser == 0
		&& submarine == 0 && destroyer == 0) {
		cout << "All ships destroyed. You lost!" << endl;
		game = false;
	}
	if (comcarrier == 0 && combattleship == 0 && comcruiser == 0
		&& comsubmarine == 0 && comdestroyer == 0) {
		cout << "You destroyed all their ships. You win!" << endl;
		game = false;
	}
}

void gameStatus(board Board) {
	//checks if ships are destroyed 

	int carrier = 0; int battleship = 0;
	int cruiser = 0; int submarine = 0;
	int destroyer = 0;

	int comcarrier = 0; int combattleship = 0;
	int comcruiser = 0; int comsubmarine = 0;
	int comdestroyer = 0;

	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (Board[y][x][4] == '5') {
				carrier++;
			}
			else if (Board[y][x][4] == '4') {
				battleship++;
			}
			else if (Board[y][x][4] == '3') {
				cruiser++;
			}
			else if (Board[y][x][4] == '2') {
				submarine++;
			}
			else if (Board[y][x][4] == '1') {
				destroyer++;
			}
		}
	}
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (Board[y][x][5] == '5') {
				comcarrier++;
			}
			else if (Board[y][x][5] == '4') {
				combattleship++;
			}
			else if (Board[y][x][5] == '3') {
				comcruiser++;
			}
			else if (Board[y][x][5] == '2') {
				comsubmarine++;
			}
			else if (Board[y][x][5] == '1') {
				comdestroyer++;
			}
		}
	}
	if (carrier == 0) {
		cout << "Carrier destroyed!" << endl;
	}
	if (battleship == 0) {
		cout << "Battleship destroyed!" << endl;
	}
	if (cruiser == 0) {
		cout << "Cruiser destroyed!" << endl;
	}
	if (submarine == 0) {
		cout << "Submarine destroyed!" << endl;
	}
	if (destroyer == 0) {
		cout << "Destroyer destroyed!" << endl;
	}
	cout << endl;
	if (comcarrier == 0) {
		cout << "Computer carrier destroyed!" << endl;
	}
	if (combattleship == 0) {
		cout << "Computer battleship destroyed!" << endl;
	}
	if (comcruiser == 0) {
		cout << "Computer cruiser destroyed!" << endl;
	}
	if (comsubmarine == 0) {
		cout << "Computer submarine destroyed!" << endl;
	}
	if (comdestroyer == 0) {
		cout << "Computer destroyer destroyed!" << endl;
	}
}

void guessCom(board Board) {
	//checks and validates random guesses
	int guessy;
	int guessx;
	bool valid = false;
	srand(time(NULL));
	do {
		do {
			guessx = rand() % 10 + 1;
			if (guessx <= 10 && guessx > 0) {
				valid = true;
				guessx -= 1;
			}
		} while (!valid);
		valid = false;
		do {
			guessy = rand() % 10 + 1;
			if (guessy <= 10 && guessy > 0) {
				valid = true;
				guessy -= 1;
			}
		} while (!valid);
		valid = false;
		if ((Board[guessy][guessx][2] == 'M') || (Board[guessy][guessx][2] == 'H')) {
			valid = false;
		}
		else {
			valid = true;
		}
	} while (!valid);
	cout << "Computer : " << "X - " << guessx + 1 << " Y - " << guessy + 1 << endl;
	if (Board[guessy][guessx][1] == '#') {
		Board[guessy][guessx][2] = 'H';
		Board[guessy][guessx][1] = 'H';
		cout << "Hit!" << endl << endl;
	}
	else {
		Board[guessy][guessx][2] = 'M';
		Board[guessy][guessx][1] = 'M';
		cout << "Miss!" << endl << endl;
	}
	Board[guessy][guessx][4] = 'X';
}

void guess(board Board, int& player, bool& game) {
	//checks and validates user guesses
	int guessy;
	int guessx;
	bool valid = false;

	outputboard(Board, player);

	cout << endl << "Your turn" << endl;
	do {
		do {
			cout << "User X axis : ";
			cin >> guessx;
			if (guessx == 1234) {
				player = 2;
			}
			else if (guessx == 4321) {
				player = 0;
			}
			if (guessx <= 10 && guessx > 0) {
				valid = true;
				guessx -= 1;
			}
			else if (guessx != 9999) {
				cout << "Invalid" << endl;
			}
		} while (!valid);
		valid = false;
		do {
			if (guessx != 9999) {
				cout << "User Y axis : ";
				cin >> guessy;
			}
			else {
				valid = true;
			}
			if (guessy <= 10 && guessy > 0) {
				valid = true;
				guessy -= 1;
			}
			else {
				cout << "Invalid" << endl;
			}
		} while (!valid);
		valid = false;
		if (guessx == 9999) {
			valid = true;
		}
		else if ((Board[guessy][guessx][0] == 'M') || (Board[guessy][guessx][0] == 'H')) {
			cout << "Invalid" << endl;
		}
		else {
			valid = true;
		}
	} while (!valid);
	if (guessx != 9999) {
		if (Board[guessy][guessx][3] == '#') {
			Board[guessy][guessx][0] = 'H';
			Board[guessy][guessx][3] = 'H';
			cout << "Hit!" << endl << endl;
		}
		else {
			Board[guessy][guessx][0] = 'M';
			Board[guessy][guessx][3] = 'M';
			cout << "Miss!" << endl << endl;
		}
	}
	if (guessx == 9999) {
		guessx = 1;
		guessy = 1;
	}
	Board[guessy][guessx][5] = 'X';
}

void cships(board Board) {
	//placement of computer ships
	char shipType;
	int shipSize;
	int yPlacementcom;
	int yPlacement = 0;
	int xPlacement;
	int direction;

	cout << "Computer is placing their ships now..." << endl;

	for (int c = 0; c < 5; c++) {
		bool print = true;
		switch (c) {
		case 0:
			shipSize = 5;
			shipType = '5';
			break;
		case 1:
			shipSize = 4;
			shipType = '4';
			break;
		case 2:
			shipSize = 3;
			shipType = '3';
			break;
		case 3:
			shipSize = 3;
			shipType = '2';
			break;
		case 4:
			shipSize = 2;
			shipType = '1';
			break;
		}
		srand(time(NULL));

		xPlacement = rand() % 10 + 1;
		yPlacementcom = rand() % 10 + 1;
		direction = rand() % 4 + 1;

		for (int x = 0; x < shipSize; x++) {
			if (direction == 1) {
				if (Board[yPlacementcom - 1][xPlacement - 1 - x][3] == '#') {
					c--;
					print = false;
				}
			}
			else if (direction == 2) {
				if (Board[yPlacementcom - 1][xPlacement - 1 + x][3] == '#') {
					c--;
					print = false;
				}
			}
			else if (direction == 3) {
				if (Board[yPlacementcom - 1 + x][xPlacement - 1][3] == '#') {
					c--;
					print = false;
				}
			}
			else if (direction == 4) {
				if (Board[yPlacementcom - 1 - x][xPlacement - 1][3] == '#') {
					c--;
					print = false;
				}
			}
			else {
				if (Board[yPlacementcom - 1][xPlacement - 1 + x][3] == '#') {
					c--;
					print = false;
				}
			}
			if (!print) {
				break;
			}
		}
		for (int x = 0; x < shipSize; x++) {
			if (direction == 1) {
				if (xPlacement - 1 - x < 0) {
					c--;
					print = false;
				}
			}
			else if (direction == 2) {
				if (xPlacement - 1 + x > 9) {
					c--;
					print = false;
				}
			}
			else if (direction == 3) {
				if (yPlacementcom - 1 + x > 9) {
					c--;
					print = false;
				}
			}
			else if (direction == 4) {
				if (yPlacementcom - 1 - x < 0) {
					c--;
					print = false;
				}
			}
			else {
				if (xPlacement - 1 + x > 9) {
					c--;
					print = false;
					break;
				}
			}
			if (!print) {
				break;
			}
		}
		if (print) {
			ifprint(shipSize, direction, Board, yPlacement, xPlacement, shipType);
		}
	}
}

void uships(board Board, int& shipsize) {
	//placement of user ships
	char shipType;
	int shipSize; int yPlacement;
	int xPlacement; int direction;


	for (int c = 0; c < 5; c++) {
		bool print = true;
		outputboard(Board, 0);
		switch (c) {
		case 0:
			shipSize = 5;
			shipType = '5';
			cout << endl << "Place carrier (5 spaces) " << endl;
			break;
		case 1:
			shipSize = 4;
			shipType = '4';
			cout << endl << "Place battleship (4 spaces) " << endl;
			break;
		case 2:
			shipSize = 3;
			shipType = '3';
			cout << endl << "Place cruiser (3 spaces) " << endl;
			break;
		case 3:
			shipSize = 3;
			shipType = '2';
			cout << endl << "Place submarine (3 spaces) " << endl;
			break;
		case 4:
			shipSize = 2;
			shipType = '1';
			cout << endl << "Place destroyer (2 spaces) " << endl;
			break;
		}
		cout << "X axis : ";
		cin >> xPlacement;
		if (xPlacement > 10 || xPlacement <= 0) {
			cout << "Invalid" << endl;
			c--;
			continue;
		}
		cout << "Y axis : ";
		cin >> yPlacement;
		if (yPlacement > 10 || yPlacement <= 0) {
			cout << "Invalid" << endl;
			c--;
			continue;
		}
		cout << "Direction , Left 1 , Right 2 , Down 3 , Up 4 : ";
		cin >> direction;
		for (int x = 0; x < shipSize; x++) {
			if (direction == 1) {
				if (Board[yPlacement - 1][xPlacement - 1 - x][1] == '#') {
					cout << "Invalid" << endl;
					c--;
					print = false;
				}
			}
			else if (direction == 2) {
				if (Board[yPlacement - 1][xPlacement - 1 + x][1] == '#') {
					cout << "Invalid" << endl;
					c--;
					print = false;
				}
			}
			else if (direction == 3) {
				if (Board[yPlacement - 1 + x][xPlacement - 1][1] == '#') {
					cout << "Invalid" << endl;
					c--;
					print = false;
				}
			}
			else if (direction == 4) {
				if (Board[yPlacement - 1 - x][xPlacement - 1][1] == '#') {
					cout << "Invalid" << endl;
					c--;
					print = false;
				}
			}
			else {
				if (Board[yPlacement - 1][xPlacement - 1 + x][1] == '#') {
					cout << "Invalid" << endl;
					c--;
					print = false;
				}
			}
		}
		if (!print) {
			break;
		}
		for (int x = 0; x < shipSize; x++) {
			if (direction == 1) {
				if (xPlacement - 1 - x < 0) {
					cout << "Invalid" << endl;
					c--;
					print = false;
				}
			}
			else if (direction == 2) {
				if (xPlacement - 1 + x > 9) {
					cout << "Invalid" << endl;
					c--;
					print = false;
				}
			}
			else if (direction == 3) {
				if (yPlacement - 1 + x > 9) {
					cout << "Invalid" << endl;
					c--;
					print = false;
				}
			}
			else if (direction == 4) {
				if (yPlacement - 1 - x < 0) {
					cout << "Invalid" << endl;
					c--;
					print = false;
				}
			}
			if (!print) {
				break;
			}
		}
		if (print) {
			ifprint(shipSize, direction, Board, yPlacement, xPlacement, shipType);
		}
	}
}

void ifprint(int& shipSize, int direction, board Board, int yPlacement, int xPlacement, int shipType) 
{//Outputs hashtags
	for (int x = 0; x < shipSize; x++) {
		if (direction == 1) {
			Board[yPlacement - 1][xPlacement - 1 - x][1] = '#';
			Board[yPlacement - 1][xPlacement - 1 - x][4] = shipType;
		}
		else if (direction == 2) {
			Board[yPlacement - 1][xPlacement - 1 + x][1] = '#';
			Board[yPlacement - 1][xPlacement - 1 + x][4] = shipType;
		}
		else if (direction == 3) {
			Board[yPlacement - 1 + x][xPlacement - 1][1] = '#';
			Board[yPlacement - 1 + x][xPlacement - 1][4] = shipType;
		}
		else if (direction == 4) {
			Board[yPlacement - 1 - x][xPlacement - 1][1] = '#';
			Board[yPlacement - 1 - x][xPlacement - 1][4] = shipType;
		}
		else {
			Board[yPlacement - 1][xPlacement - 1 + x][1] = '#';
			Board[yPlacement - 1][xPlacement - 1 + x][4] = shipType;
		}
	}
}

void header()
{
	cout << "This is BATTLESHIP!" << endl;
}

void ini(board Board) {//Initiates Board
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			for (int z = 0; z < 6; z++) {
				Board[y][x][z] = '~';
			}
		}
	}
}

void outputboard(board Board, int player) {//Outputs base Board as water symbol
	for (int z = 0; z < player + 2; z++) {
		cout << endl;
		cout << "   1 2 3 4 5 6 7 8 9 10 X" << endl;
		for (int y = 0; y < 10; y++) {
			cout << setw(2) << y + 1;
			cout << ' ';
			for (int x = 0; x < 10; x++) {
				cout << Board[y][x][z] << ' ';
			}
			cout << endl;
		}
	}
}