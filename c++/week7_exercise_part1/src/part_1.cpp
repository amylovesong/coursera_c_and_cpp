#include <iostream>
using namespace std;
// 在此处补充你的代码
template<class T>
class CArray3D {
	class CArray2D {
		T ** array;
		int length;
	public:
		CArray2D() {
			array = NULL;
			length = 0;
		}
		CArray2D(int m, int n) {
			length = m;
			array = new T *[length];
			for (int i = 0; i < length; i++) {
				array[i] = new T[n];
			}
		}
		~CArray2D() {
			for (int i = 0; i < length; i++) {
				if (array[i]) {
					delete[] array;
				}
			}
			if (array) {
				delete[] array;
			}
		}
		void setInfo(int m, int n) {
			length = m;
			array = new T *[length];
			for (int i = 0; i < length; i++) {
				array[i] = new T[n];
			}
		}
		T * operator[](int i) {
			return array[i];
		}
	};

	CArray2D * array;
	int length;
public:
	CArray3D(int l, int m, int n) {
		length = l;
		array = new CArray2D[length];
		for (int i = 0; i < length; i++) {
			array[i].setInfo(m, n);
		}
	}
	~CArray3D() {
		if (array) {
			delete[] array;
		}
	}
	CArray2D & operator[](int i) {
		return array[i];
	}
};

int main() {
	CArray3D<int> a(3, 4, 5);
	int No = 0;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 5; ++k)
				a[i][j][k] = No++;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 5; ++k)
				cout << a[i][j][k] << ",";
	return 0;
}
