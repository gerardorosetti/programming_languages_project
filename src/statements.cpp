#include "statements.hpp"

Display::Display(std::shared_ptr<Expression> _exp) : exp(_exp) {}

void Display::execute() const
{
    if(exp == nullptr)
    {
        std::cout << "NULLPTR" << std::endl;
    }
    else
    {
        std::cout << exp->toString() << std::endl;
    }
}
Print::Print(std::string _str) : str(_str) {}

void Print::execute() const
{
    std::cout << str;
}