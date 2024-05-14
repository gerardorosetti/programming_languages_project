#include <iostream>
#include "expressions.hpp"

int main()
{

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(2);

    std::shared_ptr<Expression> sum = std::make_shared<Addition>(num1,num2);

    std::shared_ptr<Expression> result = sum->eval(emptyEnv);

    // Mostrar el resultado (depende de cómo definas la impresión de expresiones)
    std::cout << "El resultado de la suma es: " << std::dynamic_pointer_cast<Number>(result)->getNumber() << std::endl;


    // std::shared_ptr<Expression> num3 = std::make_shared<Number>(0);
    // std::shared_ptr<Expression> num4 = std::make_shared<Number>(10);

    // std::shared_ptr<Expression> interval = std::make_shared<Pair>(num3, num4);

    // std::shared_ptr<Expression> letter = std::make_shared<Variable>('x');
    // std::shared_ptr<Expression> sum2 = std::make_shared<Addition>(letter, num2);

    // std::shared_ptr<Expression> sum3 = std::make_shared<Addition>(letter, sum2);

    // std::shared_ptr<Expression> num5 = std::make_shared<Function>(sum3->eval(emptyEnv));

    // std::shared_ptr<Expression> integral = std::make_shared<Integral>(std::make_shared<Pair>(num3,num4), std::make_shared<Function>(num5));

    // std::cout << "El resultado de la integral es: " << std::dynamic_pointer_cast<Number>(integral->eval(emptyEnv))->getNumber() << std::endl;

    std::shared_ptr<Expression> num3 = std::make_shared<Number>(0);
    std::shared_ptr<Expression> num4 = std::make_shared<Number>(10);

    std::shared_ptr<Expression> interval = std::make_shared<Pair>(num3, num4);

    std::shared_ptr<Expression> letter = std::make_shared<Variable>('x');
    std::shared_ptr<Expression> sum2 = std::make_shared<Addition>(letter, num2);

    std::shared_ptr<Expression> sin = std::make_shared<Sine>(letter);

    std::shared_ptr<Expression> sum3 = std::make_shared<Addition>(sin, sum2);

    std::shared_ptr<Expression> num5 = std::make_shared<Function>(sum3);

    std::shared_ptr<Expression> integral = std::make_shared<Integral>(std::make_shared<Pair>(num3,num4), std::make_shared<Function>(num5), std::dynamic_pointer_cast<Variable>(letter));

    std::cout << "El resultado de la integral es: " << std::dynamic_pointer_cast<Number>(integral->eval(emptyEnv))->getNumber() << std::endl;

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

    std::cout << "El resultado de la interpolacion es: " << std::dynamic_pointer_cast<Number>(interpolate->eval(emptyEnv))->getNumber() << std::endl;

    std::vector<std::shared_ptr<Expression>> vec1 = {std::make_shared<Number>(2), std::make_shared<Number>(3)};
    std::vector<std::shared_ptr<Expression>> vec2 = {std::make_shared<Number>(4), std::make_shared<Number>(5)};
    std::vector<std::vector<std::shared_ptr<Expression>>> mat1 = {vec1, vec2};

    std::vector<std::shared_ptr<Expression>> vec3 = {std::make_shared<Number>(1), std::make_shared<Number>(2)};
    std::vector<std::shared_ptr<Expression>> vec4 = {std::make_shared<Number>(1), std::make_shared<Number>(2)};
    std::vector<std::vector<std::shared_ptr<Expression>>> mat2 = {vec3, vec4};

    std::shared_ptr<Matrix> matrix = std::dynamic_pointer_cast<Matrix>(std::make_shared<Addition>(std::make_shared<Matrix>(mat1), std::make_shared<Matrix>(mat2))->eval(emptyEnv));//std::make_shared<Matrix>(mat);

    //matrix->displayMatrix();

    return 0;
}