#include <cmath>
#include <memory>
#include <vector>

enum class DataType
{
    Pair,
    Vector,
    Matrix,
    Number,
    Letter
};

class Expression
{
public:
    virtual std::shared_ptr<Expression> eval() const = 0;
    virtual ~Expression() {}
};

class Value : public Expression
{
protected:
    DataType dataType;
public:
    Value(DataType type) : dataType{type} {}
    DataType getDataType() const
    {
        return dataType;
    }
};

class UnaryExpression : public Expression
{
protected:
    std::shared_ptr<Expression> expression;

public:
    UnaryExpression(std::shared_ptr<Expression> exp) : expression{exp} {}
};

class BinaryExpression : public Expression
{

protected:
    std::shared_ptr<Expression> leftExpression;
    std::shared_ptr<Expression> rigthExpression;

public:
    BinaryExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> rigth) : leftExpression{left}, rigthExpression{rigth} {};
};

class Letter : public Value
{
protected:
    char letter;
public:
    Letter(char lett) : Value(DataType::Letter), letter{lett} {}

    std::shared_ptr<Expression> eval() const override
    {
        return std::make_shared<Letter>(letter);
    }

    double getLetter() const
    {
        return letter;
    }
};

class Number : public Value
{
protected:
    double number;

public:
    Number(double num) : Value(DataType::Number), number{num} {}

    std::shared_ptr<Expression> eval() const override
    {
        return std::make_shared<Number>(number);
    }

    double getNumber() const
    {
        return number;
    }
};

// known Expressions
class Addition : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    std::shared_ptr<Expression> eval() const override
    {
        auto exp1 = leftExpression->eval();
        auto exp2 = rigthExpression->eval();
        auto element1 = std::dynamic_pointer_cast<Value>(exp1);
        auto element2 = std::dynamic_pointer_cast<Value>(exp2);

        if (element1->getDataType() == DataType::Letter || element2->getDataType() == DataType::Letter)
        {
            return std::make_shared<Addition>(exp1, exp2);
        }

        auto num1 = std::dynamic_pointer_cast<Number>(exp1);
        auto num2 = std::dynamic_pointer_cast<Number>(exp2);
        if (num1 == nullptr || num2 == nullptr)
        {
            return nullptr;
        }
        double result = num1->getNumber() + num2->getNumber();
        return std::make_shared<Number>(result);
    }
};

class Subtraction : public BinaryExpression {

public:
    using BinaryExpression::BinaryExpression;

    std::shared_ptr<Expression> eval() const override
    {
        auto exp1 = leftExpression->eval();
        auto exp2 = rigthExpression->eval();
        auto element1 = std::dynamic_pointer_cast<Value>(exp1);
        auto element2 = std::dynamic_pointer_cast<Value>(exp2);
        if (element1->getDataType() == DataType::Letter || element2->getDataType() == DataType::Letter)
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
};

class Multiplication : public BinaryExpression {

public:
    using BinaryExpression::BinaryExpression;

    std::shared_ptr<Expression> eval() const override
    {
        auto exp1 = leftExpression->eval();
        auto exp2 = rigthExpression->eval();
        auto element1 = std::dynamic_pointer_cast<Value>(exp1);
        auto element2 = std::dynamic_pointer_cast<Value>(exp2);
        if (element1->getDataType() == DataType::Letter || element2->getDataType() == DataType::Letter)
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
};

class Division : public BinaryExpression {

public:
    using BinaryExpression::BinaryExpression;

    std::shared_ptr<Expression> eval() const override
    {
        auto exp1 = leftExpression->eval();
        auto exp2 = rigthExpression->eval();
        auto element1 = std::dynamic_pointer_cast<Value>(exp1);
        auto element2 = std::dynamic_pointer_cast<Value>(exp2);
        if (element1->getDataType() == DataType::Letter || element2->getDataType() == DataType::Letter)
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
};

class Power : public BinaryExpression {

public:
    using BinaryExpression::BinaryExpression;

    std::shared_ptr<Expression> eval() const override
    {
        auto exp1 = leftExpression->eval();
        auto exp2 = rigthExpression->eval();
        auto element1 = std::dynamic_pointer_cast<Value>(exp1);
        auto element2 = std::dynamic_pointer_cast<Value>(exp2);
        if (element1->getDataType() == DataType::Letter || element2->getDataType() == DataType::Letter)
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
};

class NaturalLogarithm : public UnaryExpression {

public:
    using UnaryExpression::UnaryExpression;

    std::shared_ptr<Expression> eval() const override
    {
        auto exp1 = expression->eval();
        auto element1 = std::dynamic_pointer_cast<Value>(exp1);
        if(element1->getDataType() == DataType::Letter)
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
};

class Logarithm : public BinaryExpression {

public:
    using BinaryExpression::BinaryExpression;

    std::shared_ptr<Expression> eval() const override
    {
        auto exp1 = leftExpression->eval();
        auto exp2 = rigthExpression->eval();
        auto element1 = std::dynamic_pointer_cast<Value>(exp1);
        auto element2 = std::dynamic_pointer_cast<Value>(exp2);
        if (element1->getDataType() == DataType::Letter || element2->getDataType() == DataType::Letter)
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
};

class Sine : public UnaryExpression {

public:
    using UnaryExpression::UnaryExpression;

    std::shared_ptr<Expression> eval() const override
    {
       auto exp1 = expression->eval();
        auto element1 = std::dynamic_pointer_cast<Value>(exp1);
        if(element1->getDataType() == DataType::Letter)
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
};

class Cosine : public UnaryExpression {

public:
    using UnaryExpression::UnaryExpression;

    std::shared_ptr<Expression> eval() const override
    {
        auto exp1 = expression->eval();
        auto element1 = std::dynamic_pointer_cast<Value>(exp1);
        if(element1->getDataType() == DataType::Letter)
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
};

class Tangent : public UnaryExpression {

public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval() const override
    {
        auto exp1 = expression->eval();
        auto element1 = std::dynamic_pointer_cast<Value>(exp1);
        if(element1->getDataType() == DataType::Letter)
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
};

class Cotangent : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval() const override
    {
        auto exp1 = expression->eval();
        auto element1 = std::dynamic_pointer_cast<Value>(exp1);
        if(element1->getDataType() == DataType::Letter)
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
};

// Expressions for our language
class Pair : public Value
{
private:
    std::shared_ptr<Expression> first;
    std::shared_ptr<Expression> second;
public:
    Pair(std::shared_ptr<Expression> first, std::shared_ptr<Expression> second) : Value(DataType::Pair), first{first}, second{second} {}
    std::shared_ptr<Expression> eval() const override
    {
        auto exp1 = first->eval();
        auto exp2 = second->eval();
        return std::make_shared<Pair>(exp1, exp2);
    }
    std::shared_ptr<Expression> getFirst()
    {
        return first;
    }
    std::shared_ptr<Expression> getSecond()
    {
        return second;
    }
};

class PairFirst : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval() const override
    {
        auto exp = expression->eval();
        auto pair = std::dynamic_pointer_cast<Pair>(exp);
        if (pair == nullptr)
        {
            return nullptr;
        }
        return pair->getFirst()->eval();
    }
};

class PairSecond : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval() const override
    {
        auto exp = expression->eval();
        auto pair = std::dynamic_pointer_cast<Pair>(exp);
        if (pair == nullptr)
        {
            return nullptr;
        }
        return pair->getSecond()->eval();
    }
};

class Vector : public Value
{
private:
    std::vector<std::shared_ptr<Expression>> vectorExpression;
public:
    Vector(std::vector<std::shared_ptr<Expression>> _vectorExpression) : Value(DataType::Vector), vectorExpression(_vectorExpression) {}
    std::shared_ptr<Expression> eval() const override
    {
        std::vector<std::shared_ptr<Expression>> newVector;
        for (auto exp : vectorExpression)
        {
            auto element = exp->eval();
            newVector.push_back(element);
        }
        return std::make_shared<Vector>(newVector);
    }
};
/*
class Matrix : public Value
{
private:
    std::vector<Vector> matrixExpression;
public:
    Matrix(std::vector<Vector> _matrixExpression) : Value(DataType::Matrix), matrixExpression(_matrixExpression) {}
};*/
