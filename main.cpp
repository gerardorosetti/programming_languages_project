#include <iostream>
#include "expresions.hpp"

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



    return 0;
}