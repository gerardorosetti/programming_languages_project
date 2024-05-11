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
    double value;
    bool hasValue;
public:
    Letter(char _letter) : Value(DataType::Letter), letter{_letter}, hasValue{false} {}

    std::shared_ptr<Expression> eval() const override
    {
        if (hasValue)
        {
            return std::make_shared<Number>(value);
        }
        return std::make_shared<Letter>(letter);
    }

    void setValue(double val)
    {
        hasValue = true;
        value = val;
    }
    void removeValue()
    {
        hasValue = false;
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
    Number(double _number) : Value(DataType::Number), number{_number} {}

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
    Pair(std::shared_ptr<Expression> _first, std::shared_ptr<Expression> _second) : Value(DataType::Pair), first{_first}, second{_second} {}
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
            if (element = nullptr)
            {
                return nullptr;
            }
            newVector.push_back(element);
        }
        return std::make_shared<Vector>(newVector);
    }
};

class Matrix : public Value
{
private:
    std::vector<std::vector<std::shared_ptr<Expression>>> matrixExpression;
public:
    Matrix(std::vector<std::vector<std::shared_ptr<Expression>>> _matrixExpression) : Value(DataType::Matrix), matrixExpression(_matrixExpression) {}
    std::shared_ptr<Expression> eval() const override
    {
        std::vector<std::vector<std::shared_ptr<Expression>>> newMatrix;
        for (std::vector<std::shared_ptr<Expression>> vec : matrixExpression)
        {
            std::vector<std::shared_ptr<Expression>> newVector;
            for (std::shared_ptr<Expression> exp : vec)
            {
                auto element = exp->eval();
                if (element = nullptr)
                {
                    return nullptr;
                }
                newVector.push_back(element);
            }
            newMatrix.push_back(newVector);
        }
        return std::make_shared<Matrix>(newMatrix);
    }
};

class Equation : public BinaryExpression
{

public:
    using BinaryExpression::BinaryExpression;
    std::shared_ptr<Expression> eval() const override
    {
        auto exp1 = leftExpression->eval();
        auto exp2 = rigthExpression->eval();
        /*auto element1 = std::dynamic_pointer_cast<Value>(exp1);
        auto element2 = std::dynamic_pointer_cast<Value>(exp2);
        if (element1->getDataType() == DataType::Letter || element2->getDataType() == DataType::Letter)
        {
            return std::make_shared<Addition>(exp1, exp2);
        }
        auto num1 = std::dynamic_pointer_cast<Number>(exp1);
        auto num2 = std::dynamic_pointer_cast<Number>(exp2);
        */if (exp1 == nullptr || exp2 == nullptr)
        {
            return nullptr;
        }
        return std::make_shared<Equation>(exp1, exp2);
        //return std::make_shared<Expression>(Pair(num1, num2));
    }
};
class Function : public UnaryExpression
{

public:
    using UnaryExpression::UnaryExpression;

    std::shared_ptr<Expression> eval() const override
    {
        auto exp = expression->eval();
        if (exp == nullptr)
        {
            return nullptr;
        }
        return std::make_shared<Function>(exp);
    }
};

class Integral : public Expression
{
private:
    std::shared_ptr<Pair> interval;
    std::shared_ptr<Function> function;
public:
    Integral(std::shared_ptr<Pair> _interval, std::shared_ptr<Function> _function) : interval(_interval) , function(_function) {}

    std::shared_ptr<Expression> eval() const override
    {
        auto inter = interval->eval();

        auto to = std::dynamic_pointer_cast<Number>(PairFirst{inter}.eval());
        auto tf = std::dynamic_pointer_cast<Number>(PairSecond{inter}.eval());
        if (to->getDataType() != DataType::Number || tf->getDataType() != DataType::Number)
        {
            return nullptr;
        }

        double a = to->getNumber();
        double b = tf->getNumber();
        auto f = function->eval();
        double result = 0.0;

        // Perform integration here
        // For example, you could use the trapezoidal rule
        double h = (b - a) / 100.0;
        for (double x = a; x <= b; x += h)
        {
            auto fx = std::dynamic_pointer_cast<Number>(f->eval());
            if (fx == nullptr)
            {
                return nullptr;
            }
            result += h * fx->getNumber();
        }

        return std::make_shared<Number>(result);
    }
};
class ODEInitialValues : public Expression
{
private:
    std::shared_ptr<Function> function;
    std::shared_ptr<Pair> values;
public:
    ODEInitialValues(std::shared_ptr<Function> _function, std::shared_ptr<Pair> _values) : function(_function), values(_values) {}
    std::shared_ptr<Expression> eval() const override
    {
        auto inter = values->eval();
        auto to = std::dynamic_pointer_cast<Number>(std::dynamic_pointer_cast<PairFirst>(inter)->eval());
        auto tf = std::dynamic_pointer_cast<Number>(std::dynamic_pointer_cast<PairSecond>(inter)->eval());
        if (to->getDataType() != DataType::Number || tf->getDataType() != DataType::Number)
        {
            return nullptr;
        }
        return nullptr;
    }
};
/*
class SystemOfEquations : public Expression
{
public:
    std::vector<std::shared_ptr<Equation>> system;
private:
    SystemOfEquations(std::vector<std::shared_ptr<Equation>> system) : system(system) {}

    std::shared_ptr<Expression> eval() const override
    {
        std::vector<std::shared_ptr<Equation>> newEqSys;
        for (auto exp : system)
        {
            auto element = exp->eval();
            if (element = nullptr)
            {
                return nullptr;
            }
            newEqSys.push_back(std::dynamic_pointer_cast<Equation>(element));
        }
        return std::make_shared<Vector>(newEqSys);
        return nullptr;
    }
};*/