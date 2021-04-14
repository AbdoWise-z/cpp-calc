//
// Created by Abdo Momahed (AbdoWise) on 2021-04-14
//
// currently supports : sqrt , cprt , sin , cos , tan , asin , acos , atan
//                      csc , sec , cot , acsc , asec , acot , sinh , cosh
//                      tanh , csch , sech , coth , rand , deg , rad
//
// was going to add variable support .. but I have to study integration
// this thing took me 1+ hour to code already
//


#include "MathUtils.h"

#include <iostream>
#include <cmath>


using namespace std;

static long double parseExpression();
static long double parseTerm();
static long double parseFactor();


static int pos = 0;
static char ch;

static char *i_in;
static int i_len;

static const char func_sqrt[] = {'s','q','r','t'};

static const char func_deg[] = {'d','e','g'};
static const char func_rad[] = {'r','a','d'};

#define DEG_TO_RAD  M_PI/180.0;
#define RAD_TO_DEG  180.0/M_PI;

static const char func_sin[] = {'s','i','n'};
static const char func_cos[] = {'c','o','s'};
static const char func_tan[] = {'t','a','n'};

static const char func_asin[] = {'a','s','i','n'};
static const char func_acos[] = {'a','c','o','s'};
static const char func_atan[] = {'a','t','a','n'};

static const char func_csc[] = {'c','s','c'};
static const char func_sec[] = {'s','e','c'};
static const char func_cot[] = {'c','o','t'};

static const char func_acsc[] = {'a','c','s','c'};
static const char func_asec[] = {'a','s','e','c'};
static const char func_acot[] = {'a','c','o','t'};

static const char func_cbrt[] = {'c','b','r','t'};

static const char func_sinh[] = {'s','i','n','h'};
static const char func_cosh[] = {'c','o','s','h'};
static const char func_tanh[] = {'t','a','n','h'};

static const char func_csch[] = {'c','s','c','h'};
static const char func_sech[] = {'s','e','c','h'};
static const char func_coth[] = {'c','o','t','h'};

static const char func_rand[] = {'r','a','n','d'};


//Char Array comparison function
//if both have the same elements .. then return true other wise false
static bool charequal(const char* a1 , const char* a2 , int s1 , int s2){
    if (s1 != s2)
        return false;
    for (int i = 0; i < s1; ++i) {
        if (*(a1 + i) != *(a2 + i))
            return false;
    }
    return true;
}


//copies a region of a char array to another char array
char* supchar(int start , int end){
    char* out = new char[end - start];
    for (int i = start; i < end; ++i) {
        out[i - start] = *(i + i_in);
    }
    return out;
}

//goes to the next char in the input
static void nextChar(){
    pos ++;
    if (pos < i_len)
        ch = *(i_in + pos);
    else
        ch = -1;

    //cout << "Char: " << ch << endl;

}

static bool eat(char c){
    while (ch == ' ') nextChar();
    if (ch == c){
        nextChar();
        return true;
    }
    return false;
}

static long double parseExpression(){
    //cout << "Start Expression" << endl;
    long double x = parseTerm();
    for (;;){
        if (eat('+')){
            x = x + parseTerm();
        } else if (eat('-')){
            x = x - parseTerm();
        }
        else return x;
    }
}

static long double parseTerm(){
    long double x = parseFactor();
    for (;;){
        if (eat('*')){
            x = x * parseFactor();
        } else if (eat('/')){
            x = x / parseFactor();
        }
        else return x;
    }
}

static long double parseFactor() {
    if (eat('+')) return parseFactor(); // unary plus
    if (eat('-')) return -parseFactor(); // unary minus

    long double x = 0;
    int startPos = pos;
    if (eat('(')) { // parentheses
        x = parseExpression();
        eat(')');
    } else if ((ch >= '0' && ch <= '9') || ch == '.') { // numbers
        while ((ch >= '0' && ch <= '9') || ch == '.') nextChar();
        char* num = supchar(startPos , pos);
        //cout << "S: " << startPos << "  E: " << pos << endl;

        //cout << "Parsing Number : " << num << endl;
        x = atof(num);
    } else if (ch >= 'a' && ch <= 'z') { // functions
        while (ch >= 'a' && ch <= 'z') nextChar();
        char* func = supchar(startPos , pos);
        int s1 = pos - startPos;

        //cout << "Applying Function '" << func << "'" << endl;

        if (charequal(func , func_sqrt , s1 , 4)){
            //cout << "Applying sqrt for '" << d << "'" << endl;
            x = sqrt(parseFactor());
        }
        else if (charequal(func , func_cbrt , s1 , 4)){
            x = cbrt(parseFactor());
        }
        else if (charequal(func , func_deg , s1 , 3)){
            x = parseFactor() * RAD_TO_DEG;
        }
        else if (charequal(func , func_rad , s1 , 3)){
            x = parseFactor() * DEG_TO_RAD;
        }
        else if (charequal(func , func_sin , s1 , 3)){
            x = sin(parseFactor());
        }
        else if (charequal(func , func_cos , s1 , 3)){
            x = cos(parseFactor());
        }
        else if (charequal(func , func_tan , s1 , 3)){
            x = tan(parseFactor());
        }
        else if (charequal(func , func_asin , s1 , 3)){
            x = asin(parseFactor());
        }
        else if (charequal(func , func_acos , s1 , 3)){
            x = acos(parseFactor());
        }
        else if (charequal(func , func_atan , s1 , 3)){
            x = atan(parseFactor());
        }
        else if (charequal(func , func_csc , s1 , 3)){
            x = 1.0 / sin(parseFactor());
        }
        else if (charequal(func , func_sec , s1 , 3)){
            x = 1.0 / cos(parseFactor());
        }
        else if (charequal(func , func_cot , s1 , 3)){
            x = 1.0 / tan(parseFactor());
        }
        else if (charequal(func , func_acsc , s1 , 3)){
            x = asin(1.0 / parseFactor());
        }
        else if (charequal(func , func_asec , s1 , 3)){
            x = acos(1.0 / parseFactor());
        }
        else if (charequal(func , func_acot , s1 , 3)){
            x = atan(1.0 / parseFactor());
        }
        else if (charequal(func , func_sinh , s1 , 4)){
            x = sinh(parseFactor());
        }
        else if (charequal(func , func_cosh , s1 , 4)){
            x = cosh(parseFactor());
        }
        else if (charequal(func , func_tanh , s1 , 4)){
            x = tanh(parseFactor());
        }
        else if (charequal(func , func_csch , s1 , 4)){
            x = 1.0 / sinh(parseFactor());
        }
        else if (charequal(func , func_sech , s1 , 4)){
            x = 1.0 / cosh(parseFactor());
        }
        else if (charequal(func , func_coth , s1 , 4)){
            x = 1.0 / tanh(parseFactor());
        }
        else if (charequal(func , func_rand , s1 , 4)){
            long double arg1 = -1;         //from
            long double arg2 = 1;     //to
            long arg3 = time(NULL); //seed
            if (eat('(')){
                arg2 = parseExpression();
                if (eat(',')) {
                    long double t = arg2;
                    arg2 = parseExpression();
                    arg1 = t;
                }
                if (eat(','))
                    arg3 = long(parseExpression());

                eat(')');

            }else{
                arg1 = 0;
                arg2 = parseFactor();
            }

            srand(arg3);
            double r = ((double) rand()) / RAND_MAX;

            x = (arg2 - arg1) * r + arg1;

        }else{
            cout << "(Error) Unknown function: " << func << endl;
        }

    } else {
        cout << "(Error) Unexpected: "  << ch << endl;
    }

    if (eat('^')){
        x = pow(x , parseFactor());
    }

    return x;
}

extern long double eval(char *input , int len){
    pos = -1;
    i_in = input;
    i_len = len;


    nextChar();

    long double output = parseExpression();
    if (pos != len)
        cout << "(Error) Input error at pos=" << pos << endl;

    return output;
}

