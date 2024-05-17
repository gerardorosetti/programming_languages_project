#include "test.hpp"

void Test::ValuesTest()
{
    std::shared_ptr<Expression> pair1 = std::make_shared<Pair>(std::make_shared<Number>(5), std::make_shared<Number>(10));
    
    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);

    std::vector<std::shared_ptr<Expression>> vect1 = {std::make_shared<Number>(2), std::make_shared<Number>(3)};
    std::shared_ptr<Expression> expVect1 = std::make_shared<Vector>(vect1);

    std::vector<std::shared_ptr<Expression>> vec1 = {std::make_shared<Number>(2), std::make_shared<Number>(3)};
    std::vector<std::shared_ptr<Expression>> vec2 = {std::make_shared<Number>(4), std::make_shared<Number>(5)};
    std::vector<std::vector<std::shared_ptr<Expression>>> mat1 = {vec1, vec2};
    std::shared_ptr<Expression> expMat1 = std::make_shared<Matrix>(mat1);

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);

    std::shared_ptr<Expression> var1 = std::make_shared<Variable>("A");
}

void Test::AdditionTest()
{
    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(2);

    std::shared_ptr<Expression> sum = std::make_shared<Addition>(num1,num2);

    std::shared_ptr<Expression> result = sum->eval(emptyEnv);

    std::cout << "El resultado de la suma es: " << std::endl;

    std::shared_ptr<Statement> displayAdditionResult = std::make_shared<Display>(result);
    displayAdditionResult->execute();

};