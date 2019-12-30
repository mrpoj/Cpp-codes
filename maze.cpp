#include<bits/stdc++.h>
#include <windows.h>
#include <conio.h>

#define F first
#define S second
#define Pii pair<int, int>

using namespace std;

const int max_size = 55;

class Maze {
	
	bool mark [max_size * 2][max_size * 2];
	char maze [max_size * 2][max_size * 2];
	Pii player;
	
	void gotoxy (int x, int y) {
		static HANDLE h = NULL;
		if (!h) 
			h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD c = {x, y};
		SetConsoleCursorPosition(h, c);
	}
	
	// Print divar haye maze
	void printWalls (int size) {
		for (int i = 0; i < size; i++) {
			maze [0][i] = '#';
			maze [size * 2][i] = '#';
			mark[0][1] = true;
			mark[size * 2][i] = true;
		}	
		for (int i = 0; i <= size * 2; i++) {
			maze[i][0] = '#';
			maze[i][size - 1] = '#';
			mark[i][0] = true;
			mark[i][size - 1] = true;
		}
		for (int i = 0; i <= size * 2; i++)
			for (int j = 0; j < size * 2; j++)
				if (maze[i][j] == '#') {
					gotoxy (i, j);
					cout << char(254u);
				}
	}

	// Sakhtane masire random ba estefade az algorithm DFS
	void buildPath  (int x, int y) {	
		if (maze[x][y] == 'E') return;
		mark[x][y] = true;
		int random = rand() % 11;
		if (random <= 4 && maze[x + 1][y] != '#') buildPath (x + 1, y);
		else if (random <= 7  && maze[x][y + 1] != '#') buildPath (x, y + 1);
		else if (random <= 9  && maze[x][y - 1] != '#') buildPath (x, y - 1);
		else if (maze[x - 1][y] != '#') buildPath (x - 1, y);
		else buildPath (x, y);
	}

	// Chap maze random
	void printField (int size) {
		buildPath (1, 1);
		buildPath (16,2);
		//buildPath (30,10);
		for (int i = 1; i <= size * 2; i++)
			for (int j = 1; j <= size * 2; j++) {
				if (!mark[i][j] && maze[i][j] != 'E') {
					int random = rand () % 5;
					if (random <= 1) {
						maze[i][j] = ' ';
						gotoxy (i, j);
						cout << ' ';
					}
					else if (random == 3) {
						maze[i][j] = '#';
						gotoxy (i, j);
						cout << char(254u);
					}
					else {
						maze[i][j] = 'B';
						gotoxy (i, j);
						cout << 'B';
					}		
				}
				else if (maze[i][j] == '#') break;
					
			}
	}
	bool winCheck (Pii player) {
		if (maze[player.F][player.S] == 'E') return true;
		return false;
	}
	bool bombCheck (pair<int, int> player) {
		if (maze[player.F][player.S] == 'B') return true;
		return false;
	}
	Pii movePlayer (Pii player, int d) {
		bool flag = false;
		int x = player.F, y = player.S;
		if (d == 72 && maze[x][y - 1] != '#') 
			y --, flag = true;
		else if (d == 80 && maze[x][y + 1] != '#')
			y ++, flag = true;
		else if (d == 77 && maze[x + 1][y] != '#')
			x ++, flag = true;
		else if (d == 75 && maze[x - 1][y] != '#')
			x --, flag = true;
		if (flag == true) {
			gotoxy (player.F, player.S);
			cout << ' ';
			gotoxy (x, y);
			cout << 'P';
		}
		Pii ret = {x, y};
		return ret;
	}
public:
	void execute(int _size) {
		int size = _size;
		system ("cls");
		player.F = 1;
		player.S = 1;
		gotoxy ((size * 2) - 1, size - 2);
		maze[(size * 2) - 1][size - 2] = 'E';
		cout << 'E';
		printWalls (size);
		printField (size);
		gotoxy (1, 1);
		maze [1][1] = 'P';
		cout << 'P';
		while (true) {
			int d = getch();
			player = movePlayer(player, d);
			if (winCheck (player) == true) {
				system("cls");
				cout << "You Won!!" << endl;
				return;
			}
			if (bombCheck (player)) {
				system("cls");
				cout << "Booom!!! You lost" << endl;
				return;
			}
		}
		gotoxy(0, size * 2 + 5);
	}
};


int main () {
	srand(time(NULL));	
	int n;
	Maze game;
	cout << "Welcome to maze game!" << endl;
	cout << "Enter the width of the maze (maximum is 50) : ";
	cin >> n;
	game.execute(n);
	return 0;
}
