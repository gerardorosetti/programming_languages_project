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
        return std::make_shared<Subtraction>(exp1, exp2);
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
                newVec.push_back(std::make_shared<Subtraction>(matrix1[i][j], matrix2[i][j]));
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
        return std::make_shared<Multiplication>(exp1, exp2);
    }
    else if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Matrix)
    {
        auto matrix1 = std::dynamic_pointer_cast<Matrix>(element1)->getMatrixExpression();
        auto matrix2 = std::dynamic_pointer_cast<Matrix>(element2)->getMatrixExpression();
        std::vector<std::vector<std::shared_ptr<Expression>>> newMatrix;
        for (size_t i = 0; i < matrix1.size(); ++i)
        {
            if (matrix1.size() != matrix2[i].size())
            {
                return nullptr;
            }
            std::vector<std::shared_ptr<Expression>> newVec;
            for (size_t j = 0; j < matrix2[i].size(); ++j)
            {
                std::shared_ptr<Expression> acc = std::make_shared<Number>(0.0);
                for (size_t k1 = 0, k2 = 0; k1 < matrix2[i].size(); ++k1, ++k2)
                {
                    acc = std::make_shared<Addition>(acc, std::make_shared<Multiplication>(matrix1[i][k1], matrix2[k2][j]));
                }
                newVec.push_back(acc);
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
        return std::make_shared<Division>(exp1, exp2);
    }
    else if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Matrix)
    {
        auto matrix1 = std::dynamic_pointer_cast<Matrix>(element1);
        auto matrix2 = std::dynamic_pointer_cast<Matrix>(element2);

        return std::make_shared<Multiplication>(matrix1, std::make_shared<InverseMatrix>(matrix2))->eval(env);
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

std::vector<std::shared_ptr<Expression>> Vector::getVectorExpression() const
{
    return vectorExpression;
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

// Inverse Matrix
InverseMatrix::InverseMatrix(std::shared_ptr<Matrix> _matrix) : Value(DataType::Matrix), matrix(_matrix) {}
std::vector<std::vector<std::shared_ptr<Expression>>> InverseMatrix::gauss(std::vector<std::vector<std::shared_ptr<Expression>>> matrixExpression) const
{
    size_t size = matrixExpression.size();

    double matrix[size][size * 2];

    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            matrix[i][j] = std::dynamic_pointer_cast<Number>(matrixExpression[i][j])->getNumber();
        }
    }

    for (size_t i = size, k = 0; i < size * 2; ++i ,++k)
    {
        for (size_t j = size; j < size * 2; ++j)
        {
            if (i == j)
            {
                matrix[k][j] = 1.0;
            }
            else
            {
                matrix[k][j] = 0.0;
            }
        }
    }

    for (size_t i = 0; i < size - 1; ++i)
    {
        size_t primaryIndexPivot = i;
        for (size_t j = i + 1; j < size; ++j)
        {
            if (std::abs(matrix[primaryIndexPivot][i]) < std::abs(matrix[j][i]))
            {
                primaryIndexPivot = j;
            }
        }
        if (primaryIndexPivot != i)
        {
            for (size_t j = 0; j < size * 2; ++j)
            {
                std::swap(matrix[i][j], matrix[primaryIndexPivot][j]);
            }
        }

        if (matrix[i][i] == 0) // Singular Matrix Found
        {
            std::vector<std::vector<std::shared_ptr<Expression>>> newMatrix;
            for (size_t idx = 0; idx < size; ++idx)
            {
                std::vector<std::shared_ptr<Expression>> newVector;
                for (size_t j = 0; j < size; ++j)
                {
                    newVector.push_back(std::make_shared<Number>(matrix[idx][j]));
                }
                newMatrix.push_back(newVector);
            }
            return newMatrix;
        }

        for (int jRow = i + 1; jRow < size; ++jRow)
        {
            if (matrix[jRow][i] != 0)
            {
                double result = matrix[jRow][i] / matrix[i][i];
                for (int jColumn = i + 1; jColumn < size * 2; ++jColumn)
                {
                    double temp = matrix[jRow][jColumn];
                    matrix[jRow][jColumn] -= result * matrix[i][jColumn];
                    if (std::abs(matrix[jRow][jColumn]) < std::numeric_limits<double>::epsilon() * temp)
                    {
                        matrix[jRow][jColumn] = 0.0;
                    }
                }
            }
        }
    }

    if (matrix[size - 1][size - 1] == 0) // Singular Matrix Found
    {
        std::vector<std::vector<std::shared_ptr<Expression>>> newMatrix;
        for (size_t i = 0; i < size; ++i)
        {
            std::vector<std::shared_ptr<Expression>> newVector;
            for (size_t j = 0; j < size; ++j)
            {
                newVector.push_back(std::make_shared<Number>(matrix[i][j]));
            }
            newMatrix.push_back(newVector);
        }
        return newMatrix;
    }

    for (size_t m = size; m < size * 2; ++m)
    {
        matrix[size - 1][m] /= matrix[size - 1][size - 1];
        for (int newIdx = size - 2; newIdx >= 0; --newIdx)
        {
            double temp = matrix[newIdx][m];
            for (int k = newIdx + 1; k < size; ++k)
            {
                temp -= matrix[newIdx][k] * matrix[k][m];
            }
            matrix[newIdx][m] = temp / matrix[newIdx][newIdx];
        }
    }

    std::vector<std::vector<std::shared_ptr<Expression>>> newMatrix;
    for (size_t i = 0; i < size; ++i)
    {
        std::vector<std::shared_ptr<Expression>> newVector;
        for (size_t j = size; j < size * 2; ++j)
        {
            newVector.push_back(std::make_shared<Number>(matrix[i][j]));
        }
        newMatrix.push_back(newVector);
    }
    return newMatrix;
}
std::shared_ptr<Expression> InverseMatrix::eval(Environment& env) const
{
    auto evMatrix = std::dynamic_pointer_cast<Matrix>(matrix->eval(env));
    auto mat = evMatrix->getMatrixExpression();
    if (mat.size() != mat[0].size()) // Validation for a Square Matrix
    {
        return nullptr;
    }
    return std::make_shared<Matrix>(gauss(mat));
}

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