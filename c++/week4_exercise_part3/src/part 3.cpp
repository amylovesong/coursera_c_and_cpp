#include <iostream>
#include <cstring>
using namespace std;
// 在此处补充你的代码
class Array2 {
	int row, col;
//	int *pr[]; 定义数组时最好定长，即int *p[10]，如果不确定长度，就是用int **p
	int **pr;
public:
	Array2(int r = 0, int c = 0) :
			row(r), col(c) {
		if (row == 0 || col == 0) {
//			*pr = NULL;
			pr = NULL;
		} else {
			pr = new int *[row];
			for (int i = 0; i < row; i++) {
				pr[i] = new int[col];
			}
		}
	}
	~Array2() {
		if (pr) {
			for (int i = 0; i < row; i++) {
				delete[] pr[i];
			}
			delete[] pr;
		}
	}
	Array2 & operator=(Array2 & a) {
		if (pr == a.pr) {
			return *this;
		}
		if (!a.pr) { //a中的数组为空
			if (pr) {
				for (int i = 0; i < row; i++) {
					delete[] pr[i];
					pr[i] = NULL;
				}
				delete[] pr;
				pr = NULL;
			}
			row = 0;
			col = 0;
			return *this;
		}
		if (row < a.row || col < a.col) { // 当前对象的空间比要赋值的对象的空间小，需要重新分配
			if (pr) {
				for (int i = 0; i < row; i++) {
					delete[] pr[i];
				}
				delete[] pr;
			}
			pr = new int * [a.row];
			for (int i = 0; i < a.row; i++) {
				pr[i] = new int[a.col];
			}
		}
		for (int i = 0; i < a.row; i++) {
			memcpy(pr[i], a.pr[i], sizeof(int) * a.col);
		}
		row = a.row;
		col = a.col;

		return *this;
	}
	int & operator()(int i, int j) {
		return *(pr[i] + j);
	}
	int * operator[](int i) {
		return pr[i];
	}
};

int main() {
	Array2 a(3, 4);
	int i, j;
	for (i = 0; i < 3; ++i)
		for (j = 0; j < 4; j++)
			a[i][j] = i * 4 + j;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 4; j++) {
			cout << a(i, j) << ",";
		}
		cout << endl;
	}
	cout << "next" << endl;
	Array2 b;
	b = a;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 4; j++) {
			cout << b[i][j] << ",";
		}
		cout << endl;
	}
	return 0;
}
