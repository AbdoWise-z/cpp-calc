#include <iostream>
#include "MathUtils.h"
#include <cmath>

long double factorial(int x);
long double ePow(long double x , int accuracy);
long double intPow(long double x , int b);
const bool debug = false;

using namespace std;

char* supchar(const char* i_in , int start , int end){
    char* out = new char[end - start];
    for (int i = start; i < end; ++i) {
        out[i - start] = *(i + i_in);
    }
    return out;
}

void trim(string* str){
    size_t endpos = str->find_last_not_of(" ");
    size_t startpos = str->find_first_not_of(" ");
    if (startpos != std::string::npos){
        *str = str->substr(startpos);
        endpos -= startpos;
    }
    if (endpos >= 0){
        *str = str->substr(0 , endpos + 1);
    }
}

string fix_string(string* str){
    string out;
    for (char c : *str) {
        if (c == ' ')
            c = '_';
        out += c;
    }
    return out;
}


int main() {


    char in[360];

    cout << "Supported functions are : " << endl;
    cout << "      sin(a) , cos(a) , tan(a) , sec(a) , csc(a) , cot(a)" << endl
         << "      asin(a) , acos(a) , atan(a) , asec(a) , acsc(a) , acot(a)" << endl
         << "      sinh(a) , cosh(a) , tanh(a) , sech(a) , csch(a) , coth(a)" << endl
         << "      sgn(a) , abs(a) , log(b,l) , exp(a) , pow(base,power)" << endl
         << "      sqrt(a) , cbrt(a) , rand(to) , rand(from,to) , rand(from,to,seed)" << endl
         << "      deg(angle_in_radians) , rad(angle_in_degrees)" << endl << endl;

    cout << "Supported operations are : + , - , * , / , ( , ) , ^ " << endl << endl;

    cout << "Constants PI , e , DEG_TO_RAD , RAD_TO_DEG" << endl << endl;

    cout << "Commands : var_name = var_value" << endl;
    cout << "           expression" << endl;
    cout << "           exit" << endl << endl;



    cout << "Made by Abdo Mohamed (fb/AbdoWise)" << endl;
    cout << "Ver (1.0)" << endl << endl;

    MathInit();
    int size , equality_count;

    while(true) {
        cout << ">>> ";
        cout.flush();

        cin.getline(in, 360);
        size = cin.gcount();
        size--;//the last char is '\n'

        if (size <= 0)
            continue;

        if (in[0] == 'e' && in[1] == 'x' && in[2] == 'i' && in[3] == 't') {
            break;
        }

        //its not official but leave it .. why not ?
        if (in[0] == 'd' && in[1] == 'e' && in[2] == 'f' && in[3] == ' '){
            bool prev_usage = true;
            bool do_set = true;

            for (int i = 4; i < size; ++i) {
                if (in[i] == ' '){

                    if (!(i - 4 > 0 && size - i - 1 > 0)){
                        break;
                    }

                    string name;
                    char* n_char = supchar(in , 4 , i);

                    for (int j = 4; j < i - 4; ++j) {
                        char ch = n_char[j];
                        if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_'))){
                            prev_usage = false;
                            do_set = false;
                            cout << "Syntax Error :" << n_char << " is not a valid variable name" << endl;
                            break;
                        }
                    }

                    if (!do_set)
                        break;

                    name.append(n_char);

                    char* v_char = supchar(in , i + 1 , size);
                    long double d = eval(v_char , size - i - 1);
                    setVariable(name , d);

                    cout << name << " = " << d << endl;
                    prev_usage = false;
                    break;
                }
            }
            if (prev_usage) {
                cout << "Usage: def name value" << endl;
            }else{
                continue;
            }
        }

        equality_count = 0;
        for (int i = 0; i < size; ++i) {
            if (in[i] == '=')
                equality_count ++;
        }

        if (equality_count > 1){
            cout << "Syntax Error : more than one equality sign" << endl;
        }

        if (equality_count == 1){
            bool do_set = true;
            for (int i = 0; i < size; ++i) {
                if (in[i] == '='){

                    if (size - i - 1 <= 0){
                        cout << "Syntax Error : Empty expression" << endl;
                        break;
                    }

                    string name;
                    char* n_char = supchar(in , 0 , i);

                    for (int j = 0; j < i; ++j) {
                        char ch = n_char[j];
                        if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_') || (ch == ' '))){
                            do_set = false;
                            cout << "Syntax Error : " << n_char << " is not a valid variable name" << endl;
                            break;
                        }
                    }

                    if (!do_set)
                        break;

                    name.append(n_char);
                    trim(&name);
                    name = fix_string(&name);

                    char* v_char = supchar(in , i + 1 , size);
                    long double d = eval(v_char , size - i - 1);
                    setVariable(name , d);

                    cout << name << " = " << d << endl;
                    break;
                }
            }
        }else {
            long double d = eval(in, size);
            cout << d << endl;
        }

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



