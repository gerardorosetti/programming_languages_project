#include "test.hpp"

void Test::ValuesTest()
{
    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\nVALUES TEST (DATA TYPES)\n");
    print1->execute();

    std::shared_ptr<Expression> pair1 = std::make_shared<Pair>(std::make_shared<Number>(5), std::make_shared<Number>(10));
    
    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nPair");
    print2->execute();
    
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(pair1);
    display1->execute();

    std::vector<std::shared_ptr<Expression>> vect1 = {std::make_shared<Number>(2), std::make_shared<Number>(3), std::make_shared<Number>(10)};
    std::shared_ptr<Expression> expVect1 = std::make_shared<Vector>(vect1);

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("\nVector: ");
    print3->execute();

    std::shared_ptr<Statement> display2 = std::make_shared<Display>(expVect1);
    display2->execute();

    std::vector<std::shared_ptr<Expression>> vec1 = {std::make_shared<Number>(2), std::make_shared<Number>(3)};
    std::vector<std::shared_ptr<Expression>> vec2 = {std::make_shared<Number>(4), std::make_shared<Variable>('B')};
    std::vector<std::vector<std::shared_ptr<Expression>>> mat1 = {vec1, vec2};
    std::shared_ptr<Expression> expMat1 = std::make_shared<Matrix>(mat1);

    std::shared_ptr<Statement> print4 = std::make_shared<Print>("\nMatrix: \n");
    print4->execute();
    
    std::shared_ptr<Statement> display3 = std::make_shared<Display>(expMat1);
    display3->execute();

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);

    std::shared_ptr<Statement> print5 = std::make_shared<Print>("Number: ");
    print5->execute();
    
    std::shared_ptr<Statement> display4 = std::make_shared<Display>(num1);
    display4->execute();

    std::shared_ptr<Expression> var1 = std::make_shared<Variable>('A');
    
    std::shared_ptr<Statement> print6 = std::make_shared<Print>("\nVariable: ");
    print6->execute();

    std::shared_ptr<Statement> display5 = std::make_shared<Display>(var1);
    display5->execute();
}

void Test::ExpressionTest()
{
    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nEXPRESSIONS TEST\n");
    print1->execute();

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(2);
    std::shared_ptr<Expression> var = std::make_shared<Variable>('A');
    std::shared_ptr<Expression> sum = std::make_shared<Addition>(num1,var);
    std::shared_ptr<Expression> sub = std::make_shared<Subtraction>(num1,sum);
    std::shared_ptr<Expression> mul = std::make_shared<Multiplication>(sub,var);
    std::shared_ptr<Expression> div = std::make_shared<Division>(mul,std::make_shared<Number>(10));
    std::shared_ptr<Expression> func = std::make_shared<Function>(div);
    
    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nAddition, Subtraction, Multiplication and Division: ");
    print2->execute();

    std::shared_ptr<Statement> display1 = std::make_shared<Display>(func);
    display1->execute();

    std::shared_ptr<Expression> var1 = std::make_shared<Variable>('x');
    std::shared_ptr<Expression> pow = std::make_shared<Power>(var1,std::make_shared<Number>(2));
    std::shared_ptr<Expression> sum1 = std::make_shared<Addition>(pow,std::make_shared<Addition>(std::make_shared<Sine>(var1),std::make_shared<Logarithm>(std::make_shared<Number>(10), var1)));
    std::shared_ptr<Expression> func2 = std::make_shared<Function>(sum1);

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("\nPower, Trigonometrics, ln: ");
    print3->execute();

    std::shared_ptr<Statement> display2 = std::make_shared<Display>(func2);
    display2->execute();

    std::shared_ptr<Expression> to = std::make_shared<Number>(0);
    std::shared_ptr<Expression> tf = std::make_shared<Number>(10);

    std::shared_ptr<Expression> interval = std::make_shared<Pair>(to, tf);

    std::shared_ptr<Expression> letter = std::make_shared<Variable>('x');
    std::shared_ptr<Expression> sum2 = std::make_shared<Addition>(letter, std::make_shared<Number>(2));

    std::shared_ptr<Expression> integral = std::make_shared<Integral>(std::make_shared<Pair>(to,tf), std::make_shared<Function>(sum2),  std::dynamic_pointer_cast<Variable>(letter));

    std::shared_ptr<Statement> print4 = std::make_shared<Print>("\nIntegral: ");
    print4->execute();
    
    std::shared_ptr<Statement> display3 = std::make_shared<Display>(integral);
    display3->execute();

    std::shared_ptr<Expression> xo = std::make_shared<Number>(0);

    std::shared_ptr<Expression> sum3 = std::make_shared<Addition>(std::make_shared<Multiplication>(std::make_shared<Division>(std::make_shared<Number>(-3), std::make_shared<Number>(125)),letter), std::make_shared<Number>(0.6));

    std::shared_ptr<Expression> tFinal = std::make_shared<Number>(30);

    std::shared_ptr<Expression> ODE = std::make_shared<ODEFirstOrderInitialValues>(std::make_shared<Function>(sum3), std::make_shared<Pair>(to,xo), std::dynamic_pointer_cast<Number>(tFinal), std::dynamic_pointer_cast<Variable>(letter));

    std::shared_ptr<Statement> print5 = std::make_shared<Print>("\nOrdinary Differential Equation First Order, with initial values:\n");
    print5->execute();

    std::shared_ptr<Statement> display4 = std::make_shared<Display>(ODE);
    display4->execute();
}

void Test::EnvTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nENVIRONMENT TEST\n");
    print1->execute();

    Environment env = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vec1 = {std::make_shared<Number>(2), std::make_shared<Number>(3)};
    std::vector<std::shared_ptr<Expression>> vec2 = {std::make_shared<Number>(4), std::make_shared<Variable>('B')};
    std::vector<std::vector<std::shared_ptr<Expression>>> mat1 = {vec1, vec2};
    std::shared_ptr<Expression> expMat1 = std::make_shared<Matrix>(mat1);

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nMatrix without value for B\n");
    print2->execute();

    std::shared_ptr<Statement> display1 = std::make_shared<Display>(expMat1->eval(env));
    display1->execute();

    env.push_front(std::make_pair('B', std::make_shared<Number>(10)));
    
    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Matrix with value for B added\n");
    print3->execute();

    std::shared_ptr<Statement> display2 = std::make_shared<Display>(expMat1->eval(env));
    display2->execute();
}

void Test::AdditionTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nADDITION TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(2);

    std::shared_ptr<Expression> sum = std::make_shared<Addition>(num1,num2);

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression: ");
    print2->execute();

    std::shared_ptr<Statement> display1 = std::make_shared<Display>(sum);
    display1->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval: ");
    print3->execute();

    std::shared_ptr<Statement> display2 = std::make_shared<Display>(sum->eval(emptyEnv));
    display2->execute();
};

void Test::AdditionMatrixTest()
{

    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nADDITION MATRIX TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vec1 = {std::make_shared<Number>(2), std::make_shared<Number>(3)};
    std::vector<std::shared_ptr<Expression>> vec2 = {std::make_shared<Number>(4), std::make_shared<Number>(19)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma1 = {vec1, vec2};
    std::shared_ptr<Expression> m1 = std::make_shared<Matrix>(ma1);

    std::vector<std::shared_ptr<Expression>> vec3 = {std::make_shared<Number>(1), std::make_shared<Number>(4), std::make_shared<Number>(9)};
    std::vector<std::shared_ptr<Expression>> vec4 = {std::make_shared<Number>(1), std::make_shared<Number>(3), std::make_shared<Number>(2)};
    std::vector<std::shared_ptr<Expression>> vec5 = {std::make_shared<Number>(3), std::make_shared<Number>(2), std::make_shared<Number>(5)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma2 = {vec3, vec4, vec5};
    std::shared_ptr<Expression> m2 = std::make_shared<Matrix>(ma2);
    std::shared_ptr<Expression> sum1 = std::make_shared<Addition>(m1,m2);

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression1: \n");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(sum1);
    display1->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval1: \n");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(sum1->eval(emptyEnv));
    display2->execute();

    std::vector<std::shared_ptr<Expression>> vec6 = {std::make_shared<Number>(1), std::make_shared<Number>(100)};
    std::vector<std::shared_ptr<Expression>> vec7 = {std::make_shared<Number>(3), std::make_shared<Variable>(9)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma3 = {vec6, vec7};
    std::shared_ptr<Expression> m3 = std::make_shared<Matrix>(ma3);
    std::shared_ptr<Expression> sum2 = std::make_shared<Addition>(m1,m3);

    std::shared_ptr<Statement> print4 = std::make_shared<Print>("\nExpression2: \n");
    print4->execute();
    std::shared_ptr<Statement> display3 = std::make_shared<Display>(sum2);
    display3->execute();
    
    std::shared_ptr<Statement> print5 = std::make_shared<Print>("Eval2: \n");
    print5->execute();
    std::shared_ptr<Statement> display4 = std::make_shared<Display>(sum2->eval(emptyEnv));
    display4->execute();
}

void Test::SubtractionTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nSUBTRACTION TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(2);

    std::shared_ptr<Expression> exp = std::make_shared<Subtraction>(num1,num2);
    
    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression: ");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(exp);
    display1->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval: ");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(exp->eval(emptyEnv));
    display2->execute();
}

void Test::MultiplicationTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nMULTIPLICATION TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(2);

    std::shared_ptr<Expression> exp = std::make_shared<Multiplication>(num1, num2);

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression: ");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(exp);
    display1->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval: ");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(exp->eval(emptyEnv));
    display2->execute();
}

void Test::MultiplicationMatrixTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nMULTIPLICATION MATRIX TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vec1 = {std::make_shared<Number>(2), std::make_shared<Number>(3)};
    std::vector<std::shared_ptr<Expression>> vec2 = {std::make_shared<Number>(4), std::make_shared<Number>(19)};
    std::vector<std::shared_ptr<Expression>> vec3 = {std::make_shared<Number>(4), std::make_shared<Number>(19)};

    std::vector<std::vector<std::shared_ptr<Expression>>> ma1 = {vec1, vec2, vec3};
    std::shared_ptr<Expression> m1 = std::make_shared<Matrix>(ma1);

    std::vector<std::shared_ptr<Expression>> vec4 = {std::make_shared<Number>(2), std::make_shared<Number>(3), std::make_shared<Number>(5)};
    std::vector<std::shared_ptr<Expression>> vec5 = {std::make_shared<Number>(4), std::make_shared<Number>(19), std::make_shared<Number>(1)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma2 = {vec4, vec5};
    std::shared_ptr<Expression> m2 = std::make_shared<Matrix>(ma2);

    std::shared_ptr<Expression> mul1 = std::make_shared<Multiplication>(m1,m2);
    
    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression1: \n");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(mul1);
    display1->execute();
 
    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval1: \n");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(mul1->eval(emptyEnv));
    display2->execute();

    std::vector<std::shared_ptr<Expression>> vec6 = {std::make_shared<Number>(2), std::make_shared<Number>(3)};
    std::vector<std::shared_ptr<Expression>> vec7 = {std::make_shared<Number>(4), std::make_shared<Number>(19)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma3 = {vec6, vec7};
    std::shared_ptr<Expression> m3 = std::make_shared<Matrix>(ma3);

    std::shared_ptr<Expression> mul2 = std::make_shared<Multiplication>(m2,m3);

    std::shared_ptr<Statement> print4 = std::make_shared<Print>("\nExpression2: \n");
    print4->execute();
    std::shared_ptr<Statement> display3 = std::make_shared<Display>(mul2);
    display3->execute();

    std::shared_ptr<Statement> print5 = std::make_shared<Print>("Eval2: \n");
    print5->execute();
    std::shared_ptr<Statement> display4 = std::make_shared<Display>(mul2->eval(emptyEnv));
    display4->execute();

    std::shared_ptr<Expression> mul3 = std::make_shared<Multiplication>(std::make_shared<Number>(10),m3);

    std::shared_ptr<Statement> print6 = std::make_shared<Print>("\nExpression3: \n");
    print6->execute();
    std::shared_ptr<Statement> display5 = std::make_shared<Display>(mul3);
    display5->execute();

    std::shared_ptr<Statement> print7 = std::make_shared<Print>("Eval3: \n");
    print7->execute();
    std::shared_ptr<Statement> display6 = std::make_shared<Display>(mul3->eval(emptyEnv));
    display6->execute();
}

void Test::DivisionTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nDIVISION TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(2);

    std::shared_ptr<Expression> exp = std::make_shared<Division>(num1,num2);

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression: ");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(exp);
    display1->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval: ");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(exp->eval(emptyEnv));
    display2->execute();
}

void Test::PowerTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>( "\n\nPOWER TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(2);

    std::shared_ptr<Expression> exp = std::make_shared<Power>(num1,num2);

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression: ");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(exp);
    display1->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval: ");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(exp->eval(emptyEnv));
    display2->execute();
}

void Test::SquareRootTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>( "\n\nSQUARE ROOT TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(16);

    std::shared_ptr<Expression> exp = std::make_shared<SquareRoot>(num1);

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression: ");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(exp);
    display1->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval: ");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(exp->eval(emptyEnv));
    display2->execute();
}

void Test::RootTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nROOT TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(27);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(3);

    std::shared_ptr<Expression> exp = std::make_shared<Root>(num1, num2);

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression: ");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(exp);
    display1->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval: ");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(exp->eval(emptyEnv));
    display2->execute();
}

void Test::TrigonometricsTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nTRIGONOMETRICS TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> sin = std::make_shared<Sine>(std::make_shared<PI>());
    std::shared_ptr<Expression> cos = std::make_shared<Cosine>(std::make_shared<PI>());
    std::shared_ptr<Expression> tan = std::make_shared<Tangent>(std::make_shared<PI>());
    std::shared_ptr<Expression> ctg = std::make_shared<Cotangent>(std::make_shared<PI>());
    std::shared_ptr<Expression> tan2 = std::make_shared<Tangent>(std::make_shared<Division>(std::make_shared<PI>(),std::make_shared<Number>(2)));
    std::shared_ptr<Expression> ctg2 = std::make_shared<Cotangent>(std::make_shared<Division>(std::make_shared<PI>(),std::make_shared<Number>(2)));

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpressions:\n");
    print2->execute();

    std::shared_ptr<Statement> display1 = std::make_shared<Display>(sin);
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(cos);
    std::shared_ptr<Statement> display3 = std::make_shared<Display>(tan);
    std::shared_ptr<Statement> display4 = std::make_shared<Display>(ctg);
    std::shared_ptr<Statement> display5 = std::make_shared<Display>(tan2);
    std::shared_ptr<Statement> display6 = std::make_shared<Display>(ctg2);

    display1->execute();
    display2->execute();
    display3->execute();
    display4->execute();
    display5->execute();
    display6->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("\nEvals:\n");
    print3->execute();

    std::shared_ptr<Statement> display7 = std::make_shared<Display>(sin->eval(emptyEnv));
    std::shared_ptr<Statement> display8 = std::make_shared<Display>(cos->eval(emptyEnv));
    std::shared_ptr<Statement> display9 = std::make_shared<Display>(tan->eval(emptyEnv));
    std::shared_ptr<Statement> display10 = std::make_shared<Display>(ctg->eval(emptyEnv));
    std::shared_ptr<Statement> display11 = std::make_shared<Display>(tan2->eval(emptyEnv));
    std::shared_ptr<Statement> display12 = std::make_shared<Display>(ctg2->eval(emptyEnv));

    display7->execute();
    display8->execute();
    display9->execute();
    display10->execute();
    display11->execute();
    display12->execute();
}
void Test::InverseMatrixTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nINVERSE MATRIX TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vecMat1 = {std::make_shared<Number>(2), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::shared_ptr<Expression>> vecMat2 = {std::make_shared<Number>(-1), std::make_shared<Number>(3), std::make_shared<Number>(2)};
    std::vector<std::shared_ptr<Expression>> vecMat3 = {std::make_shared<Number>(3), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma1 = {vecMat1, vecMat2, vecMat3};
    std::shared_ptr<Expression> m1 = std::make_shared<Matrix>(ma1);

    std::shared_ptr<Expression> m1inv = std::make_shared<InverseMatrix>(std::dynamic_pointer_cast<Matrix>(m1));
    
    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression: \n");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(m1inv);
    display1->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval: \n");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(m1inv->eval(emptyEnv));
    display2->execute();
}

void Test::MatrixLUTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nLU MATRIX TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vecMat1 = {std::make_shared<Number>(2), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::shared_ptr<Expression>> vecMat2 = {std::make_shared<Number>(-1), std::make_shared<Number>(3), std::make_shared<Number>(2)};
    std::vector<std::shared_ptr<Expression>> vecMat3 = {std::make_shared<Number>(3), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma1 = {vecMat1, vecMat2, vecMat3};
    std::shared_ptr<Expression> m1 = std::make_shared<Matrix>(ma1);

    std::shared_ptr<Expression> matrixPair = std::make_shared<MatrixLU>(std::dynamic_pointer_cast<Matrix>(m1));

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression: \n");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(matrixPair);
    display1->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval: \n");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(matrixPair->eval(emptyEnv));
    display2->execute();

}

void Test::TridiagonalMatrixTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nTRIDIAGONAL MATRIX TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vecMat1 = {std::make_shared<Number>(2), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::shared_ptr<Expression>> vecMat2 = {std::make_shared<Number>(-1), std::make_shared<Number>(3), std::make_shared<Number>(2)};
    std::vector<std::shared_ptr<Expression>> vecMat3 = {std::make_shared<Number>(3), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma1 = {vecMat1, vecMat2, vecMat3};
    std::shared_ptr<Expression> m1 = std::make_shared<Matrix>(ma1);

    std::shared_ptr<Expression> trid = std::make_shared<TridiagonalMatrix>(std::dynamic_pointer_cast<Matrix>(m1));

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression1: \n");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(trid);
    display1->execute();
 
    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval1: \n");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(trid->eval(emptyEnv));
    display2->execute();

    std::vector<std::shared_ptr<Expression>> vecMat4 = {std::make_shared<Number>(4), std::make_shared<Number>(3), std::make_shared<Number>(2), std::make_shared<Number>(1)};
    std::vector<std::shared_ptr<Expression>> vecMat5 = {std::make_shared<Number>(3), std::make_shared<Number>(3), std::make_shared<Number>(2), std::make_shared<Number>(1)};
    std::vector<std::shared_ptr<Expression>> vecMat6 = {std::make_shared<Number>(2), std::make_shared<Number>(2), std::make_shared<Number>(2), std::make_shared<Number>(1)};
    std::vector<std::shared_ptr<Expression>> vecMat7 = {std::make_shared<Number>(1), std::make_shared<Number>(1), std::make_shared<Number>(1), std::make_shared<Number>(1)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma2 = {vecMat4, vecMat5, vecMat6, vecMat7};

    std::shared_ptr<Expression> m2 = std::make_shared<Matrix>(ma2);

    std::shared_ptr<Expression> trid2 = std::make_shared<TridiagonalMatrix>(std::dynamic_pointer_cast<Matrix>(m2));

    std::shared_ptr<Statement> print4 = std::make_shared<Print>("\nExpression2: \n");
    print4->execute();
    std::shared_ptr<Statement> display3 = std::make_shared<Display>(trid2);
    display3->execute();

    std::shared_ptr<Statement> print5 = std::make_shared<Print>("Eval2: \n");
    print5->execute();
    std::shared_ptr<Statement> display4 = std::make_shared<Display>(trid->eval(emptyEnv));
    display4->execute();
}

void Test::RealEigenvaluesTest() // Only works with real numbers
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nEIGENVALUES TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vecMat1 = {std::make_shared<Number>(4), std::make_shared<Number>(3), std::make_shared<Number>(2), std::make_shared<Number>(1)};
    std::vector<std::shared_ptr<Expression>> vecMat2 = {std::make_shared<Number>(3), std::make_shared<Number>(3), std::make_shared<Number>(2), std::make_shared<Number>(1)};
    std::vector<std::shared_ptr<Expression>> vecMat3 = {std::make_shared<Number>(2), std::make_shared<Number>(2), std::make_shared<Number>(2), std::make_shared<Number>(1)};
    std::vector<std::shared_ptr<Expression>> vecMat4 = {std::make_shared<Number>(1), std::make_shared<Number>(1), std::make_shared<Number>(1), std::make_shared<Number>(1)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma1 = {vecMat1, vecMat2, vecMat3, vecMat4};

    std::shared_ptr<Expression> m1 = std::make_shared<Matrix>(ma1);

    std::shared_ptr<Expression> values = std::make_shared<RealEigenvalues>(std::dynamic_pointer_cast<Matrix>(m1));//->eval(emptyEnv);

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression: \n");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(values);
    display1->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval: \n");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(values->eval(emptyEnv));
    display2->execute();
}

void Test::DeterminantTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nMATRIX DETERMINANT TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vecMat1 = {std::make_shared<Number>(2), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::shared_ptr<Expression>> vecMat2 = {std::make_shared<Number>(-1), std::make_shared<Number>(3), std::make_shared<Number>(2)};
    std::vector<std::shared_ptr<Expression>> vecMat3 = {std::make_shared<Number>(3), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma1 = {vecMat1, vecMat2, vecMat3};
    std::shared_ptr<Expression> m1 = std::make_shared<Matrix>(ma1);
    std::shared_ptr<Expression> det = std::make_shared<Determinant>(std::dynamic_pointer_cast<Matrix>(m1));

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression: \n");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(det);
    display1->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval: \n");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(det->eval(emptyEnv));
    display2->execute();
}

void Test::DivisionMatrixTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nMATRIX DIVISION TEST\n");
    print1->execute();

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
    std::shared_ptr<Expression> m2 = std::make_shared<Division>(m1, std::make_shared<Matrix>(ma2));

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression1: \n");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(m2);
    display1->execute();
 
    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval1: \n");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(m2->eval(emptyEnv));
    display2->execute();

    std::shared_ptr<Expression> m3 = std::make_shared<Division>(m1, m1);

    std::shared_ptr<Statement> print4 = std::make_shared<Print>("\nExpression2: \n");
    print4->execute();
    std::shared_ptr<Statement> display3 = std::make_shared<Display>(m3);
    display3->execute();

    std::shared_ptr<Statement> print5 = std::make_shared<Print>("Eval2: \n");
    print5->execute();
    std::shared_ptr<Statement> display4 = std::make_shared<Display>(m3->eval(emptyEnv));
    display4->execute();


    std::shared_ptr<Expression> m4 = std::make_shared<Division>(m1, std::make_shared<Number>(10));

    std::shared_ptr<Statement> print6 = std::make_shared<Print>("\nExpression3: \n");
    print6->execute();
    std::shared_ptr<Statement> display5 = std::make_shared<Display>(m4);
    display5->execute();

    std::shared_ptr<Statement> print7 = std::make_shared<Print>("Eval3: \n");
    print7->execute();
    std::shared_ptr<Statement> display6 = std::make_shared<Display>(m4->eval(emptyEnv));
    display6->execute();
}

void Test::IntegralTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nINTEGRAL TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> to = std::make_shared<Number>(0);
    std::shared_ptr<Expression> tf = std::make_shared<Number>(10);

    std::shared_ptr<Expression> interval = std::make_shared<Pair>(to, tf);

    std::shared_ptr<Expression> letter = std::make_shared<Variable>('x');
    std::shared_ptr<Expression> sum = std::make_shared<Addition>(letter, std::make_shared<Number>(2));

    std::shared_ptr<Expression> integral = std::make_shared<Integral>(std::make_shared<Pair>(to,tf), std::make_shared<Function>(sum),  std::dynamic_pointer_cast<Variable>(letter));

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression: ");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(integral);
    display1->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval: \n");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(integral->eval(emptyEnv));
    display2->execute();

}

void Test::InterpolateTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nINTERPOLATE TEST\n");
    print1->execute();

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
    
    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression: ");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(interpolate);
    display1->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval: \n");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(interpolate->eval(emptyEnv));
    display2->execute();

}

void Test::ODEFirstOrderInitialValuesTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nORDINARY DIFFERENTIAL EQUATION FIRST ORDER INITIAL VALUES TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> to = std::make_shared<Number>(0);
    std::shared_ptr<Expression> xo = std::make_shared<Number>(0);

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(3);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(125);
    std::shared_ptr<Expression> var = std::make_shared<Variable>('x');

    std::shared_ptr<Expression> div = std::make_shared<Division>(num1,num2);
    std::shared_ptr<Expression> mult = std::make_shared<Multiplication>(div,var);

    std::shared_ptr<Expression> num3 = std::make_shared<Number>(0.6);
    std::shared_ptr<Expression> sum = std::make_shared<Subtraction>(num3, mult);

    std::shared_ptr<Expression> tFinal = std::make_shared<Number>(30);

    std::shared_ptr<Expression> ODE1 = std::make_shared<ODEFirstOrderInitialValues>(std::make_shared<Function>(sum), std::make_shared<Pair>(to,xo), std::dynamic_pointer_cast<Number>(tFinal), std::dynamic_pointer_cast<Variable>(var));

    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression1: \n");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(ODE1);
    display1->execute();
 
    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval1: \n");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(ODE1->eval(emptyEnv));
    display2->execute();

    std::shared_ptr<Expression> ODE2 = std::make_shared<ODEFirstOrderInitialValues>(std::make_shared<Function>(sum), std::make_shared<Pair>(to,xo), std::make_shared<Number>(-10), std::dynamic_pointer_cast<Variable>(var));

    std::shared_ptr<Statement> print4 = std::make_shared<Print>("\nExpression2: \n");
    print4->execute();
    std::shared_ptr<Statement> display3 = std::make_shared<Display>(ODE2);
    display3->execute();

    std::shared_ptr<Statement> print5 = std::make_shared<Print>("Eval2: \n");
    print5->execute();
    std::shared_ptr<Statement> display4 = std::make_shared<Display>(ODE2->eval(emptyEnv));
    display4->execute();

}

void Test::FindRootBisectionTest()
{
    std::shared_ptr<Statement> print1 = std::make_shared<Print>("\n\nFIND ROOT USING BISECTION TEST\n");
    print1->execute();

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> to = std::make_shared<Number>(0);
    std::shared_ptr<Expression> tf = std::make_shared<Number>(1);

    std::shared_ptr<Expression> interval = std::make_shared<Pair>(to, tf);

    std::shared_ptr<Expression> letter = std::make_shared<Variable>('x');

    std::shared_ptr<Expression> part1 = std::make_shared<Multiplication>(std::make_shared<Number>(0.1), std::make_shared<Power>(letter, std::make_shared<Number>(3)));
    std::shared_ptr<Expression> part2 = std::make_shared<Multiplication>(std::make_shared<Number>(-5), std::make_shared<Power>(letter, std::make_shared<Number>(2)));
    std::shared_ptr<Expression> part3 = std::make_shared<Addition>(std::make_shared<Multiplication>(std::make_shared<Number>(-1), letter), std::make_shared<Number>(04));

    std::shared_ptr<Expression> part4 = std::make_shared<Addition>(part3, std::make_shared<Power>(std::make_shared<EULER>(), std::make_shared<Multiplication>(std::make_shared<Number>(-1), letter)));

    std::shared_ptr<Expression> sum = std::make_shared<Addition>(part1, std::make_shared<Addition>(part2, part4));
    std::shared_ptr<Expression> finalExp = std::make_shared<Function>(sum);

    std::shared_ptr<Expression> bisection = std::make_shared<FindRootBisection>(std::dynamic_pointer_cast<Pair>(interval), std::dynamic_pointer_cast<Function>(finalExp), std::dynamic_pointer_cast<Variable>(letter));
    
    std::shared_ptr<Statement> print2 = std::make_shared<Print>("\nExpression: \n");
    print2->execute();
    std::shared_ptr<Statement> display1 = std::make_shared<Display>(bisection);
    display1->execute();

    std::shared_ptr<Statement> print3 = std::make_shared<Print>("Eval: \n");
    print3->execute();
    std::shared_ptr<Statement> display2 = std::make_shared<Display>(bisection->eval(emptyEnv));
    display2->execute();
};