#include "statements.hpp"

Display& Display::getInstance() 
{
    static Display instance;
    return instance;
}
void Display::execute(std::shared_ptr<Expression> exp, std::string name) const
{
    auto value = std::dynamic_pointer_cast<Value>(exp);
    if (value == nullptr)
    {
        std::cout << "COULD NOT DISPLAY A NON VALUE EXPRESSION" << std::endl;
        return;
    }
    
    if (value->getDataType() == DataType::Number)
    {
        auto num = std::dynamic_pointer_cast<Number>(exp);
        if (num == nullptr)
        {
            std::cout << "CANNOT DISPLAY DATA TYPE INCORRECT" << std::endl;
            return;
        }
        std::cout << ((name == "") ? "Number = " : name)  << std::fixed << std::setprecision(4) << std::setw(8) << num->getNumber();
        if (name == "") std::cout << std::endl;
    }
    else if (value->getDataType() == DataType::Variable)
    {
        auto var = std::dynamic_pointer_cast<Variable>(exp);
        if (var == nullptr)
        {
            std::cout << "CANNOT DISPLAY DATA TYPE INCORRECT" << std::endl;
            return;
        }
        std::cout << ((name == "") ? "Variable = " : name) << std::setw(8) << var->getVariable();
        if (name == "") std::cout << std::endl;
    }
    else if (value->getDataType() == DataType::Pair)
    {
        auto pairExpression = std::dynamic_pointer_cast<Pair>(exp);
        if (pairExpression == nullptr)
        {
            std::cout << "CANNOT DISPLAY DATA TYPE INCORRECT" << std::endl;
            return;
        }
        auto to = std::dynamic_pointer_cast<Value>(pairExpression->getFirst());
        auto tf = std::dynamic_pointer_cast<Value>(pairExpression->getSecond());
        std::cout<<"Pair :";
        execute(to," ");
        execute(tf," "); 
        std::cout << std::endl;
    }
    else if (value->getDataType() == DataType::Vector)
    {
        auto vectorExpression = std::dynamic_pointer_cast<Vector>(exp)->getVectorExpression();
        std::cout << "Vector :";
        for (std::shared_ptr<Expression> i : vectorExpression)
        {
            auto val = std::dynamic_pointer_cast<Value>(i);
            execute(val, " ");
        }
        std::cout << std::endl;
    }
    else if (value->getDataType() == DataType::Matrix)
    {
        auto matrixExpression = std::dynamic_pointer_cast<Matrix>(exp)->getMatrixExpression();
        std::cout << ((name == "") ? "Matrix" : name) << " =" <<  std::endl;
        for (std::vector<std::shared_ptr<Expression>> vec : matrixExpression)
        {
            for (std::shared_ptr<Expression> expr : vec)
            {
                auto num = std::dynamic_pointer_cast<Value>(expr);
                execute(num, " ");
            }
            std::cout << std::endl;
        }
        std::cout << std::defaultfloat << std::setprecision(6);
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