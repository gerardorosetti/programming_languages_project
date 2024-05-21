#include "test.hpp"

Display& display = Display::getInstance();
Print& print = Print::getInstance();

void Test::ValuesTest()
{
    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    print.execute(nullptr,"\nVALUES TEST (DATA TYPES)\n");

    std::shared_ptr<Expression> pair1 = std::make_shared<Pair>(std::make_shared<Number>(5), std::make_shared<Number>(10));
    print.execute(nullptr,"\nPair: ");
    display.execute(pair1);

    std::vector<std::shared_ptr<Expression>> vect1 = {std::make_shared<Number>(2), std::make_shared<Number>(3), std::make_shared<Number>(10)};
    std::shared_ptr<Expression> expVect1 = std::make_shared<Vector>(vect1);

    print.execute(nullptr,"\nVector: ");
    display.execute(expVect1);

    std::vector<std::shared_ptr<Expression>> vec1 = {std::make_shared<Number>(2), std::make_shared<Number>(3)};
    std::vector<std::shared_ptr<Expression>> vec2 = {std::make_shared<Number>(4), std::make_shared<Variable>('B')};
    std::vector<std::vector<std::shared_ptr<Expression>>> mat1 = {vec1, vec2};
    std::shared_ptr<Expression> expMat1 = std::make_shared<Matrix>(mat1);

    print.execute(nullptr,"\nMatrix: \n");
    display.execute(expMat1);

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);

    print.execute(nullptr,"Number: ");
    display.execute(num1);

    print.execute(nullptr,"\nVariable: ");
    std::shared_ptr<Expression> var1 = std::make_shared<Variable>('A');

    display.execute(var1);
}

void Test::ExpressionTest()
{
    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    print.execute(nullptr,"\n\nEXPRESSIONS TEST\n");
    std::shared_ptr<Expression> num1 = std::make_shared<Number>(2);
    std::shared_ptr<Expression> var = std::make_shared<Variable>('A');
    std::shared_ptr<Expression> sum = std::make_shared<Addition>(num1,var);
    std::shared_ptr<Expression> sub = std::make_shared<Subtraction>(num1,sum);
    std::shared_ptr<Expression> mul = std::make_shared<Multiplication>(sub,var);
    std::shared_ptr<Expression> div = std::make_shared<Division>(mul,std::make_shared<Number>(10));
    std::shared_ptr<Expression> func = std::make_shared<Function>(div);
    print.execute(nullptr,"\nAddition, Subtraction, Multiplication and Division: ");
    display.execute(func);

    std::shared_ptr<Expression> var1 = std::make_shared<Variable>('x');
    std::shared_ptr<Expression> pow = std::make_shared<Power>(var1,std::make_shared<Number>(2));
    std::shared_ptr<Expression> sum1 = std::make_shared<Addition>(pow,std::make_shared<Addition>(std::make_shared<Sine>(var1),std::make_shared<Logarithm>(std::make_shared<Number>(10), var1)));
    std::shared_ptr<Expression> func2 = std::make_shared<Function>(sum1);

    print.execute(nullptr,"\nPower, Trigonometrics, ln: ");
    display.execute(func2/*->eval(emptyEnv)*/);

    /*std::shared_ptr<Expression> eq = std::make_shared<Equation>(func,func2);

    print.execute(nullptr,"\nEquation: ");
    display.execute(eq);*/

    std::shared_ptr<Expression> to = std::make_shared<Number>(0);
    std::shared_ptr<Expression> tf = std::make_shared<Number>(10);

    std::shared_ptr<Expression> interval = std::make_shared<Pair>(to, tf);

    std::shared_ptr<Expression> letter = std::make_shared<Variable>('x');
    std::shared_ptr<Expression> sum2 = std::make_shared<Addition>(letter, std::make_shared<Number>(2));

    std::shared_ptr<Expression> integral = std::make_shared<Integral>(std::make_shared<Pair>(to,tf), std::make_shared<Function>(sum2),  std::dynamic_pointer_cast<Variable>(letter));

    print.execute(nullptr, "\nIntegral: ");
    display.execute(integral);

    std::shared_ptr<Expression> xo = std::make_shared<Number>(0);

    std::shared_ptr<Expression> sum3 = std::make_shared<Addition>(std::make_shared<Multiplication>(std::make_shared<Division>(std::make_shared<Number>(-3), std::make_shared<Number>(125)),letter), std::make_shared<Number>(0.6));

    std::shared_ptr<Expression> tFinal = std::make_shared<Number>(30);

    std::shared_ptr<Expression> ODE = std::make_shared<ODEFirstOrderInitialValues>(std::make_shared<Function>(sum3), std::make_shared<Pair>(to,xo), std::dynamic_pointer_cast<Number>(tFinal), std::dynamic_pointer_cast<Variable>(letter));

    print.execute(nullptr, "\nOrdinary Differential Equation First Order, with initial values:\n");
    display.execute(ODE);
}

void Test::EnvTest()
{
    print.execute(nullptr, "\n\nENVIRONMENT TEST\n");

    Environment env = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vec1 = {std::make_shared<Number>(2), std::make_shared<Number>(3)};
    std::vector<std::shared_ptr<Expression>> vec2 = {std::make_shared<Number>(4), std::make_shared<Variable>('B')};
    std::vector<std::vector<std::shared_ptr<Expression>>> mat1 = {vec1, vec2};
    std::shared_ptr<Expression> expMat1 = std::make_shared<Matrix>(mat1);

    print.execute(nullptr,"\nMatrix without value for B\n");
    display.execute(expMat1->eval(env));

    env.push_front(std::make_pair('B', std::make_shared<Number>(10)));
    print.execute(nullptr, "Matrix with value for B added\n");
    display.execute(expMat1->eval(env));
}

void Test::AdditionTest()
{
    print.execute(nullptr, "\n\nADDITION TEST\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(2);

    std::shared_ptr<Expression> sum = std::make_shared<Addition>(num1,num2);

    print.execute(nullptr,"\nExpression: ");
    display.execute(sum);

    print.execute(nullptr,"Eval: ");
    display.execute(sum->eval(emptyEnv));
};

void Test::AdditionMatrixTest()
{
    print.execute(nullptr, "\n\nADDITION MATRIX TEST\n");

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

    print.execute(nullptr,"\nExpression1: \n");
    display.execute(sum1);

    print.execute(nullptr,"Eval1: \n");
    display.execute(sum1->eval(emptyEnv));

    std::vector<std::shared_ptr<Expression>> vec6 = {std::make_shared<Number>(1), std::make_shared<Number>(100)};
    std::vector<std::shared_ptr<Expression>> vec7 = {std::make_shared<Number>(3), std::make_shared<Variable>(9)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma3 = {vec6, vec7};
    std::shared_ptr<Expression> m3 = std::make_shared<Matrix>(ma3);
    std::shared_ptr<Expression> sum2 = std::make_shared<Addition>(m1,m3);

    print.execute(nullptr,"\nExpression2: ");
    display.execute(sum2);

    print.execute(nullptr,"Eval2: ");
    display.execute(sum2->eval(emptyEnv));
}

void Test::SubtractionTest()
{
    print.execute(nullptr, "\n\nSUBTRACTION TEST\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(2);

    std::shared_ptr<Expression> exp = std::make_shared<Subtraction>(num1,num2);

    print.execute(nullptr,"\nExpression: ");
    display.execute(exp);

    print.execute(nullptr,"Eval: ");
    display.execute(exp->eval(emptyEnv));
}

void Test::MultiplicationTest()
{
    print.execute(nullptr, "\n\nMULTIPLICATION TEST\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(2);

    std::shared_ptr<Expression> exp = std::make_shared<Multiplication>(num1, num2);

    print.execute(nullptr,"\nExpression: ");
    display.execute(exp);

    print.execute(nullptr,"Eval: ");
    display.execute(exp->eval(emptyEnv));
}

void Test::MultiplicationMatrixTest()
{
    print.execute(nullptr, "\n\nMULTIPLICATION MATRIX TEST\n");

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

    print.execute(nullptr,"\nExpression1: \n");
    display.execute(mul1);

    print.execute(nullptr,"Eval1: \n");
    display.execute(mul1->eval(emptyEnv));

    std::vector<std::shared_ptr<Expression>> vec6 = {std::make_shared<Number>(2), std::make_shared<Number>(3)};
    std::vector<std::shared_ptr<Expression>> vec7 = {std::make_shared<Number>(4), std::make_shared<Number>(19)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma3 = {vec6, vec7};
    std::shared_ptr<Expression> m3 = std::make_shared<Matrix>(ma3);

    std::shared_ptr<Expression> mul2 = std::make_shared<Multiplication>(m2,m3);

    print.execute(nullptr,"\nExpression2: \n");
    display.execute(mul2);

    print.execute(nullptr,"Eval2: \n");
    display.execute(mul2->eval(emptyEnv));


    std::shared_ptr<Expression> mul3 = std::make_shared<Multiplication>(std::make_shared<Number>(10),m3);

    print.execute(nullptr,"\nExpression3: \n");
    display.execute(mul3);

    print.execute(nullptr,"Eval3: \n");
    display.execute(mul3->eval(emptyEnv));
}

void Test::DivisionTest()
{
    print.execute(nullptr, "\n\nDIVISION TEST\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(2);

    std::shared_ptr<Expression> exp = std::make_shared<Division>(num1,num2);

    print.execute(nullptr,"\nExpression: ");
    display.execute(exp);

    print.execute(nullptr,"Eval: ");
    display.execute(exp->eval(emptyEnv));
}

void Test::PowerTest()
{
    print.execute(nullptr, "\n\nPOWER TEST\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(2);

    std::shared_ptr<Expression> exp = std::make_shared<Power>(num1,num2);

    print.execute(nullptr,"\nExpression: ");
    display.execute(exp);

    print.execute(nullptr,"Eval: ");
    display.execute(exp->eval(emptyEnv));
}

void Test::SquareRootTest()
{
    print.execute(nullptr, "\n\nSQUARE ROOT TEST\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(16);

    std::shared_ptr<Expression> exp = std::make_shared<SquareRoot>(num1);

    print.execute(nullptr,"\nExpression: ");
    display.execute(exp);

    print.execute(nullptr,"Eval: ");
    display.execute(exp->eval(emptyEnv));
}

void Test::RootTest()
{
    print.execute(nullptr, "\n\nROOT TEST\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> num1 = std::make_shared<Number>(27);
    std::shared_ptr<Expression> num2 = std::make_shared<Number>(3);

    std::shared_ptr<Expression> exp = std::make_shared<Root>(num1, num2);

    print.execute(nullptr,"\nExpression: ");
    display.execute(exp);

    print.execute(nullptr,"Eval: ");
    display.execute(exp->eval(emptyEnv));
}

void Test::TrigonometricsTest()
{
    print.execute(nullptr, "\n\nTRIGONOMETRICS TEST\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> sin = std::make_shared<Sine>(std::make_shared<PI>());
    std::shared_ptr<Expression> cos = std::make_shared<Cosine>(std::make_shared<PI>());
    std::shared_ptr<Expression> tan = std::make_shared<Tangent>(std::make_shared<PI>());
    std::shared_ptr<Expression> ctg = std::make_shared<Cotangent>(std::make_shared<PI>());
    std::shared_ptr<Expression> tan2 = std::make_shared<Tangent>(std::make_shared<Division>(std::make_shared<PI>(),std::make_shared<Number>(2)));
    std::shared_ptr<Expression> ctg2 = std::make_shared<Cotangent>(std::make_shared<Division>(std::make_shared<PI>(),std::make_shared<Number>(2)));

    print.execute(nullptr,"\nExpressions:\n");
    display.execute(sin);
    display.execute(cos);
    display.execute(tan);
    display.execute(ctg);
    display.execute(tan2);
    display.execute(ctg2);

    print.execute(nullptr,"\nEvals:\n");
    display.execute(sin->eval(emptyEnv));
    display.execute(cos->eval(emptyEnv));
    display.execute(tan->eval(emptyEnv));
    display.execute(ctg->eval(emptyEnv));
    display.execute(tan2->eval(emptyEnv));
    display.execute(ctg2->eval(emptyEnv));
}
void Test::InverseMatrixTest()
{
    print.execute(nullptr, "\n\nINVERSE MATRIX TEST\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vecMat1 = {std::make_shared<Number>(2), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::shared_ptr<Expression>> vecMat2 = {std::make_shared<Number>(-1), std::make_shared<Number>(3), std::make_shared<Number>(2)};
    std::vector<std::shared_ptr<Expression>> vecMat3 = {std::make_shared<Number>(3), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma1 = {vecMat1, vecMat2, vecMat3};
    std::shared_ptr<Expression> m1 = std::make_shared<Matrix>(ma1);

    std::shared_ptr<Expression> m1inv = std::make_shared<InverseMatrix>(std::dynamic_pointer_cast<Matrix>(m1));


    print.execute(nullptr,"\nExpression: \n");
    display.execute(m1inv);
    print.execute(nullptr,"Eval: \n");
    display.execute(m1inv->eval(emptyEnv));
}

void Test::MatrixLUTest()
{
    print.execute(nullptr, "\n\nLU MATRIX TEST\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vecMat1 = {std::make_shared<Number>(2), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::shared_ptr<Expression>> vecMat2 = {std::make_shared<Number>(-1), std::make_shared<Number>(3), std::make_shared<Number>(2)};
    std::vector<std::shared_ptr<Expression>> vecMat3 = {std::make_shared<Number>(3), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma1 = {vecMat1, vecMat2, vecMat3};
    std::shared_ptr<Expression> m1 = std::make_shared<Matrix>(ma1);

    std::shared_ptr<Expression> matrixPair = std::make_shared<MatrixLU>(std::dynamic_pointer_cast<Matrix>(m1));

    print.execute(nullptr,"\nExpression:\n");
    display.execute(matrixPair);

    print.execute(nullptr,"Eval:\n");

    display.execute(matrixPair->eval(emptyEnv));
}

void Test::TridiagonalMatrixTest()
{
    print.execute(nullptr, "\n\nTRIDIAGONAL MATRIX TEST\n");

    //test 1s

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vecMat1 = {std::make_shared<Number>(2), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::shared_ptr<Expression>> vecMat2 = {std::make_shared<Number>(-1), std::make_shared<Number>(3), std::make_shared<Number>(2)};
    std::vector<std::shared_ptr<Expression>> vecMat3 = {std::make_shared<Number>(3), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma1 = {vecMat1, vecMat2, vecMat3};
    std::shared_ptr<Expression> m1 = std::make_shared<Matrix>(ma1);

    std::shared_ptr<Expression> trid = std::make_shared<TridiagonalMatrix>(std::dynamic_pointer_cast<Matrix>(m1));

    print.execute(nullptr,"\nExpression for test 1: \n");
    display.execute(trid);

    print.execute(nullptr,"Eval for test 1: \n");
    display.execute(trid->eval(emptyEnv));

    //test 2

    std::vector<std::shared_ptr<Expression>> vecMat4 = {std::make_shared<Number>(4), std::make_shared<Number>(3), std::make_shared<Number>(2), std::make_shared<Number>(1)};
    std::vector<std::shared_ptr<Expression>> vecMat5 = {std::make_shared<Number>(3), std::make_shared<Number>(3), std::make_shared<Number>(2), std::make_shared<Number>(1)};
    std::vector<std::shared_ptr<Expression>> vecMat6 = {std::make_shared<Number>(2), std::make_shared<Number>(2), std::make_shared<Number>(2), std::make_shared<Number>(1)};
    std::vector<std::shared_ptr<Expression>> vecMat7 = {std::make_shared<Number>(1), std::make_shared<Number>(1), std::make_shared<Number>(1), std::make_shared<Number>(1)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma2 = {vecMat4, vecMat5, vecMat6, vecMat7};

    std::shared_ptr<Expression> m2 = std::make_shared<Matrix>(ma2);

    std::shared_ptr<Expression> trid2 = std::make_shared<TridiagonalMatrix>(std::dynamic_pointer_cast<Matrix>(m2));

    print.execute(nullptr,"\nExpression for test 2: \n");
    display.execute(trid2);

    print.execute(nullptr,"Eval for test 2: \n");
    display.execute(trid2->eval(emptyEnv));
}

void Test::RealEigenvaluesTest() // Only works with real numbers
{
    print.execute(nullptr, "\n\nEigenvalues Test\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vecMat1 = {std::make_shared<Number>(4), std::make_shared<Number>(3), std::make_shared<Number>(2), std::make_shared<Number>(1)};
    std::vector<std::shared_ptr<Expression>> vecMat2 = {std::make_shared<Number>(3), std::make_shared<Number>(3), std::make_shared<Number>(2), std::make_shared<Number>(1)};
    std::vector<std::shared_ptr<Expression>> vecMat3 = {std::make_shared<Number>(2), std::make_shared<Number>(2), std::make_shared<Number>(2), std::make_shared<Number>(1)};
    std::vector<std::shared_ptr<Expression>> vecMat4 = {std::make_shared<Number>(1), std::make_shared<Number>(1), std::make_shared<Number>(1), std::make_shared<Number>(1)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma1 = {vecMat1, vecMat2, vecMat3, vecMat4};

    std::shared_ptr<Expression> m1 = std::make_shared<Matrix>(ma1);

    std::shared_ptr<Expression> values = std::make_shared<RealEigenvalues>(std::dynamic_pointer_cast<Matrix>(m1));//->eval(emptyEnv);

    display.execute(values->eval(emptyEnv));
}

void Test::DeterminantTest()
{
    print.execute(nullptr, "\n\nMATRIX DETERMINANT TEST\n");
    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::vector<std::shared_ptr<Expression>> vecMat1 = {std::make_shared<Number>(2), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::shared_ptr<Expression>> vecMat2 = {std::make_shared<Number>(-1), std::make_shared<Number>(3), std::make_shared<Number>(2)};
    std::vector<std::shared_ptr<Expression>> vecMat3 = {std::make_shared<Number>(3), std::make_shared<Number>(1), std::make_shared<Number>(-3)};
    std::vector<std::vector<std::shared_ptr<Expression>>> ma1 = {vecMat1, vecMat2, vecMat3};
    std::shared_ptr<Expression> m1 = std::make_shared<Matrix>(ma1);
    std::shared_ptr<Expression> det = std::make_shared<Determinant>(std::dynamic_pointer_cast<Matrix>(m1));

    print.execute(nullptr,"\nExpression: \n");
    display.execute(det);

    print.execute(nullptr,"Eval: \n");
    display.execute(det->eval(emptyEnv));
}

void Test::DivisionMatrixTest()
{
    print.execute(nullptr, "\n\nMATRIX DIVISION TEST\n");

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

    print.execute(nullptr,"\nExpression1: \n");
    display.execute(m2);

    print.execute(nullptr,"Eval1: \n");
    display.execute(m2->eval(emptyEnv));

    std::shared_ptr<Expression> m3 = std::make_shared<Division>(m1, m1);

    print.execute(nullptr,"\nExpression2: \n");
    display.execute(m3);

    print.execute(nullptr,"Eval2: \n");
    display.execute(m3->eval(emptyEnv));

    std::shared_ptr<Expression> m4 = std::make_shared<Division>(m1, std::make_shared<Number>(10));

    print.execute(nullptr,"\nExpression3: \n");
    display.execute(m4);

    print.execute(nullptr,"Eval3: \n");
    display.execute(m4->eval(emptyEnv));
}

void Test::IntegralTest()
{
    print.execute(nullptr, "\n\nINTEGRAL TEST\n");

    Environment emptyEnv = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>{};

    std::shared_ptr<Expression> to = std::make_shared<Number>(0);
    std::shared_ptr<Expression> tf = std::make_shared<Number>(10);

    std::shared_ptr<Expression> interval = std::make_shared<Pair>(to, tf);

    std::shared_ptr<Expression> letter = std::make_shared<Variable>('x');
    std::shared_ptr<Expression> sum = std::make_shared<Addition>(letter, std::make_shared<Number>(2));

    std::shared_ptr<Expression> integral = std::make_shared<Integral>(std::make_shared<Pair>(to,tf), std::make_shared<Function>(sum),  std::dynamic_pointer_cast<Variable>(letter));

    print.execute(nullptr, "Expression: \n");
    display.execute(integral);
    print.execute(nullptr, "Eval: \n");
    display.execute(integral->eval(emptyEnv));

};

void Test::InterpolateTest()
{
    print.execute(nullptr, "\n\nINTERPOLATE TEST\n");

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

    print.execute(nullptr, "Expression: \n");
    display.execute(interpolate);

    print.execute(nullptr, "Eval: \n");
    display.execute(interpolate->eval(emptyEnv));
}

void Test::ODEFirstOrderInitialValuesTest()
{
    print.execute(nullptr, "\n\nORDINARY DIFFERENTIAL EQUATION FIRST ORDER INITIAL VALUES TEST\n");

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

    print.execute(nullptr, "Expression1: \n");
    display.execute(ODE1);

    print.execute(nullptr, "Eval1: \n");
    display.execute(ODE1->eval(emptyEnv));

    std::shared_ptr<Expression> ODE2 = std::make_shared<ODEFirstOrderInitialValues>(std::make_shared<Function>(sum), std::make_shared<Pair>(to,xo), std::make_shared<Number>(-10), std::dynamic_pointer_cast<Variable>(var));

    print.execute(nullptr, "\nExpression2: \n");
    display.execute(ODE2);

    print.execute(nullptr, "Eval2: \n");
    display.execute(ODE2->eval(emptyEnv));

}

void Test::FindRootBisectionTest()
{
    print.execute(nullptr, "\n\nFIND ROOT USING BISECTION TEST\n");

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

    print.execute(nullptr, "Expression: \n");
    display.execute(bisection);
    print.execute(nullptr, "Eval: \n");
    display.execute(bisection->eval(emptyEnv));
};