#include "statements.hpp"

Statement::Statement(std::shared_ptr<Expression> _exp) :  exp(_exp) {}

void Display::execute() const
{
    auto value = std::dynamic_pointer_cast<Value>(exp);
    if (value == nullptr)
    {
        std::cout << "COULD NOT DISPLAY A NON VALUE EXPRESSION" << std::endl;
        return;
    }

    if (value->getDataType() == DataType::Pair)
    {/*
        auto to = std::dynamic_pointer_cast<Number>(PairFirst{inter}->getNumber());
        auto tf = std::dynamic_pointer_cast<Number>(PairSecond{inter}->getNumber());
        
        std::cout<< << std::endl;*/
    }
    else if (value->getDataType() == DataType::Matrix)
    {
        auto matrixExpression = std::dynamic_pointer_cast<Matrix>(exp)->getMatrixExpression();
        std::cout << "Matrix =\n\n";
        for (std::vector<std::shared_ptr<Expression>> vec : matrixExpression)
        {
            for (std::shared_ptr<Expression> expr : vec)
            {
                //Statement::Statement{std::make_shared<Display>(expr)}.execute();
                auto num = std::dynamic_pointer_cast<Number>(expr);
                if (num == nullptr)
                {
                    std::cout << "cannot display data type incorrect" << std::endl;
                    return;
                }
                std::cout << " " << num->getNumber();
            }
            std::cout << std::endl;
        }
    } else if (value->getDataType() == DataType::Number)
    {
        auto num = std::dynamic_pointer_cast<Number>(exp);
        if (num == nullptr)
        {
            std::cout << "cannot display data type incorrect" << std::endl;
            return;
        }
        std::cout << "Number = " << num->getNumber() << std::endl;
    }
}