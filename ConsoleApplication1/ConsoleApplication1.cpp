// Игра 2048 рус.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;
int board[4][4];
//направление для строки и столбца
int dirLine[] = { 1,0,-1,0 };
int dirColumn[] = { 0,1,0,-1 };

//случайные числа
pair<int, int> generateUnoccupiedPosition() {
	int occupied = 1, line, column;
	while (occupied) {
		line = rand() % 4;
		column = rand() % 4;
		if (board[line][column] == 0)
			occupied = 0;
	}
	return make_pair(line, column);
}

//добавить
void addPiece() {
	pair<int, int> pos = generateUnoccupiedPosition();
	board[pos.first][pos.second] = 2;
}


void newGame() {
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)

			board[i][j] = 0;
	addPiece();

}
//Меню доска
void printUI() {
	system("cls");
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			if (board[i][j] == 0)
				cout << setw(4) << ".";
			else
				cout << setw(4) << board[i][j];
		cout << "\n";
	}
	cout << "n:new game, w: up, s: down, d: right, a: left, q: quit\n";
}
//Ход
bool canDoMove(int line, int column, int nextLine, int nextColumn) {
	if (nextLine < 0 || nextColumn < 0 || nextLine >= 4 || nextColumn >= 4
		|| (board[line][column] != board[nextLine][nextColumn] && board[nextLine][nextColumn] != 0))
		return false;
	return true;
}
//приминения направлении 
void applyMove(int direction) {
	int startLine = 0, startColumn = 0, lineStep = 1, columnStep = 1;
	if (direction == 0) {
		startLine = 3;
		lineStep = -1;
	}
	if (direction == 1) {
		startColumn = 3;
		columnStep = -1;
	}
	int movePossible, canAddPiece = 0;
	do {
		movePossible = 0;
		for (int i = startLine; i >= 0 && i < 4; i += lineStep)
			for (int j = startColumn; j >= 0 && j < 4; j += columnStep) {
				int nextI = i + dirLine[direction], nextJ = j + dirColumn[direction];

				if (board[i][j] && canDoMove(i, j, nextI, nextJ)) {
					board[nextI][nextJ] += board[i][j];
					board[i][j] = 0;
					movePossible = canAddPiece = 1;
				}
			}

	} while (movePossible);
	if (canAddPiece)
		addPiece();
}

int main()
{
	//направление 
	char comandToDir[128];
	comandToDir['s'] = 0;
	comandToDir['d'] = 1;
	comandToDir['w'] = 2;
	comandToDir['a'] = 3;
	newGame();
	while (true) {
		printUI();
		char command;
		cin >> command;
		if (command == 'n')
			newGame();
		else if (command == 'q')
			break;
		else {
			//текущее направление
			int currentDirection = comandToDir[command];
			applyMove(currentDirection);
		}
	}

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
                                             