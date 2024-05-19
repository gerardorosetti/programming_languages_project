#include "statements.hpp"

Display& Display::getInstance()
{
    static Display instance;
    return instance;
}
void Display::execute(std::shared_ptr<Expression> exp, std::string name) const
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

Print& Print::getInstance()
{
    static Print instance;
    return instance;
}
void Print::execute(std::shared_ptr<Expression> expr, std::string toPrint) const
{
    std::cout << toPrint;
}