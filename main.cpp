#include <iostream>
#include <iomanip>
#include <cmath>
#include <unistd.h>
#include "MathUtils.h"


long double factorial(int x);
long double ePow(long double x , int accuracy);
long double intPow(long double x , int b);
const bool debug = false;

using namespace std;


int main() {

    char in[360];

    cout << "Enter 'exit' to exit :)" << endl << endl;
    cout << "Supported functions are : " << endl;
    cout << "      sin(a) , cos(a) , tan(a) , sec(a) , csc(a) , cot(a)" << endl
         << "     asin(a) ,acos(a) ,atan(a) ,asec(a) ,acsc(a) ,acot(a)" << endl
         << "     sinh(a) ,cosh(a) ,tanh(a) ,sech(a) ,csch(a) ,coth(a)" << endl
         << "     sqrt(a) , cbrt(a) , rand(to) , rand(from,to) , rand(from,to,seed)" << endl
         << "     deg(angle_in_radians) , rad(angle_in_degrees)" << endl;
    cout << "Supported operations are : + , - , * , / , ( , ) , ^ " << endl << endl;

    cout << "Made by Abdo Mohamed (fb/AbdoWise)" << endl;
    cout << "Ver (1.0)" << endl << endl;

    while(true) {
        cout << "Enter Expression : ";
        cout.flush();
        int size;

        cin.getline(in, 360);
        size = cin.gcount();
        size--;//the last char is '\n'

        if (size == 4){
            if (in[0] == 'e' && in[1] == 'x' && in[2] == 'i' && in[3] == 't'){
                break;
            }
        }

        cout << "Input: " << in << endl;

        //cout << "size=" << size << endl;

        long double d = eval(in, size);

        cout << "Result = " << d << endl;
        cout << "-----------------------------------------------" << endl;
    }
    return 0;
}

long double factorial(int x){
    if (x == 0)
        return 1.0;

    long double sum = 1.0;

    for (int i = 0; i < x; ++i) {
        sum = sum * (i + 1.0);
    }

    return sum;
}

long double intPow(long double x , int b){
    long double out = 1;
    for (int i = 0; i < b; ++i) {
        out = out * x;
    }
    return out;
}

long double ePow(long double x , int accuracy){
    long double sum = 0;
    for (int i = 0; i < accuracy; ++i) {
        sum += intPow(x , i) / factorial(i);
        if (debug)
            std::cout << "(ePow) sum=" << sum << std::endl;
    }
    return sum;
}



