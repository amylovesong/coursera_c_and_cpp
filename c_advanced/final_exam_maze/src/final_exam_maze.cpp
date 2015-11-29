/*
 * final_exam_maze.cpp
 *
 *  Created on: 2015年11月29日
 *      Author: sunxiaoling
 */

#include <iostream>
using namespace std;

void func(char maze[][101], int row, int col) {
	int S_x = 0, S_y = 0;
	int T_x = 0, T_y = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (maze[i][j] == 'S') {
				S_x = i;
				S_y = j;
			}
			if (maze[i][j] == 'T') {
				T_x = i;
				T_y = j;
			}
		}
	}
}

int main() {
	char maze[100][101];
	int n, m;
	cin >> n >> m;
//	cout << n << endl;
	cin.getline(maze[0], 101);
	for (int i = 0; i < n; i++) {
		cin.getline(maze[i], 101);
	}
//	cout << maze[2] << endl;
	func(maze, n, m);

	return 0;
}

