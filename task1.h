#pragma once
#include <iostream>
#include <string>

//Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров и запускать исключение DivisionByZero,
//если второй параметр равен 0. В функции main выводить результат вызова функции div в консоль, а также ловить исключения.



class DivisionByZero
{
public:
    DivisionByZero (std::string& s) : m_error(s)
    {
    }
    std::string& outMessage()
    {
        return m_error;
    }
private:
    std::string m_error;
};

double div (double a, double b)
{
    if (b == 0)
    {
        std::string message = "cannot be divided by zero\n";
        throw DivisionByZero (message);
    }

    return ( a/b);
}




void task1()
{
    try {
        std::cout << div (23.0, 0.0);
    }  catch (DivisionByZero ex) {

        std::cout << ex.outMessage();
    }
}
