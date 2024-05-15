#include <cmath>
#include <memory>
#include <vector>
#include <forward_list>
#include <functional>

enum class DataType
{
    Pair,
    Vector,
    Matrix,
    Number,
    Variable
    //Default
};

class Expression
{
public:
    virtual std::shared_ptr<Expression> eval(std::forward_list<std::pair<char, std::shared_ptr<Expression>>>&) const = 0;
    virtual ~Expression() {}
};

using Environment = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>;

class Value : public Expression
{
protected:
    DataType dataType;
public:
    Value(DataType _dataType);
    //Value();
    DataType getDataType() const;
};

class UnaryExpression : public Expression
{
protected:
    std::shared_ptr<Expression> expression;
public:
    UnaryExpression(std::shared_ptr<Expression> exp);
};

class BinaryExpression : public Expression
{
protected:
    std::shared_ptr<Expression> leftExpression;
    std::shared_ptr<Expression> rigthExpression;
public:
    BinaryExpression(std::shared_ptr<Expression> _leftExpression, std::shared_ptr<Expression> _rigthExpression);
};

class Number : public Value
{
protected:
    double number;
public:
    Number(double _number);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    double getNumber() const;
};

class Variable : public Value
{
protected:
    char variable;
public:
    Variable(char _variable);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    char getVariable() const;
};

class Display/* : Expression*/
{
/*private:
    std::shared_ptr<Expression> exp;*/
public:
    Display(std::shared_ptr<Expression> _exp);
    //std::shared_ptr<Expression> eval(Environment& env) const override;
};

// known Expressions
class Addition : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
};

class Subtraction : public BinaryExpression {

public:
    using BinaryExpression::BinaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
};

class Multiplication : public BinaryExpression {

public:
    using BinaryExpression::BinaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
};

class Division : public BinaryExpression {

public:
    using BinaryExpression::BinaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const;
};

class Power : public BinaryExpression {

public:
    using BinaryExpression::BinaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
};

class NaturalLogarithm : public UnaryExpression {

public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
};

class Logarithm : public BinaryExpression {

public:
    using BinaryExpression::BinaryExpression;

    std::shared_ptr<Expression> eval(Environment& env) const override;
};

class Sine : public UnaryExpression {

public:
    using UnaryExpression::UnaryExpression;

    std::shared_ptr<Expression> eval(Environment& env) const override;
};

class Cosine : public UnaryExpression {

public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
};

class Tangent : public UnaryExpression {

public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
};

class Cotangent : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
};

// Expressions for our language
class Pair : public Value
{
private:
    std::shared_ptr<Expression> first;
    std::shared_ptr<Expression> second;
public:
    Pair(std::shared_ptr<Expression> _first, std::shared_ptr<Expression> _second);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::shared_ptr<Expression> getFirst();
    std::shared_ptr<Expression> getSecond();
};

class PairFirst : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
};

class PairSecond : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
};

class Vector : public Value
{
protected:
    std::vector<std::shared_ptr<Expression>> vectorExpression;
public:
    Vector(std::vector<std::shared_ptr<Expression>> _vectorExpression);
    std::shared_ptr<Expression> eval(Environment& env) const override;
};

class Matrix : public Value
{
protected:
    std::vector<std::vector<std::shared_ptr<Expression>>> matrixExpression;
public:
    Matrix(std::vector<std::vector<std::shared_ptr<Expression>>> _matrixExpression);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::vector<std::vector<std::shared_ptr<Expression>>> getMatrixExpression() const;
    //void displayMatrix() const;
};

class Equation : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
};
class Function : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;

    std::shared_ptr<Expression> eval(Environment& env) const override;
};

class Integral : public Expression // Resolution by Simpson Method
{
private:
    std::shared_ptr<Pair> interval;
    std::shared_ptr<Function> function;
    std::shared_ptr<Variable> variable;
    std::shared_ptr<Number> simpsonMethod(double a, double b, int n, std::shared_ptr<Expression> function, Environment& env, std::shared_ptr<Variable> variable) const;
public:
    Integral(std::shared_ptr<Pair> _interval, std::shared_ptr<Function> _function, std::shared_ptr<Variable> _variable);
    std::shared_ptr<Expression> eval(Environment& env) const override;
};
class ODEInitialValues : public Expression
{
private:
    std::shared_ptr<Function> function;
    std::shared_ptr<Pair> values;
public:
    ODEInitialValues(std::shared_ptr<Function> _function, std::shared_ptr<Pair> _values);
    std::shared_ptr<Expression> eval(Environment& env) const override;
};

class Interpolate : public Vector // Resolution by Lagrange
{
private:
    std::shared_ptr<Number> numInter;
public:
    Interpolate(std::vector<std::shared_ptr<Expression>> _vectorExpression, std::shared_ptr<Number> _numInter);
    std::shared_ptr<Expression> eval(Environment& env) const override;
};

/*
class SystemOfEquations : public Expression
{
public:
    std::vector<std::shared_ptr<Equation>> system;
private:
    SystemOfEquations(std::vector<std::shared_ptr<Equation>> system) : system(system) {}

    std::shared_ptr<Expression> eval(std::forward_list<std::shared_ptr<Expression>>) const override
    {
        std::vector<std::shared_ptr<Equation>> newEqSys;
        for (auto exp : system)
        {
            auto element = exp->eval(std::forward_list<std::shared_ptr<Expression>>);
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