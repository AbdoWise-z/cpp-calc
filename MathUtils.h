//
// Created by Abdo Mohamed on 2021-04-14
//

#include <string>
#include <vector>

#ifndef LEARN_MATHUTILS_H
#define LEARN_MATHUTILS_H

extern long double eval(char *input , int len);
extern void MathInit();
extern void setVariable(const std::string& name , long double value);
extern void defineFunction(const std::string& name , const std::vector<std::string>& params , const std::string& expression);

#endif //LEARN_MATHUTILS_H
