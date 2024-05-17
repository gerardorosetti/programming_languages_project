#include "test.hpp"

Display& display = Display::getInstance();

void Test::ValuesTest()
{
    std::shared_ptr<Expression> pair1 = std::make_shared<Pair>(std::make_shared<Number>(5), std::make_shared<Number>(10));

    display.execute(pair1);

    std::vector<std::shared_ptr<Expression>> vect1 = {std::make_shared<Number>(2), std::make_shared<Number>(3)};
    std::shared_ptr<Expression> expVect1 = std::make_shared<Vector>(vect1);

    display.execute(expVect1);

    std::vector<std::shared_ptr<Expression>> vec1 = {std::make_shared<Number>(2), std::make_shared<Number>(3)};
    std::vector<std::shared_ptr<Expression>> vec2 = {std::make_shared<Number>(4), std::make_shared<Number>(5)};
    std::vector<std::vector<std::shared_ptr<Expression>>> mat1 = {vec1, vec2};
    std::shared_ptr<Expression> expMat1 = std::make_shared<Matrix>(mat1);

    display.execute(expMat1);

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);

    display.execute(num1);

    std::shared_ptr<Expression> var1 = std::make_shared<Variable>('A');

    display.execute(var1);

    // Inverse Matrix

    std::vector<std::shared_ptr<Expression>> vecMat1 = {std::make_shared<Number>(2), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::shared_ptr<Expression>> vecMat2 = {std::make_shared<Number>(-1), std::make_shared<Number>(3), std::make_shared<Number>(2)};
    std::vector<std::shared_ptr<Expression>> vecMat3 = {std::make_shared<Number>(3), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma1 = {vecMat1, vecMat2, vecMat3};
    std::shared_ptr<Expression> m1 = std::make_shared<Matrix>(ma1);

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};
    std::shared_ptr<Expression> m1inv = std::make_shared<InverseMatrix>(std::dynamic_pointer_cast<Matrix>(m1))->eval(emptyEnv);

    display.execute(m1);
    display.execute(m1inv, "Inverse Matrix");
}

void Test::AdditionTest()
{
    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(2);

    std::shared_ptr<Expression> sum = std::make_shared<Addition>(num1,num2);

    std::shared_ptr<Expression> result = sum->eval(emptyEnv);

    std::cout << "Addition Value : ";

    display.execute(result);

};

void Test::IntegralTest()
{
    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> to = std::make_shared<Number>(0);
    std::shared_ptr<Expression> tf = std::make_shared<Number>(10);

    std::shared_ptr<Expression> interval = std::make_shared<Pair>(to, tf);

    std::shared_ptr<Expression> letter = std::make_shared<Variable>('x');
    std::shared_ptr<Expression> sum = std::make_shared<Addition>(letter, std::make_shared<Number>(2));

    std::shared_ptr<Expression> integral = std::make_shared<Integral>(std::make_shared<Pair>(to,tf), std::make_shared<Function>(sum),  std::dynamic_pointer_cast<Variable>(letter));

    std::cout << "Integer Value : ";

    std::shared_ptr<Expression> result = integral->eval(emptyEnv);

    display.execute(result);

};

void Test::InterpolateTest()
{
    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vectorExpression =
    {
        std::make_shared<Pair>(std::make_shared<Number>(0), std::make_shared<Number>(1.792)),
        std::make_shared<Pair>(std::make_shared<Addition>(std::make_shared<Number>(5), std::make_shared<Number>(5)), std::make_shared<Number>(1.308)),
        std::make_shared<Pair>(std::make_shared<Number>(30), std::make_shared<Number>(0.801)),
        std::make_shared<Pair>(std::make_shared<Number>(50), std::make_shared<Number>(0.549)),
        std::make_shared<Pair>(std::make_shared<Number>(70), std::make_shared<Number>(0.406)),
        std::make_shared<Pair>(std::make_shared<Number>(90), std::make_shared<Number>(0.317)),
        std::make_shared<Pair>(std::make_shared<Number>(100), std::make_shared<Number>(0.284)),
    };

    std::shared_ptr<Expression> interpolate = std::make_shared<Interpolate>(vectorExpression, std::make_shared<Number>(15.0));

    std::cout << "Interpolate Value : ";
    std::shared_ptr<Expression> result = interpolate->eval(emptyEnv);

    display.execute(result);
}