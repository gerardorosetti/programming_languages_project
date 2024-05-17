#include "test.hpp"

Display& display = Display::getInstance();
Print& print = Print::getInstance();

void Test::ValuesTest()
{
    print.execute(nullptr,"\nValues Test \n");

    std::shared_ptr<Expression> pair1 = std::make_shared<Pair>(std::make_shared<Number>(5), std::make_shared<Number>(10));

    display.execute(pair1);

    std::vector<std::shared_ptr<Expression>> vect1 = {std::make_shared<Number>(2), std::make_shared<Number>(3), std::make_shared<Number>(10)};
    std::shared_ptr<Expression> expVect1 = std::make_shared<Vector>(vect1);

    display.execute(expVect1);

    std::vector<std::shared_ptr<Expression>> vec1 = {std::make_shared<Number>(2), std::make_shared<Number>(3)};
    std::vector<std::shared_ptr<Expression>> vec2 = {std::make_shared<Number>(4), std::make_shared<Variable>('B')};
    std::vector<std::vector<std::shared_ptr<Expression>>> mat1 = {vec1, vec2};
    std::shared_ptr<Expression> expMat1 = std::make_shared<Matrix>(mat1);

    display.execute(expMat1);

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);

    display.execute(num1);

    std::shared_ptr<Expression> var1 = std::make_shared<Variable>('A');

    display.execute(var1);
}

void Test::EnvTest()
{
    print.execute(nullptr, "\nEnvironment Test\n");

    Environment env = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vec1 = {std::make_shared<Number>(2), std::make_shared<Number>(3)};
    std::vector<std::shared_ptr<Expression>> vec2 = {std::make_shared<Number>(4), std::make_shared<Variable>('B')};
    std::vector<std::vector<std::shared_ptr<Expression>>> mat1 = {vec1, vec2};
    std::shared_ptr<Expression> expMat1 = std::make_shared<Matrix>(mat1);

    env.push_front(std::make_pair('B', std::make_shared<Number>(10)));

    display.execute(expMat1);
    display.execute(expMat1->eval(env));
}

void Test::AdditionTest()
{
    
    print.execute(nullptr, "\nAdition Value Test\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(2);

    std::shared_ptr<Expression> sum = std::make_shared<Addition>(num1,num2);

    std::shared_ptr<Expression> result = sum->eval(emptyEnv);

    display.execute(result);

};

void Test::InverseMatrixTest()
{
    print.execute(nullptr, "\nInverse Matrix Test\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vecMat1 = {std::make_shared<Number>(2), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::shared_ptr<Expression>> vecMat2 = {std::make_shared<Number>(-1), std::make_shared<Number>(3), std::make_shared<Number>(2)};
    std::vector<std::shared_ptr<Expression>> vecMat3 = {std::make_shared<Number>(3), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma1 = {vecMat1, vecMat2, vecMat3};
    std::shared_ptr<Expression> m1 = std::make_shared<Matrix>(ma1);

    std::shared_ptr<Expression> m1inv = std::make_shared<InverseMatrix>(std::dynamic_pointer_cast<Matrix>(m1))->eval(emptyEnv);

    display.execute(m1);
    display.execute(m1inv, "Inverse Matrix");
}

void Test::DivisionMatrixTest()
{
    print.execute(nullptr, "\nMatrix Division Test\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vecMat1 = {std::make_shared<Number>(2), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::shared_ptr<Expression>> vecMat2 = {std::make_shared<Number>(-1), std::make_shared<Number>(3), std::make_shared<Number>(2)};
    std::vector<std::shared_ptr<Expression>> vecMat3 = {std::make_shared<Number>(3), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma1 = {vecMat1, vecMat2, vecMat3};
    std::shared_ptr<Expression> m1 = std::make_shared<Matrix>(ma1);

    std::vector<std::shared_ptr<Expression>> vecMat4 = {std::make_shared<Number>(1), std::make_shared<Number>(4), std::make_shared<Number>(9)};
    std::vector<std::shared_ptr<Expression>> vecMat5 = {std::make_shared<Number>(-1), std::make_shared<Number>(-3), std::make_shared<Number>(-2)};
    std::vector<std::shared_ptr<Expression>> vecMat6 = {std::make_shared<Number>(3), std::make_shared<Number>(2), std::make_shared<Number>(5)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma2 = {vecMat4, vecMat5, vecMat6};
    std::shared_ptr<Expression> m2 = std::make_shared<Division>(m1, std::make_shared<Matrix>(ma2))->eval(emptyEnv);
    display.execute(m2, "Matrix Division Test");

    std::shared_ptr<Expression> m3 = std::make_shared<Division>(m1, m1)->eval(emptyEnv);
    display.execute(m3, "Matrix Division Test 2"); 
}

void Test::IntegralTest()
{
    print.execute(nullptr, "\nIntegral Test\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> to = std::make_shared<Number>(0);
    std::shared_ptr<Expression> tf = std::make_shared<Number>(10);

    std::shared_ptr<Expression> interval = std::make_shared<Pair>(to, tf);

    std::shared_ptr<Expression> letter = std::make_shared<Variable>('x');
    std::shared_ptr<Expression> sum = std::make_shared<Addition>(letter, std::make_shared<Number>(2));

    std::shared_ptr<Expression> integral = std::make_shared<Integral>(std::make_shared<Pair>(to,tf), std::make_shared<Function>(sum),  std::dynamic_pointer_cast<Variable>(letter));

    print.execute(nullptr, "Integral Value : ");

    std::shared_ptr<Expression> result = integral->eval(emptyEnv);

    display.execute(result);

};

void Test::InterpolateTest()
{
    print.execute(nullptr, "\nInterpolate Test\n");

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

    print.execute(nullptr, "Interpolate Value : ");
    std::shared_ptr<Expression> result = interpolate->eval(emptyEnv);

    display.execute(result);
}