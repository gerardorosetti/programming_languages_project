#include <iostream>
#include "expressions.hpp"

// Value
Value::Value(DataType _dataType) : dataType{_dataType} {}
DataType Value::getDataType() const
{
    return dataType;
}

// Unary Expression
UnaryExpression::UnaryExpression(std::shared_ptr<Expression> _expression) : expression(_expression) {}

// Binary Expression
BinaryExpression::BinaryExpression(std::shared_ptr<Expression> _leftExpression, std::shared_ptr<Expression> _rigthExpression) : leftExpression(_leftExpression), rigthExpression(_rigthExpression) {}

// Number
Number::Number(double _number) : Value(DataType::Number), number{_number} {}
std::shared_ptr<Expression> Number::eval(Environment& env) const
{
    return std::make_shared<Number>(number);
}
double Number::getNumber() const
{
    return number;
}

// Variable
Variable::Variable(char _variable) : Value(DataType::Variable), variable{_variable} {}
std::shared_ptr<Expression> Variable::eval(Environment& env) const
{
    if (!env.empty())
    {
        for (auto par : env)
        {
            if (par.first == variable)
            {
                auto test = std::dynamic_pointer_cast<Number>(par.second->eval(env));
                return test;
            }
        }
        return nullptr;
    }
    return std::make_shared<Variable>(variable);
}
char Variable::getVariable() const
{
    return variable;
}

// Display
Display::Display(std::shared_ptr<Expression> _exp)
{
    auto value = std::dynamic_pointer_cast<Value>(_exp);
    if (value == nullptr)
    {
        std::cout << "COULD NOT DISPLAY A NON VALUE EXPRESSION" << std::endl;
        return;
    }
    if (value->getDataType() == DataType::Matrix)
    {
        auto matrixExpression = std::dynamic_pointer_cast<Matrix>(_exp)->getMatrixExpression();
        std::cout << "Matrix =\n\n";
        for (std::vector<std::shared_ptr<Expression>> vec : matrixExpression)
        {
            for (std::shared_ptr<Expression> exp : vec)
            {
                auto num = std::dynamic_pointer_cast<Number>(exp);
                if (num == nullptr)
                {
                    std::cout << "cannot display data type incorrect" << std::endl;
                    return;
                }
                std::cout << " " << num->getNumber();
            }
            std::cout << std::endl;
        }
    }
}


// Addition
std::shared_ptr<Expression> Addition::eval(Environment& env) const
{
    auto exp1 = leftExpression->eval(env);
    auto exp2 = rigthExpression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    auto element2 = std::dynamic_pointer_cast<Value>(exp2);
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return std::make_shared<Addition>(exp1, exp2);
    }
    else if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Matrix)
    {
        auto matrix1 = std::dynamic_pointer_cast<Matrix>(element1)->getMatrixExpression();
        auto matrix2 = std::dynamic_pointer_cast<Matrix>(element2)->getMatrixExpression();
        if (matrix1.size() != matrix2.size())
        {
            return nullptr;
        }
        std::vector<std::vector<std::shared_ptr<Expression>>> newMatrix;
        for (size_t i = 0; i < matrix1.size(); ++i)
        {
            if (matrix1[i].size() != matrix2[i].size())
            {
                return nullptr;
            }
            std::vector<std::shared_ptr<Expression>> newVec;
            for (size_t j = 0; j < matrix1[i].size(); ++j)
            {
                //auto add = Addition(matrix1[i][j], matrix2[i][j]);
                //std::cout << std::dynamic_pointer_cast<Number>(matrix1[i][j]->eval(env))->getNumber() << " - " << std::dynamic_pointer_cast<Number>(matrix2[i][j]->eval(env))->getNumber() << std::endl;
                newVec.push_back(std::make_shared<Addition>(matrix1[i][j], matrix2[i][j]));
            }
            newMatrix.push_back(newVec);
        }
        return std::make_shared<Matrix>(newMatrix)->eval(env);
    }
    auto num1 = std::dynamic_pointer_cast<Number>(exp1);
    auto num2 = std::dynamic_pointer_cast<Number>(exp2);
    if (num1 == nullptr || num2 == nullptr)
    {
        return nullptr;
    }
    double result = num1->getNumber() + num2->getNumber();
    return std::make_shared<Number>(result);
};

//Subtraction
std::shared_ptr<Expression> Subtraction::eval(Environment& env) const
{
    auto exp1 = leftExpression->eval(env);
    auto exp2 = rigthExpression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    auto element2 = std::dynamic_pointer_cast<Value>(exp2);
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return std::make_shared<Addition>(exp1, exp2);
    }

    auto num1 = std::dynamic_pointer_cast<Number>(exp1);
    auto num2 = std::dynamic_pointer_cast<Number>(exp2);
    if (num1 == nullptr || num2 == nullptr)
    {
        return nullptr;
    }
    double result = num1->getNumber() - num2->getNumber();
    return std::make_shared<Number>(result);
}

//Multiplication
std::shared_ptr<Expression> Multiplication::eval(Environment& env) const
{
    auto exp1 = leftExpression->eval(env);
    auto exp2 = rigthExpression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    auto element2 = std::dynamic_pointer_cast<Value>(exp2);
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return std::make_shared<Addition>(exp1, exp2);
    }

    auto num1 = std::dynamic_pointer_cast<Number>(exp1);
    auto num2 = std::dynamic_pointer_cast<Number>(exp2);
    if (num1 == nullptr || num2 == nullptr)
    {
        return nullptr;
    }
    double result = num1->getNumber() * num2->getNumber();
    return std::make_shared<Number>(result);
}

//Division
std::shared_ptr<Expression> Division::eval(Environment& env) const
{
    auto exp1 = leftExpression->eval(env);
    auto exp2 = rigthExpression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    auto element2 = std::dynamic_pointer_cast<Value>(exp2);
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return std::make_shared<Addition>(exp1, exp2);
    }
    auto num1 = std::dynamic_pointer_cast<Number>(exp1);
    auto num2 = std::dynamic_pointer_cast<Number>(exp2);
    if (num1 == nullptr || num2 == nullptr)
    {
        return nullptr;
    }
    double result = num1->getNumber() / num2->getNumber();
    return std::make_shared<Number>(result);
}

//Power
std::shared_ptr<Expression> Power::eval(Environment& env) const
{
    auto exp1 = leftExpression->eval(env);
    auto exp2 = rigthExpression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    auto element2 = std::dynamic_pointer_cast<Value>(exp2);
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return std::make_shared<Addition>(exp1, exp2);
    }
    auto num1 = std::dynamic_pointer_cast<Number>(exp1);
    auto num2 = std::dynamic_pointer_cast<Number>(exp2);
    if (num1 == nullptr || num2 == nullptr)
    {
        return nullptr;
    }
    double result = std::pow(num1->getNumber(), num2->getNumber());
    return std::make_shared<Number>(result);
}

//NaturalLogarithm
std::shared_ptr<Expression> NaturalLogarithm::eval(Environment& env) const
{
    auto exp1 = expression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    if(element1->getDataType() == DataType::Variable)
    {
        return std::make_shared<NaturalLogarithm>(exp1);
    }
    auto num1 = std::dynamic_pointer_cast<Number>(exp1);
    if (num1 == nullptr)
    {
        return nullptr;
    }
    double result = std::log(num1->getNumber());
    return std::make_shared<Number>(result);
}

//Logarithm
std::shared_ptr<Expression> Logarithm::eval(Environment& env) const
{
    auto exp1 = leftExpression->eval(env);
    auto exp2 = rigthExpression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    auto element2 = std::dynamic_pointer_cast<Value>(exp2);
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return std::make_shared<Addition>(exp1, exp2);
    }
    auto num1 = std::dynamic_pointer_cast<Number>(exp1);
    auto num2 = std::dynamic_pointer_cast<Number>(exp2);
    if (num1 == nullptr || num2 == nullptr)
    {
        return nullptr;
    }
    double result = std::log(num1->getNumber()) / std::log(num2->getNumber());
    return std::make_shared<Number>(result);
}

//Sine
std::shared_ptr<Expression> Sine::eval(Environment& env) const
{
   auto exp1 = expression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    if(element1->getDataType() == DataType::Variable)
    {
        return std::make_shared<Sine>(exp1);
    }
    auto num1 = std::dynamic_pointer_cast<Number>(exp1);
    if (num1 == nullptr)
    {
        return nullptr;
    }
    double result = std::sin(num1->getNumber());
    return std::make_shared<Number>(result);
}

//Cosine
std::shared_ptr<Expression> Cosine::eval(Environment& env) const
{
    auto exp1 = expression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    if(element1->getDataType() == DataType::Variable)
    {
        return std::make_shared<Cosine>(exp1);
    }
    auto num1 = std::dynamic_pointer_cast<Number>(exp1);
    if (num1 == nullptr)
    {
        return nullptr;
    }
    double result = std::cos(num1->getNumber());
    return std::make_shared<Number>(result);
}

//Tangent
std::shared_ptr<Expression> Tangent::eval(Environment& env) const
{
    auto exp1 = expression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    if(element1->getDataType() == DataType::Variable)
    {
        return std::make_shared<Tangent>(exp1);
    }
    auto num1 = std::dynamic_pointer_cast<Number>(exp1);
    if (num1 == nullptr)
    {
        return nullptr;
    }
    double result = std::tan(num1->getNumber());
    return std::make_shared<Number>(result);
}

//Cotangent
std::shared_ptr<Expression> Cotangent::eval(Environment& env) const
{
    auto exp1 = expression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    if(element1->getDataType() == DataType::Variable)
    {
        return std::make_shared<Cotangent>(exp1);
    }
    auto num1 = std::dynamic_pointer_cast<Number>(exp1);
    if (num1 == nullptr)
    {
        return nullptr;
    }
    double result = 1 / std::tan(num1->getNumber());
    return std::make_shared<Number>(result);
}

//Pair
Pair::Pair(std::shared_ptr<Expression> _first, std::shared_ptr<Expression> _second) : Value(DataType::Pair), first{_first}, second{_second} {}

std::shared_ptr<Expression> Pair::eval(Environment& env) const
{
    auto exp1 = first->eval(env);
    auto exp2 = second->eval(env);
    return std::make_shared<Pair>(exp1, exp2);
}

std::shared_ptr<Expression> Pair::getFirst()
{
    return first;
}

std::shared_ptr<Expression> Pair::getSecond()
{
    return second;
}

//PairFirst
std::shared_ptr<Expression> PairFirst::eval(Environment& env) const
{
    auto exp = expression->eval(env);
    auto pair = std::dynamic_pointer_cast<Pair>(exp);
    if (pair == nullptr)
    {
        return nullptr;
    }
    return pair->getFirst()->eval(env);
}

//PairSecond
std::shared_ptr<Expression> PairSecond::eval(Environment& env) const
{
    auto exp = expression->eval(env);
    auto pair = std::dynamic_pointer_cast<Pair>(exp);
    if (pair == nullptr)
    {
        return nullptr;
    }
    return pair->getSecond()->eval(env);
}

//Vector
Vector::Vector(std::vector<std::shared_ptr<Expression>> _vectorExpression) : Value(DataType::Vector), vectorExpression(_vectorExpression) {}
std::shared_ptr<Expression> Vector::eval(Environment& env) const
{
    std::vector<std::shared_ptr<Expression>> newVector;
    for (auto exp : vectorExpression)
    {
        auto element = exp->eval(env);
        if (element = nullptr)
        {
            return nullptr;
        }
        newVector.push_back(element);
    }
    return std::make_shared<Vector>(newVector);
}

//Matrix
Matrix::Matrix(std::vector<std::vector<std::shared_ptr<Expression>>> _matrixExpression) : Value(DataType::Matrix), matrixExpression(_matrixExpression) {}
std::shared_ptr<Expression> Matrix::eval(Environment& env) const
{
    std::vector<std::vector<std::shared_ptr<Expression>>> newMatrix;
    for (std::vector<std::shared_ptr<Expression>> vec : matrixExpression)
    {
        std::vector<std::shared_ptr<Expression>> newVector;
        for (std::shared_ptr<Expression> exp : vec)
        {
            auto element = exp->eval(env);
            auto num = std::dynamic_pointer_cast<Number>(element);
            /*if (element = nullptr)
            {
                return nullptr;
            }*/
            if (num == nullptr)
            {
                return nullptr;
            }
            newVector.push_back(num);
        }
        newMatrix.push_back(newVector);
    }
    return std::make_shared<Matrix>(newMatrix);
}
std::vector<std::vector<std::shared_ptr<Expression>>> Matrix::getMatrixExpression() const
{
    return matrixExpression;
}
/*void Matrix::displayMatrix() const
{
    std::cout << "Matrix =\n\n";
    for (std::vector<std::shared_ptr<Expression>> vec : matrixExpression)
    {
        for (std::shared_ptr<Expression> exp : vec)
        {
            auto num = std::dynamic_pointer_cast<Number>(exp);
            if (num == nullptr)
            {
                std::cout << "cannot display data type incorrect" << std::endl;
                return;
            }
            std::cout << " " << num->getNumber();
        }
        std::cout << std::endl;
    }
}*/

//Equation
std::shared_ptr<Expression> Equation::eval(Environment& env) const
{
    auto exp1 = leftExpression->eval(env);
    auto exp2 = rigthExpression->eval(env);
    if (exp1 == nullptr || exp2 == nullptr)
    {
        return nullptr;
    }
    return std::make_shared<Equation>(exp1, exp2);
}

//Function
std::shared_ptr<Expression> Function::eval(Environment& env) const
{
    auto exp = expression->eval(env);
    if (exp == nullptr)
    {
        return nullptr;
    }
    return exp;
}

//Integral
Integral::Integral(std::shared_ptr<Pair> _interval, std::shared_ptr<Function> _function, std::shared_ptr<Variable> _variable) : interval(_interval), function(_function), variable(_variable) {}
std::shared_ptr<Number> Integral::simpsonMethod(double a, double b, int n, std::shared_ptr<Expression> function, Environment& env, std::shared_ptr<Variable> variable) const
{
    double s = 0.0;
    double ss = 0.0;
    int ls = (n / 2 * 2 == n) ? 0 : 3;
    double h = (b - a) / n;
    if (ls == 3)
    {
        for (size_t i = 0; i <= 3; ++i)
        {
            double x = a + h * i;
            double w = (i == 0 || i == 3) ? 1 : 3;
            env.push_front(std::make_pair(variable->getVariable(), std::make_shared<Number>(x)));
            std::shared_ptr<Number> funcResult = std::dynamic_pointer_cast<Number>(function->eval(env));
            if (funcResult == nullptr)
            {
                return funcResult;
            }
            ss = ss + w * funcResult->getNumber();
        }
        ss = ss * h * 3 / 8;
        if (n == 3)
        {
            return std::make_shared<Number>(ss);
        }
    }
    for (size_t i = 0; i <= n - ls; ++i)
    {
        double x = a + h * (i + ls);
        double w = 2;
        if (int(i / 2) * 2 + 1 == i)
        {
            w = 4;
        }
        if (i == 0 || i == n - ls)
        {
            w = 1;
        }
        env.push_front(std::make_pair(variable->getVariable(), std::make_shared<Number>(x)));
        std::shared_ptr<Number> funcResult = std::dynamic_pointer_cast<Number>(function->eval(env));
        if (funcResult == nullptr)
        {
            return funcResult;
        }
        s = s + w * funcResult->getNumber();
    }
    return std::make_shared<Number>(ss + s * h / 3);
}
std::shared_ptr<Expression> Integral::eval(Environment& env) const
{
    auto inter = interval->eval(env);
    auto to = std::dynamic_pointer_cast<Number>(PairFirst{inter}.eval(env));
    auto tf = std::dynamic_pointer_cast<Number>(PairSecond{inter}.eval(env));
    if (to->getDataType() != DataType::Number || tf->getDataType() != DataType::Number)
    {
        return nullptr;
    }
    double a = to->getNumber();
    double b = tf->getNumber();
    std::shared_ptr<Number> num = simpsonMethod(a, b, 100, function, env, variable);
    if (num == nullptr)
    {
        return nullptr;
    }
    return num;
}

//ODEInitialValues
ODEInitialValues::ODEInitialValues(std::shared_ptr<Function> _function, std::shared_ptr<Pair> _values) : function(_function), values(_values) {}
std::shared_ptr<Expression> ODEInitialValues::eval(Environment& env) const
{
    auto inter = values->eval(env);
    auto to = std::dynamic_pointer_cast<Number>(std::dynamic_pointer_cast<PairFirst>(inter)->eval(env));
    auto tf = std::dynamic_pointer_cast<Number>(std::dynamic_pointer_cast<PairSecond>(inter)->eval(env));
    if (to->getDataType() != DataType::Number || tf->getDataType() != DataType::Number)
    {
        return nullptr;
    }
    return nullptr;
}

// Interpolate
Interpolate::Interpolate(std::vector<std::shared_ptr<Expression>> _vectorExpression, std::shared_ptr<Number> _numInter) : Vector(_vectorExpression), numInter(_numInter) {}
std::shared_ptr<Expression> Interpolate::eval(Environment& env) const
{
    std::vector<double> x;
    std::vector<double> f;
    int n = vectorExpression.size();
    double xa = numInter->getNumber();
    for (auto exp : vectorExpression)
    {
        auto pair = std::dynamic_pointer_cast<Pair>(exp);
        if (pair->getDataType() != DataType::Pair)
        {
            return nullptr;
        }
        x.push_back(std::dynamic_pointer_cast<Number>(PairFirst{pair}.eval(env))->getNumber());
        f.push_back(std::dynamic_pointer_cast<Number>(PairSecond{pair}.eval(env))->getNumber());
    }
    double y_res = 0.0;
    for (int i = 0; i < n; ++i) {
        double z = 1.0;
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                z = z * (xa - x[j]) / (x[i] - x[j]);
            }
        }
        y_res += z * f[i];
    }
    return std::make_shared<Number>(y_res);
}