#include "statements.hpp"

Display& Display::getInstance() {
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

    if (value->getDataType() == DataType::Pair)
    {
        auto pairExpression = std::dynamic_pointer_cast<Pair>(exp);
        if (pairExpression == nullptr)
        {
            std::cout << "CANNOT DISPLAY DATA TYPE INCORRECT" << std::endl;
            return;
        }
        auto to = std::dynamic_pointer_cast<Number>(pairExpression->getFirst());
        auto tf = std::dynamic_pointer_cast<Number>(pairExpression->getSecond());
        if (to == nullptr || tf == nullptr)
        {
            std::cout << "CANNOT DISPLAY DATA TYPE INCORRECT" << std::endl;
            return;
        }

        std::cout<<"Pair = ["<< to->getNumber() <<", "<< tf->getNumber() <<"]" << std::endl;
    }
    else if (value->getDataType() == DataType::Vector)
    {
     //TO DO ADD GET VECTOR EXPRESSION
    }
    else if (value->getDataType() == DataType::Matrix)
    {
        auto matrixExpression = std::dynamic_pointer_cast<Matrix>(exp)->getMatrixExpression();
        std::cout << ((name == "") ? "Matrix" : name) << " =" <<  std::endl;
        std::cout << std::fixed << std::setprecision(4);
        for (std::vector<std::shared_ptr<Expression>> vec : matrixExpression)
        {
            for (std::shared_ptr<Expression> expr : vec)
            {
                auto num = std::dynamic_pointer_cast<Number>(expr);
                if (num == nullptr)
                {
                    std::cout << "CANNOT DISPLAY DATA TYPE INCORRECT" << std::endl;
                    return;
                }
                std::cout << std::setw(8) << num->getNumber();
            }
            std::cout << std::endl;
        }
        std::cout << std::defaultfloat << std::setprecision(6);
    } else if (value->getDataType() == DataType::Number)
    {
        auto num = std::dynamic_pointer_cast<Number>(exp);
        if (num == nullptr)
        {
            std::cout << "CANNOT DISPLAY DATA TYPE INCORRECT" << std::endl;
            return;
        }
        std::cout << "Number = " << num->getNumber() << std::endl;
    }
    else if (value->getDataType() == DataType::Variable)
    {
        auto var = std::dynamic_pointer_cast<Variable>(exp);
        if (var == nullptr)
        {
            std::cout << "CANNOT DISPLAY DATA TYPE INCORRECT" << std::endl;
            return;
        }
        std::cout << "Variable = " << var->getVariable() << std::endl;
    }
}