//
// Created by Abdo Momahed (AbdoWise) on 2021-04-14
//
// currently supports : sqrt , cprt , sin , cos , tan , asin , acos , atan
//                      csc , sec , cot , acsc , asec , acot , sinh , cosh
//                      tanh , csch , sech , coth , rand , deg , rad , sgn
//                      log , exp , abs
//
// was going to add variable support .. but I have to study integration
// this thing took me 1+ hour to code already
//


#include "MathUtils.h"

#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>


using namespace std;

static long double parseExpression();
static long double parseTerm();
static long double parseFactor();


static int pos = 0;
static char ch;

static char *i_in;
static int i_len;

static const char func_sqrt[] = "sqrt";
static const char func_deg[] = "deg";
static const char func_rad[] = "rad";

static const long double DEG_TO_RAD =       M_PI / 180.0;
static const long double RAD_TO_DEG =       180.0 / M_PI;

static const char func_sin[] = "sin";
static const char func_cos[] = "cos";
static const char func_tan[] = "tan";

static const char func_asin[] = "asin";
static const char func_acos[] = "acos";
static const char func_atan[] = "atan";

static const char func_csc[] = "csc";
static const char func_sec[] = "sec";
static const char func_cot[] = "cot";

static const char func_acsc[] = "acsc";
static const char func_asec[] = "asec";
static const char func_acot[] = "acot";

static const char func_cbrt[] = "cbrt";

static const char func_sinh[] = "sinh";
static const char func_cosh[] = "cosh";
static const char func_tanh[] = "tanh";

static const char func_csch[] = "csch";
static const char func_sech[] = "sech";
static const char func_coth[] = "coth";

static const char func_rand[]  = "rand";
static const char func_log[]   = "log";
static const char func_exp[]   = "exp";
static const char func_sgn[]   = "sgn";
static const char func_abs[]   = "abs";
static const char func_pow[]   = "pow";
static const char func_min[]   = "min";
static const char func_max[]   = "max";

static vector<string> variables_names;
static vector<long double> variables_values;

static vector<string> func_names;
static vector<string> func_expressions;
static vector<vector<string>> func_params;

static vector<string> local_variables_names;
static vector<long double> local_variables_values;

extern void MathInit(){
    variables_names.emplace_back("pi");
    variables_values.emplace_back(M_PI);

    variables_names.emplace_back("PI");
    variables_values.emplace_back(M_PI);

    variables_names.emplace_back("e");
    variables_values.emplace_back(M_E);

    variables_names.emplace_back("DEG_TO_RAD");
    variables_values.emplace_back(DEG_TO_RAD);

    variables_names.emplace_back("RAD_TO_DEG");
    variables_values.emplace_back(RAD_TO_DEG);


}

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

    if (pos == i_len) return 0.0; //passed the size;

    long double x = 0;
    int startPos = pos;
    if (eat('(')) { // parentheses
        x = parseExpression();
        eat(')');
    } else if ((ch >= '0' && ch <= '9') || ch == '.') { // numbers
        while ((ch >= '0' && ch <= '9') || ch == '.' || ch == 'E') nextChar();
        char* num = supchar(startPos , pos);
        //cout << "S: " << startPos << "  E: " << pos << endl;

        //cout << "Parsing Number : " << num << endl;
        x = strtod(num , nullptr); //str_to_d

    } else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_')) { // functions
        while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_')) nextChar();
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
            long double arg1 = 0;         //from
            long double arg2 = 1;         //to
            long arg3 = time(NULL); //seed
            if (eat('(') && !eat(')')){
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
                cout << "(Error) rand usage is rand(t) or rand(f,t) or rand(f,t,s) returning [0,1]" << endl;
            }

            srand(arg3);
            double r = ((double) rand()) / RAND_MAX;

            x = (arg2 - arg1) * r + arg1;

        }
        else if (charequal(func , func_log , s1 , 3)){
            long double arg1 = 1;
            long double arg2 = M_E;
            if (eat('(') && !eat(')')){
                arg1 = parseExpression();
                if (eat(','))
                    arg2 = parseExpression();
                eat(')');
            }else{
                cout << "(Error) log usage is log(n) or log(n,e) returning 0" << endl;
            }

            x = log(arg1) / log(arg2);
        }
        else if (charequal(func , func_pow , s1 , 3)){
            long double arg1 = 0;
            long double arg2 = 0;
            if (eat('(') && !eat(')')){
                arg1 = parseExpression();
                if (eat(',')) {
                    arg2 = parseExpression();
                    x = pow(arg1 , arg2);
                }else{
                    cout << "(Error) pow usage is pow(base,power) returning 1" << endl;
                    x = 1.0;
                }
                eat(')');
            }else{
                cout << "(Error) pow usage is pow(base,power) returning 1" << endl;
                x = 1.0;
            }
        }
        else if (charequal(func , func_min , s1 , 3)){
            long double arg1 = 0;
            long double arg2 = 0;
            if (eat('(') && !eat(')')){
                arg1 = parseExpression();
                if (eat(',')) {
                    arg2 = parseExpression();
                    x = min(arg1 , arg2);
                }else{
                    cout << "(Error) min usage is min(n1,n2) returning 0" << endl;
                    x = 0.0;
                }
                eat(')');
            }else{
                cout << "(Error) min usage is min(n1,n2) returning 0" << endl;
                x = 0.0;
            }
        }
        else if (charequal(func , func_max , s1 , 3)){
            long double arg1 = 0;
            long double arg2 = 0;
            if (eat('(') && !eat(')')){

                arg1 = parseExpression();
                if (eat(',')) {
                    arg2 = parseExpression();
                    x = max(arg1 , arg2);
                }else{
                    cout << "(Error) max usage is max(n1,n2) returning 0" << endl;
                    x = 0.0;
                }
                eat(')');
            }else{
                cout << "(Error) max usage is max(n1,n2) returning 0" << endl;
                x = 0.0;
            }
        }
        else if (charequal(func , func_exp , s1 , 3)){
            x = exp(parseFactor());
        }
        else if (charequal(func , func_sgn , s1 , 3)){
            x = parseFactor();

            if (x > 0){
                x = 1.0;
            }else if (x < 0){
                x = -1.0;
            }else{
                x = 0.0;
            }
        }
        else if (charequal(func , func_abs , s1 , 3)){
            x = abs(parseFactor());
        }
        else{

            string str;
            str.append(func);
            if (eat('(')){ //a function
                pos = i_len;
                x = 0.0;
                cout << "(Error) Unknown function: " << str << endl;
            }
            else {
                bool found = false;
                for (int i = 0; i < variables_names.size(); ++i) {
                    if (variables_names.at(i) == str) {
                        x = variables_values.at(i);
                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "(Error) Unknown variable: " << str << endl;
            }
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

extern void setVariable(const string& name , long double value){
    for (int i = 0; i < variables_names.size(); ++i) {
        if (variables_names.at(i) == name){
            variables_values[i] = value;
            return;
        }
    }

    variables_names.emplace_back(name);
    variables_values.emplace_back(value);
}

extern void defineFunction(const std::string& name , const std::vector<std::string>& params , const std::string& expression){

    for (int i = 0; i < func_names.size(); ++i) {
        if (func_names[i] == name){
            func_names[i]         = name;
            func_params[i]        = params;
            func_expressions[i]   = expression;
            break;
        }
    }

    func_names            .emplace_back(name);
    func_params           .emplace_back(params);
    func_expressions      .emplace_back(expression);

}


