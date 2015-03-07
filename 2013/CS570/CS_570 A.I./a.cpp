#include <iostream>

using namespace std;

int main() {
int x = 5;
float f = 8.5;
float a[3] = {1.1, 1.2, 1.3};
float *fp1, *fp2;
fp1 = &f;

cout << "fp1: " << *fp1 << endl; 

fp2 = a;

cout << "fp2: " << *fp2 << endl;
cout << "fp2: " << fp2[0] << endl;
cout << "fp2: " << fp2[1] << endl;
cout << "fp2: " << fp2[2] << endl;


*fp1 = 4.4;
cout << "fp1: " << *fp1 << endl; 
cout << "f: " << f << endl; 



*fp2 = 8.5;
cout << "fp2: " << *fp2 << endl;
cout << "fp2: " << fp2[0] << endl;
cout << "fp2: " << fp2[1] << endl;
cout << "fp2: " << fp2[2] << endl;

cout << "a: " << *a << endl;
cout << "a: " << a[0] << endl;
cout << "a: " << a[1] << endl;
cout << "a: " << a[2] << endl;


fp1 = & fp2[1];
cout << "fp1: " << fp1 << endl;
cout << "fp2: " << fp2 << endl;

return 0;
}
