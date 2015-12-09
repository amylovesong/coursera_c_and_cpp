#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
// 在此处补充你的代码
    void operator=(const string & s){
    	int index = s.find("+", 0);
    	string real = s.substr(0, index);
    	string imag = s.substr(index+1, 1);
//    	cout << real << endl;
//    	cout << imag << endl;
    	r = atof(real.c_str());
    	i =atof(imag.c_str());
    }
};
int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}
