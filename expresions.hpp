#include <cmath>
#include <memory>
#include <vector>

enum DataType
{
    Operation,
    
};

class Expresion
{
public:
    virtual std::shared_ptr<Value> eval() const = 0;
    virtual ~Expresion() {}
};

class Value : public Expresion
{
protected:
    DataType dataType;
public:
    Value(DataType type) : dataType{type} {}
};

class UnaryExpresion : public Expresion
{
protected:
    std::shared_ptr<Expresion> expresion;

public:
    UnaryExpresion(std::shared_ptr<Expresion> exp) : expresion{exp} {}
};

class BinaryExpresion : public Expresion
{

protected:
    std::shared_ptr<Expresion> leftExpresion;
    std::shared_ptr<Expresion> rigthExpresion;

public:
    BinaryExpresion(std::shared_ptr<Expresion> left, std::shared_ptr<Expresion> rigth) : leftExpresion{left}, rigthExpresion{rigth} {};
};

class Number : public Value
{
protected:
    double number;

public:
    Number(double num) : number{num} {}

    std::shared_ptr<Expresion> eval() const override
    {
        return std::make_shared<Number>(number);
    }

    double getNumber() const
    {
        return number;
    }
};


// known Expresions
class Addition : public BinaryExpresion {
public:
    using BinaryExpresion::BinaryExpresion;

    std::shared_ptr<Expresion> eval() const override
    {
        auto exp1 = leftExpresion->eval();
        auto exp2 = rigthExpresion->eval();
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

class Subtraction : public BinaryExpresion {

public:
    using BinaryExpresion::BinaryExpresion;

    std::shared_ptr<Expresion> eval() const override
    {
        auto exp1 = leftExpresion->eval();
        auto exp2 = rigthExpresion->eval();
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

class Multiplication : public BinaryExpresion {

public:
    using BinaryExpresion::BinaryExpresion;

    std::shared_ptr<Expresion> eval() const override
    {
        auto exp1 = leftExpresion->eval();
        auto exp2 = rigthExpresion->eval();
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

class Division : public BinaryExpresion {

public:
    using BinaryExpresion::BinaryExpresion;

    std::shared_ptr<Expresion> eval() const override
    {
        auto exp1 = leftExpresion->eval();
        auto exp2 = rigthExpresion->eval();
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

class Power : public BinaryExpresion {

public:
    using BinaryExpresion::BinaryExpresion;

    std::shared_ptr<Expresion> eval() const override
    {
        auto exp1 = leftExpresion->eval();
        auto exp2 = rigthExpresion->eval();
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

class NaturalLogarithm : public UnaryExpresion {

public:
    using UnaryExpresion::UnaryExpresion;

    std::shared_ptr<Expresion> eval() const override
    {
        auto exp1 = expresion->eval();
        auto num1 = std::dynamic_pointer_cast<Number>(exp1);
        if (num1 == nullptr)
        {
            return nullptr;
        }
        double result = std::log(num1->getNumber());
        return std::make_shared<Number>(result);
    }
};

class Logarithm : public BinaryExpresion {

public:
    using BinaryExpresion::BinaryExpresion;

    std::shared_ptr<Expresion> eval() const override
    {
        auto exp1 = leftExpresion->eval();
        auto exp2 = rigthExpresion->eval();
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

class Sine : public UnaryExpresion {

public:
    using UnaryExpresion::UnaryExpresion;

    std::shared_ptr<Expresion> eval() const override
    {
        auto exp1 = expresion->eval();
        auto num1 = std::dynamic_pointer_cast<Number>(exp1);
        if (num1 == nullptr)
        {
            return nullptr;
        }
        double result = std::sin(num1->getNumber());
        return std::make_shared<Number>(result);
    }
};

class Cosine : public UnaryExpresion {

public:
    using UnaryExpresion::UnaryExpresion;

    std::shared_ptr<Expresion> eval() const override
    {
        auto exp1 = expresion->eval();
        auto num1 = std::dynamic_pointer_cast<Number>(exp1);
        if (num1 == nullptr)
        {
            return nullptr;
        }
        double result = std::sin(num1->getNumber());
        return std::make_shared<Number>(result);
    }
};

class Tangent : public UnaryExpresion {

public:
    using UnaryExpresion::UnaryExpresion;
    std::shared_ptr<Expresion> eval() const override
    {
        auto exp1 = expresion->eval();
        auto num1 = std::dynamic_pointer_cast<Number>(exp1);
        if (num1 == nullptr)
        {
            return nullptr;
        }
        double result = std::tan(num1->getNumber());
        return std::make_shared<Number>(result);
    }
};

class Cotangent : public UnaryExpresion {
public:
    using UnaryExpresion::UnaryExpresion;
    std::shared_ptr<Expresion> eval() const override
    {
        auto exp1 = expresion->eval();
        auto num1 = std::dynamic_pointer_cast<Number>(exp1);
        if (num1 == nullptr)
        {
            return nullptr;
        }
        double result = 1 / std::tan(num1->getNumber());
        return std::make_shared<Number>(result);
    }
};

// Expresions for our language
class Pair : public BinaryExpresion
{
public:
    using BinaryExpresion::BinaryExpresion;
    std::shared_ptr<Expresion> eval() const override
    {
        auto exp1 = leftExpresion->eval();
        auto exp2 = rigthExpresion->eval();
        return std::make_shared<Pair>(exp1, exp2);
    }
    std::shared_ptr<Expresion> getFirst()
    {
        return leftExpresion;
    }
    std::shared_ptr<Expresion> getSecond()
    {
        return rigthExpresion;
    }
};

class PairFirst : public UnaryExpresion
{
public:
    using UnaryExpresion::UnaryExpresion;
    std::shared_ptr<Expresion> eval() const override
    {
        auto exp = expresion->eval();
        auto pair = std::dynamic_pointer_cast<Pair>(exp);
        if (pair == nullptr)
        {
            return nullptr;
        }
        return pair->getFirst()->eval();
    }
};

class PairSecond : public UnaryExpresion
{
public:
    using UnaryExpresion::UnaryExpresion;
    std::shared_ptr<Expresion> eval() const override
    {
        auto exp = expresion->eval();
        auto pair = std::dynamic_pointer_cast<Pair>(exp);
        if (pair == nullptr)
        {
            return nullptr;
        }
        return pair->getSecond()->eval();
    }
};

class Vector : public Expresion
{
private:
    std::vector<std::shared_ptr<Expresion>> vectorExpresion;
public:
    Vector(std::vector<std::shared_ptr<Expresion>> _vectorExpresion) : vectorExpresion(_vectorExpresion) {}
    std::shared_ptr<Expresion> eval() const override
    {
        std::vector<std::shared_ptr<Expresion>> newVector;
        for (auto exp : vectorExpresion)
        {
            auto element = exp->eval();
            newVector.push_back(element);
        }
        return std::make_shared<Expresion>(newVector);
    }
};

class Matrix : public Expresion
{
private:
    std::vector<Vector> matrixExpresion;
public:
    Matrix(std::vector<Vector> _matrixExpresion) : matrixExpresion(_matrixExpresion) {}
};

class Equation : public BinaryExpresion
{
public:
    using BinaryExpresion::BinaryExpresion;
    std::shared_ptr<Expresion> eval() const override
    {

        return std::make_shared<Expresion>(newVector);
    }
}
/*
class Sin : public BinaryExpresion {
private:
    std::shared_ptr<Expresion> innerExpresion;

public:
    Sin(std::shared_ptr<Expresion> exp) : innerExpresion(exp) {}

    double eval() const override {
        return std::sin(innerExpresion->eval());
    }
};

class Cos : public Expresion {
private:
    std::shared_ptr<Expresion> innerExpresion;

public:
    Cos(std::shared_ptr<Expresion> exp) : innerExpresion(exp) {}

    double eval() const override {
        return std::cos(innerExpresion->eval());
    }
};


class Interval: public Expresion {
private:
    std::shared_ptr<Expresion> inferiorExpresion;
    std::shared_ptr<Expresion> superiorExpresion;

public:
    Interval(std::shared_ptr<Expresion> inf, std::shared_ptr<Expresion> sup) : inferiorExpresion(inf), superiorExpresion(sup) {}

    double eval() const override {
        return std::cos(innerExpresion->eval());
    }
};

class Integral: public Expresion {
private:
    std::shared_ptr<Expresion> innerExpresion;

public:
    Cos(std::shared_ptr<Expresion> exp) : innerExpresion(exp) {}

    double eval() const override {
        return std::cos(innerExpresion->eval());
    }
};*/