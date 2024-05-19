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

//Impossible
Impossible::Impossible() : Value(DataType::Impossible) {}

std::shared_ptr<Expression> Impossible::eval(Environment& env) const
{
    return std::shared_ptr<Impossible>();
}
std::string Impossible::toString() const noexcept
{
    return value;
}
// Number
Number::Number(double _number) : Value(DataType::Number), number{_number} {}
std::shared_ptr<Expression> Number::eval(Environment& env) const
{
    return std::make_shared<Number>(number);
}
std::string Number::toString() const noexcept
{
    return std::to_string(number);
}
double Number::getNumber() const
{
    return number;
}

// Constants
PI::PI() : Value(DataType::Number) {}
std::shared_ptr<Expression> PI::eval(Environment& env) const
{
    return std::make_shared<Number>(M_PI);
}
std::string PI::toString() const noexcept
{
    return "π";
}
EULER::EULER() : Value(DataType::Number){}
std::shared_ptr<Expression> EULER::eval(Environment& env) const
{
    return std::make_shared<Number>(M_E);
}
std::string EULER::toString() const noexcept
{
    return "e";
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
std::string Variable::toString() const noexcept
{
    return std::string{variable};
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

    if (element1 == nullptr || element2 == nullptr)
    {
        return std::make_shared<Addition>(exp1, exp2);
    }
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return std::make_shared<Addition>(exp1, exp2);
    }
    if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Matrix)
    {
        auto matrix1 = std::dynamic_pointer_cast<Matrix>(element1)->getMatrixExpression();
        auto matrix2 = std::dynamic_pointer_cast<Matrix>(element2)->getMatrixExpression();
        if (matrix1.size() != matrix2.size())
        {
            std::shared_ptr<Expression> imp = std::make_shared<Impossible>();
            return imp;
        }
        std::vector<std::vector<std::shared_ptr<Expression>>> newMatrix;
        for (size_t i = 0; i < matrix1.size(); ++i)
        {
            if (matrix1[i].size() != matrix2[i].size())
            {
                std::shared_ptr<Expression> imp = std::make_shared<Impossible>();
                return imp;
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
std::string Addition::toString() const noexcept
{
    return leftExpression->toString() + " + " + rigthExpression->toString();
}

//Subtraction
std::shared_ptr<Expression> Subtraction::eval(Environment& env) const
{
    auto exp1 = leftExpression->eval(env);
    auto exp2 = rigthExpression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    auto element2 = std::dynamic_pointer_cast<Value>(exp2);
    if (element1 == nullptr || element2 == nullptr)
    {
        return std::make_shared<Subtraction>(exp1, exp2);
    }    
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return std::make_shared<Subtraction>(exp1, exp2);
    }
    if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Matrix)
    {
        auto matrix1 = std::dynamic_pointer_cast<Matrix>(element1)->getMatrixExpression();
        auto matrix2 = std::dynamic_pointer_cast<Matrix>(element2)->getMatrixExpression();
        if (matrix1.size() != matrix2.size())
        {
            std::shared_ptr<Expression> imp = std::make_shared<Impossible>();
            return imp;
        }
        std::vector<std::vector<std::shared_ptr<Expression>>> newMatrix;
        for (size_t i = 0; i < matrix1.size(); ++i)
        {
            if (matrix1[i].size() != matrix2[i].size())
            {
                std::shared_ptr<Expression> imp = std::make_shared<Impossible>();
                return imp;
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

std::string Subtraction::toString() const noexcept
{
    return leftExpression->toString() + " - " + rigthExpression->toString();
}

//Multiplication
std::shared_ptr<Expression> Multiplication::eval(Environment& env) const
{
    auto exp1 = leftExpression->eval(env);
    auto exp2 = rigthExpression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    auto element2 = std::dynamic_pointer_cast<Value>(exp2);
    if (element1 == nullptr || element2 == nullptr)
    {
        return std::make_shared<Multiplication>(exp1, exp2);
    }
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return std::make_shared<Multiplication>(exp1, exp2);
    }
    if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Matrix)
    {
        auto matrix1 = std::dynamic_pointer_cast<Matrix>(element1)->getMatrixExpression();
        auto matrix2 = std::dynamic_pointer_cast<Matrix>(element2)->getMatrixExpression();
        std::vector<std::vector<std::shared_ptr<Expression>>> newMatrix;
        if (matrix1[0].size() != matrix2.size())
        {
            std::shared_ptr<Expression> imp = std::make_shared<Impossible>();
            return imp;
        }
        for (size_t i = 0; i < matrix1.size(); ++i)
        {
            std::vector<std::shared_ptr<Expression>> newVec;
            for (size_t j = 0; j < matrix2[0].size(); ++j)
            {
                std::shared_ptr<Expression> acc = std::make_shared<Number>(0.0);
                for (size_t k = 0; k < matrix1[i].size(); ++k)
                {
                    auto mul = std::make_shared<Multiplication>(matrix1[i][k], matrix2[k][j]);
                    acc = std::make_shared<Addition>(acc, mul);
                }
                newVec.push_back(acc);
            }
            newMatrix.push_back(newVec);
        }
        return std::make_shared<Matrix>(newMatrix)->eval(env);
    }
    if (element1->getDataType() == DataType::Number && element2->getDataType() == DataType::Matrix)
    {
        auto num = std::dynamic_pointer_cast<Number>(element1);
        auto matrix1 = std::dynamic_pointer_cast<Matrix>(element2)->getMatrixExpression();
        std::vector<std::vector<std::shared_ptr<Expression>>> newMatrix;
        for (std::vector<std::shared_ptr<Expression>> vec : matrix1)
        {
            std::vector<std::shared_ptr<Expression>> newVec;
            for (std::shared_ptr<Expression> exp : vec)
            {
                std::shared_ptr<Expression> newVal = std::make_shared<Multiplication>(num,exp);
                newVec.push_back(newVal);
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

std::string Multiplication::toString() const noexcept
{
    return "("+ leftExpression->toString()+ ") * (" + rigthExpression->toString() +")";
}

//Division
std::shared_ptr<Expression> Division::eval(Environment& env) const
{
    auto exp1 = leftExpression->eval(env);
    auto exp2 = rigthExpression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    auto element2 = std::dynamic_pointer_cast<Value>(exp2);
    if (element1 == nullptr || element2 == nullptr)
    {
        return std::make_shared<Division>(exp1, exp2);
    }
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return std::make_shared<Division>(exp1, exp2);
    }
    if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Matrix)
    {
        auto matrix1 = std::dynamic_pointer_cast<Matrix>(element1);
        auto matrix2 = std::dynamic_pointer_cast<Matrix>(element2);

        return std::make_shared<Multiplication>(matrix1, std::make_shared<InverseMatrix>(matrix2))->eval(env);
    }
    if (element1->getDataType() == DataType::Matrix && element2->getDataType() == DataType::Number)
    {
        auto matrix1 = std::dynamic_pointer_cast<Matrix>(element1);
        auto num = std::dynamic_pointer_cast<Number>(element2)->getNumber();
        std::shared_ptr<Expression> newNum = std::make_shared<Number>(1/num);
        return std::make_shared<Multiplication>(newNum, matrix1)->eval(env);
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

std::string Division::toString() const noexcept
{
    return "(" + leftExpression->toString() + ")/(" + rigthExpression->toString() + ")";
}

//Power
std::shared_ptr<Expression> Power::eval(Environment& env) const
{
    auto exp1 = leftExpression->eval(env);
    auto exp2 = rigthExpression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    auto element2 = std::dynamic_pointer_cast<Value>(exp2);
    if (element1 == nullptr || element2 == nullptr)
    {
        return std::make_shared<Power>(exp1, exp2);
    }
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return std::make_shared<Power>(exp1, exp2);
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

std::string Power::toString() const noexcept
{
    return "("+ leftExpression->toString() + ")^(" + rigthExpression->toString() + ")";
}

//NaturalLogarithm
std::shared_ptr<Expression> NaturalLogarithm::eval(Environment& env) const
{
    auto exp1 = expression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    if (element1 == nullptr)
    {
        return std::make_shared<NaturalLogarithm>(exp1);
    }
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

std::string NaturalLogarithm::toString() const noexcept
{
    return "ln(" + expression->toString() + ")";
}

//Logarithm
std::shared_ptr<Expression> Logarithm::eval(Environment& env) const
{
    auto exp1 = leftExpression->eval(env);
    auto exp2 = rigthExpression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    auto element2 = std::dynamic_pointer_cast<Value>(exp2);
    if (element1 == nullptr || element2 == nullptr)
    {
        return std::make_shared<Logarithm>(exp1, exp2);
    }
    if (element1->getDataType() == DataType::Variable || element2->getDataType() == DataType::Variable)
    {
        return std::make_shared<Logarithm>(exp1, exp2);
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

std::string Logarithm::toString() const noexcept
{
    return "lg" + leftExpression->toString() + "(" + rigthExpression->toString() + ")";
}

//Sine
std::shared_ptr<Expression> Sine::eval(Environment& env) const
{
    auto exp1 = expression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    if (element1 == nullptr)
    {
        return std::make_shared<Sine>(exp1);
    }
    if (element1->getDataType() == DataType::Variable)
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

std::string Sine::toString() const noexcept
{
    return "Sin(" + expression->toString() + ")";
}

//Cosine
std::shared_ptr<Expression> Cosine::eval(Environment& env) const
{
    auto exp1 = expression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    if (element1 == nullptr)
    {
        return std::make_shared<Cosine>(exp1);
    }
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

std::string Cosine::toString() const noexcept
{
    return "cos(" + expression->toString() + ")";
}

//Tangent
std::shared_ptr<Expression> Tangent::eval(Environment& env) const
{
    auto exp1 = expression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    if (element1 == nullptr)
    {
        return std::make_shared<Tangent>(exp1);
    }
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

std::string Tangent::toString() const noexcept
{
    return "Tag(" + expression->toString() + ")";
}

//Cotangent
std::shared_ptr<Expression> Cotangent::eval(Environment& env) const
{
    auto exp1 = expression->eval(env);
    auto element1 = std::dynamic_pointer_cast<Value>(exp1);
    if (element1 == nullptr)
    {
        return std::make_shared<Cotangent>(exp1);
    }
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

std::string Cotangent::toString() const noexcept
{
    return "Ctg(" + expression->toString() + ")";
}

//Pair
Pair::Pair(std::shared_ptr<Expression> _first, std::shared_ptr<Expression> _second) : Value(DataType::Pair), first{_first}, second{_second} {}

std::shared_ptr<Expression> Pair::eval(Environment& env) const
{
    auto exp1 = first->eval(env);
    auto exp2 = second->eval(env);
    return std::make_shared<Pair>(exp1, exp2);
}

std::string Pair::toString() const noexcept
{
    return "[" + first->toString() + ", " + second->toString() + "]";
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

std::string PairFirst::toString() const noexcept
{
    return "";
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

std::string PairSecond::toString() const noexcept
{
    return "";
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
std::string Vector::toString() const noexcept
{
    std::string result = "[  ";
    for (auto exp : vectorExpression)
    {
        std::string element = exp->toString();
        result += element +"  ";
    }
    result += "]";
    return result;
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
    size_t rowSize = matrixExpression[0].size();
    for (std::vector<std::shared_ptr<Expression>> vec : matrixExpression)
    {
        if (vec.size() != rowSize)
        {
            return nullptr;
        }
        std::vector<std::shared_ptr<Expression>> newVector;
        for (std::shared_ptr<Expression> exp : vec)
        {
            auto element = exp->eval(env);
            auto num = std::dynamic_pointer_cast<Number>(element);
            if (num == nullptr)
            {
                newVector.push_back(element);
            }
            else
            {
                newVector.push_back(num);
            }
        }
        newMatrix.push_back(newVector);
    }
    return std::make_shared<Matrix>(newMatrix);
}
std::string Matrix::toString() const noexcept
{
    std::string result;
    for (std::vector<std::shared_ptr<Expression>> vec : matrixExpression)
    {
        for (std::shared_ptr<Expression> exp : vec)
        {
            std::string element = exp->toString();
            result += element +" ";
        }
        result += "\n";
    }
    return result;
}
std::vector<std::vector<std::shared_ptr<Expression>>> Matrix::getMatrixExpression() const
{
    return matrixExpression;
}

// Inverse Matrix
InverseMatrix::InverseMatrix(std::shared_ptr<Matrix> _matrix) : Value(DataType::Matrix), matrix(_matrix) {}
std::shared_ptr<Expression> InverseMatrix::gauss(std::vector<std::vector<std::shared_ptr<Expression>>> matrixExpression) const
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
            /*std::vector<std::vector<std::shared_ptr<Expression>>> newMatrix;
            for (size_t idx = 0; idx < size; ++idx)
            {
                std::vector<std::shared_ptr<Expression>> newVector;
                for (size_t j = 0; j < size; ++j)
                {
                    newVector.push_back(std::make_shared<Number>(matrix[idx][j]));
                }
                newMatrix.push_back(newVector);
            }
            return newMatrix;*/
            return std::make_shared<Impossible>();
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
        /*std::vector<std::vector<std::shared_ptr<Expression>>> newMatrix;
        for (size_t i = 0; i < size; ++i)
        {
            std::vector<std::shared_ptr<Expression>> newVector;
            for (size_t j = 0; j < size; ++j)
            {
                newVector.push_back(std::make_shared<Number>(matrix[i][j]));
            }
            newMatrix.push_back(newVector);
        }
        return newMatrix;*/
        return std::make_shared<Impossible>();
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
    return std::make_shared<Matrix>(newMatrix);
}
std::shared_ptr<Expression> InverseMatrix::eval(Environment& env) const
{
    auto evMatrix = std::dynamic_pointer_cast<Matrix>(matrix->eval(env));
    auto mat = evMatrix->getMatrixExpression();
    if (mat.size() != mat[0].size())
    {
        return std::make_shared<Impossible>();
    }
    return gauss(mat);
}

std::string InverseMatrix::toString() const noexcept
{
    return "Matrix to Inverse:\n" + matrix->toString();
}

// LU Matrix
MatrixLU::MatrixLU(std::shared_ptr<Matrix> _matrix) : Value(DataType::Matrix), matrix(_matrix) {}
std::pair<std::vector<std::vector<std::shared_ptr<Expression>>>, std::vector<std::vector<std::shared_ptr<Expression>>>> MatrixLU::lowerUpperDecomposition(std::vector<std::vector<std::shared_ptr<Expression>>> matrixExpression) const
{
    size_t size = matrixExpression.size();

    double matrix[size][size];

    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            matrix[i][j] = std::dynamic_pointer_cast<Number>(matrixExpression[i][j])->getNumber();
        }
    }

    auto L = std::vector<std::vector<double>>(size, std::vector<double>(size, 0.0));
    auto U = std::vector<std::vector<double>>(size, std::vector<double>(size, 0.0));
    for (int i = 0; i < size; ++i)
    {
        L[i][i] = 1.0;
        for (int j = 0; j < size; ++j)
        {
            U[i][j] = matrix[i][j];
        }
    }
    for (int k = 0; k < size - 1; ++k)
    {
        int maxIndex = k;
        double maxVal = std::abs(U[k][k]);
        for (int i = k + 1; i < size; ++i)
        {
            if (std::abs(U[i][k]) > maxVal)
            {
                maxVal = std::abs(U[i][k]);
                maxIndex = i;
            }
        }
        if (maxIndex != k)
        {
            //std::swap(P[k], P[maxIndex]);
            std::swap(U[k], U[maxIndex]);
            for (int i = 0; i < k; ++i)
            {
                std::swap(L[k][i], L[maxIndex][i]);
            }
        }
        for (int i = k + 1; i < size; ++i)
        {
            L[i][k] = U[i][k] / U[k][k];
            for (int j = k; j < size; ++j)
            {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }
    }
    std::vector<std::vector<std::shared_ptr<Expression>>> newMatrixLower;
    std::vector<std::vector<std::shared_ptr<Expression>>> newMatrixUpper;
    for (size_t i = 0; i < size; ++i)
    {
        std::vector<std::shared_ptr<Expression>> newVectorLower;
        std::vector<std::shared_ptr<Expression>> newVectorUpper;
        for (size_t j = 0; j < size; ++j)
        {
            newVectorLower.push_back(std::make_shared<Number>(L[i][j]));
            newVectorUpper.push_back(std::make_shared<Number>(U[i][j]));
        }
        newMatrixLower.push_back(newVectorLower);
        newMatrixUpper.push_back(newVectorUpper);
    }
    return std::make_pair(newMatrixLower, newMatrixUpper);
}
std::shared_ptr<Expression> MatrixLU::eval(Environment& env) const
{
    auto evMatrix = std::dynamic_pointer_cast<Matrix>(matrix->eval(env));
    auto mat = evMatrix->getMatrixExpression();
    if (mat.size() != mat[0].size()) // Validation for a Square Matrix
    {
        return nullptr;
    }
    auto matrixPair = lowerUpperDecomposition(mat);
    return std::make_shared<Pair>(std::make_shared<Matrix>(matrixPair.first), std::make_shared<Matrix>(matrixPair.second));
}

std::string MatrixLU::toString() const noexcept
{
    return "Matrix to lower Upper Decomposition: \n"+ matrix->toString();
}
// Tridiagonal Matrix
TridiagonalMatrix::TridiagonalMatrix(std::shared_ptr<Matrix> _matrix) : Value(DataType::Matrix), matrix(_matrix) {}
std::vector<std::vector<std::shared_ptr<Expression>>> TridiagonalMatrix::tridiagonal(std::vector<std::vector<std::shared_ptr<Expression>>> matrix) const
{
    size_t N = matrix.size();
    std::vector<std::vector<double>> A(N + 1, std::vector<double>(N + 1)), T(N + 1, std::vector<double>(N + 1));
    for (size_t i = 1; i <= N; ++i)
    {
        for (size_t j = 1; j <= N; ++j)
        {
            A[i][j] = std::dynamic_pointer_cast<Number>(matrix[i - 1][j - 1])->getNumber();
        }
    }

    std::vector<double> U(N + 1);
    for (int IR = 1; IR <= N - 2; ++IR)
    {
        double S = 0;
        for (int I = 1; I <= N; ++I)
        {
            U[I] = 0;
            if (I > IR + 1) U[I] = A[I][IR];
            if (I > IR) S += A[I][IR] * A[I][IR];
        }
        double W = 1;
        if (A[IR + 1][IR] < 0) W = -1;
        double SSR = sqrt(S);
        double H = S + std::abs(A[IR + 1][IR]) * SSR;
        U[IR + 1] = A[IR + 1][IR] + SSR * W;
        double UAU = 0;
        for (int I = 1; I <= N; ++I)
        {
            for (int J = 1; J <= N; ++J)
            {
                UAU += U[I] * A[I][J] * U[J];
                if ((I <= IR) && (J <= IR))
                {
                    T[I][J] = A[I][J];
                    continue;
                }
                if ((J == IR) && (I >= IR + 2))
                {
                    T[I][J] = 0;
                    continue;
                }
                double B23 = 0;
                for (int K = 1; K <= N; ++K)
                {
                    B23 -= (U[I] * A[K][J] + A[I][K] * U[J]) * U[K];
                }
                T[I][J] = A[I][J] + B23 / H;
            }
        }
        UAU /= H * H;
        for (int I = 1; I <= N; ++I)
        {
            for (int J = 1; J <= N; ++J)
            {
                A[I][J] = T[I][J] + UAU * U[I] * U[J];
                if (std::abs(A[I][J]) < 0.000001) A[I][J] = 0;
            }
        }
    }

    std::vector<std::vector<std::shared_ptr<Expression>>> newMatrix;
    for (size_t i = 1; i <= N; ++i)
    {
        std::vector<std::shared_ptr<Expression>> newVector;
        for (size_t j = 1; j <= N; ++j)
        {
            newVector.push_back(std::make_shared<Number>(A[i][j]));
        }
        newMatrix.push_back(newVector);
    }
    return newMatrix;
}

std::shared_ptr<Expression> TridiagonalMatrix::eval(Environment& env) const
{
    auto evMatrix = std::dynamic_pointer_cast<Matrix>(matrix->eval(env));
    auto mat = evMatrix->getMatrixExpression();
    return std::make_shared<Matrix>(tridiagonal(mat));
}

std::string TridiagonalMatrix::toString() const noexcept
{
    return "Matrix to make tridiagonal: \n"+ matrix->toString();
}

// Eigenvalues
RealEigenvalues::RealEigenvalues(std::shared_ptr<Matrix> _matrix) : Value(DataType::Matrix), matrix(_matrix) {}
void RealEigenvalues::determ(std::vector<double> G, std::vector<std::vector<double>> A, double X, double &SL, size_t L) const
{
    G[0] = 1;
    if (L == 1) return;
    G[1] = A[1][1] - X;
    if (L == 1) return;
    for (int K = 2; K <= L; K++)
    {
        G[K] = (A[K][K] - X) * G[K - 1] - A[K][K - 1] * A[K][K - 1] * G[K - 2];
    }
    SL = G[L];
}
void RealEigenvalues::bisec(std::vector<double> G, std::vector<std::vector<double>> A, double XL, double XH, double &XM, size_t L) const
{
    int KA = 0;
    double YL, YH, DX, XB, YM;
    determ(G, A, XL, YL, L);
    determ(G, A, XH, YH, L);
    while (true)
    {
        KA++;
        if (KA > 99) return;
        DX = XH - XL;
        if (DX < 0.0000001) return;
        if (DX > 1)
        {
            XM = (XL + XH) / 2;
            determ(G, A, XM, YM, L);
            if (YL * YM < 0)
            {
                XH = XM;
                YH = YM;
                continue;
            }
            XL = XM;
            YL = YM;
            continue;
        }
        XB = XM;
        XM = (XL * YH - XH * YL) / (YH - YL);
        determ(G, A, XM, YM, L);
        if (std::abs(XB - XM) < 0.000001) return;
        if (YL * YM < 0)
        {
            XH = XM;
            YH = YM;
            continue;
        }
        XL = XM;
        YL = YM;
    }
}
std::vector<std::shared_ptr<Expression>> RealEigenvalues::eigenvalues(std::vector<std::vector<std::shared_ptr<Expression>>> matrix) const
{
    size_t N = matrix.size();

    std::vector<std::vector<double>> A(N + 1, std::vector<double>(N + 1)), T(N + 1, std::vector<double>(N + 1)), EI(N + 1, std::vector<double>(N + 1));
    for (size_t i = 1; i <= N; ++i)
    {
        for (size_t j = 1; j <= N; ++j)
        {
            A[i][j] = std::dynamic_pointer_cast<Number>(matrix[i - 1][j - 1])->getNumber();
        }
    }

    std::vector<double> U(N + 1);
    for (int IR = 1; IR <= N - 2; ++IR)
    {
        double S = 0;
        for (int I = 1; I <= N; ++I)
        {
            U[I] = 0;
            if (I > IR + 1) U[I] = A[I][IR];
            if (I > IR) S += A[I][IR] * A[I][IR];
        }
        double W = 1;
        if (A[IR + 1][IR] < 0) W = -1;
        double SSR = sqrt(S);
        double H = S + std::abs(A[IR + 1][IR]) * SSR;
        U[IR + 1] = A[IR + 1][IR] + SSR * W;
        double UAU = 0;
        for (int I = 1; I <= N; ++I)
        {
            for (int J = 1; J <= N; ++J)
            {
                UAU += U[I] * A[I][J] * U[J];
                if ((I <= IR) && (J <= IR))
                {
                    T[I][J] = A[I][J];
                    continue;
                }
                if ((J == IR) && (I >= IR + 2))
                {
                    T[I][J] = 0;
                    continue;
                }
                double B23 = 0;
                for (int K = 1; K <= N; ++K)
                {
                    B23 -= (U[I] * A[K][J] + A[I][K] * U[J]) * U[K];
                }
                T[I][J] = A[I][J] + B23 / H;
            }
        }
        UAU /= H * H;
        for (int I = 1; I <= N; ++I)
        {
            for (int J = 1; J <= N; ++J)
            {
                A[I][J] = T[I][J] + UAU * U[I] * U[J];
                if (std::abs(A[I][J]) < 0.000001) A[I][J] = 0;
            }
        }
    }

    int KM = N;

    for (size_t L = 1; L <= KM; ++L)
    {
        if (L == 1)
        {
            EI[1][1] = A[1][1];
        }
        else
        {
            for (int J = 1; J <= L; ++J)
            {
                double XL = EI[L - 1][J - 1];
                double XH = EI[L - 1][J];
                double XM;
                bisec(U, A, XL, XH, XM, L);
                EI[L][J] = XM;
            }
        }
        if (L < KM)
        {
            EI[L][0] = -99;
            EI[L][L + 1] = 99;
        }
    }
    std::vector<std::shared_ptr<Expression>> newVector{};
    for (size_t i = 1; i <= N; ++i)
    {
        newVector.push_back(std::make_shared<Number>(EI[N][i]));
    }
    return newVector;
}
std::shared_ptr<Expression> RealEigenvalues::eval(Environment& env) const
{
    auto evMatrix = matrix->eval(env);
    auto values = eigenvalues(std::dynamic_pointer_cast<Matrix>(evMatrix)->getMatrixExpression());
    return std::make_shared<Vector>(values);
}
std::string RealEigenvalues::toString() const noexcept
{
    return "Matrix to calculate eigenvalues: \n"+ matrix->toString();
}
// Determinant
Determinant::Determinant(std::shared_ptr<Matrix> _matrix) : Value(DataType::Number), matrix(_matrix) {}
std::shared_ptr<Expression> Determinant::eval(Environment& env) const
{
    auto matrixPair = std::make_shared<MatrixLU>(matrix);
    auto upperMatrix = std::dynamic_pointer_cast<Matrix>(std::make_shared<PairSecond>(matrixPair)->eval(env));
    auto U = upperMatrix->getMatrixExpression();
    double det = 1;
    for (int I = 0; I < U.size(); ++I)
    {
        det *= std::dynamic_pointer_cast<Number>(U[I][I])->getNumber();
    }
    return std::make_shared<Number>(((det < 0) ? -det : det));
}
std::string Determinant::toString() const noexcept
{
    return "Matrix to calculate determinant: \n"+ matrix->toString();
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
std::string Equation::toString() const noexcept
{
    return leftExpression->toString() + " = " + rigthExpression->toString();
}

//Function
std::shared_ptr<Expression> Function::eval(Environment& env) const
{
    if (std::dynamic_pointer_cast<Value>(expression->eval(env)) != nullptr )
    {
        auto exp = expression->eval(env);
        return std::dynamic_pointer_cast<Number>(exp);
    }
    else
    {
        return expression;
    }
}

std::string Function::toString() const noexcept
{
    return expression->toString();
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
    return num;
}
std::string Integral::toString() const noexcept
{
    std::string str = "Interval: " + interval->toString() + " | Integral = ∫(" + function->toString() + ")d" + variable->toString();
    return str;
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
std::string Interpolate::toString() const noexcept
{
    std::string result = "[  ";
    for (auto exp : vectorExpression)
    {
        std::string element = exp->toString();
        result += element +"  ";
    }
    result += "]\nInterpolate Number: " +numInter->toString();

    return result;
}

ODEFirstOrderInitialValues::ODEFirstOrderInitialValues(std::shared_ptr<Function> _funct, std::shared_ptr<Pair> _initialValue, std::shared_ptr<Number> _tFinal, std::shared_ptr<Variable> _variable) : funct(_funct), initialValue(_initialValue), tFinal(_tFinal), variable(_variable) {}
std::shared_ptr<Pair> ODEFirstOrderInitialValues::rungekuttaMethod(double _t, double _x, double f, double h, std::shared_ptr<Expression> function, Environment& env, std::shared_ptr<Variable> variable) const
{
    double t = _t, x = _x, tn = f;
    while(t < tn)
    {
        env.push_front(std::make_pair(variable->getVariable(), std::make_shared<Number>(x)));
        auto num1 = std::dynamic_pointer_cast<Number>(function->eval(env));

        if (num1 == nullptr)
        {
            return nullptr;
        }
        double k1 = h * num1->getNumber();

        env.push_front(std::make_pair(variable->getVariable(), std::make_shared<Number>(x + 0.5 * k1)));
        auto num2 = std::dynamic_pointer_cast<Number>(function->eval(env));

        if(num2 == nullptr)
        {
            return nullptr;
        }

        double k2 = h * num2->getNumber();

        env.push_front(std::make_pair(variable->getVariable(), std::make_shared<Number>(x + 0.5 * k2)));
        auto num3 = std::dynamic_pointer_cast<Number>(function->eval(env));

        if (num3 == nullptr)
        {
            return nullptr;
        }
        double k3 = h * num3->getNumber();

        env.push_front(std::make_pair(variable->getVariable(), std::make_shared<Number>(x + k3)));
        auto num4 = std::dynamic_pointer_cast<Number>(function->eval(env));

        if (num4 == nullptr)
        {
            return nullptr;
        }
        double k4 = h * num4->getNumber();

        x = x + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);
        t = t + h;
    }
    return std::make_shared<Pair>(std::make_shared<Number>(t), std::make_shared<Number>(x));
}
std::shared_ptr<Expression> ODEFirstOrderInitialValues::eval(Environment& env) const
{
    auto initialV = initialValue->eval(env);
    auto to = std::dynamic_pointer_cast<Number>(PairFirst{initialValue}.eval(env));
    auto xo = std::dynamic_pointer_cast<Number>(PairSecond{initialValue}.eval(env));
    auto tEval = std::dynamic_pointer_cast<Number>(tFinal->eval(env));
    if (to->getDataType() != DataType::Number || xo->getDataType() != DataType::Number || tEval->getDataType() != DataType::Number)
    {
        return nullptr;
    }
    double t = to->getNumber();
    double x = xo->getNumber();
    double f = tEval->getNumber();
    double step = 0.1;
    if (f < t)
    {
        std::shared_ptr<Expression> imp = std::make_shared<Impossible>();
        return imp;
    }
    std::shared_ptr<Pair> num = rungekuttaMethod(t, x, f, step, funct, env, variable);

    return num;
}
std::string ODEFirstOrderInitialValues::toString() const noexcept
{
    return variable->toString() + "' = " + funct->toString() +"\n[t,"+ variable->toString()+"] = " + initialValue->toString() + "\nT_Final: " + tFinal->toString();
}

FindRootBisection::FindRootBisection(std::shared_ptr<Pair> _interval, std::shared_ptr<Function> _function, std::shared_ptr<Variable> _variable, std::shared_ptr<Number> _iterationLimit) : interval(_interval), function(_function), variable(_variable), iterationLimit(_iterationLimit) {}
std::shared_ptr<Number> FindRootBisection::bisectionMethod(std::shared_ptr<Number> left, std::shared_ptr<Number> right, std::shared_ptr<Function> evFunction, Environment& env) const
{
    double a = left->getNumber(), c = right->getNumber(), ep = 0.0001;
    size_t il = iterationLimit->getNumber();

    char var = variable->getVariable();

    env.push_front(std::make_pair(var, left));
    double ya = std::dynamic_pointer_cast<Number>(evFunction->eval(env))->getNumber();
    env.push_front(std::make_pair(var, right));
    double yc = std::dynamic_pointer_cast<Number>(evFunction->eval(env))->getNumber();
    int it = 0;

    while (true)
    {
        double b = (a + c) / 2;
        env.push_front(std::make_pair(var, std::make_shared<Number>(b)));
        double yb = std::dynamic_pointer_cast<Number>(evFunction->eval(env))->getNumber();

        if (++it > il)
        {
            break;
        }
        if (std::abs(b - a) < ep)
        {
            break;
        }
        if (ya * yb <= 0)
        {
            c = b;
            yc = yb;
        }
        else
        {
            a = b;
            ya = yb;
        }
    }
    return std::make_shared<Number>((a + c) / 2);
}
std::shared_ptr<Expression> FindRootBisection::eval(Environment& env) const
{
    auto evInterval = std::dynamic_pointer_cast<Pair>(interval->eval(env));
    if (evInterval == nullptr)
    {
        return nullptr;
    }
    auto left = std::dynamic_pointer_cast<Number>(PairFirst{evInterval}.eval(env));
    auto right = std::dynamic_pointer_cast<Number>(PairSecond{evInterval}.eval(env));
    if (left->getDataType() != DataType::Number || right->getDataType() != DataType::Number)
    {
        return std::make_shared<Impossible>();
    }
    if (left->getNumber() > right->getNumber())
    {
        return std::make_shared<Impossible>();
    }

    return bisectionMethod(left, right, function, env);
}
std::string FindRootBisection::toString() const noexcept
{
    return "Interval: " + interval->toString() + " | Function: " + function->toString();
}

