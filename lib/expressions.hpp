#pragma once

#include "utils.hpp"
class Expression
{
public:
    virtual std::shared_ptr<Expression> eval(Environment&) const = 0;
    virtual std::string toString() const noexcept = 0;
    virtual ~Expression() {}
};

class Value : public Expression
{
protected:
    DataType dataType;
public:
    Value(DataType _dataType);
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

class Impossible : public Value
{
protected:
    std::string value = "IMPOSSIBLE";
public:
    Impossible();
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept;
};

class Number : public Value
{
protected:
    double number;
public:
    Number(double _number);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
    double getNumber() const;
};

class Variable : public Value
{
protected:
    char variable;
public:
    Variable(char _variable);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
    char getVariable() const;
};

class Addition : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Subtraction : public BinaryExpression {

public:
    using BinaryExpression::BinaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Multiplication : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Division : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const;
    std::string toString() const noexcept override;
};

class Power : public BinaryExpression {

public:
    using BinaryExpression::BinaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class NaturalLogarithm : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Logarithm : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Sine : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Cosine : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Tangent : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Cotangent : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Pair : public Value
{
private:
    std::shared_ptr<Expression> first;
    std::shared_ptr<Expression> second;
public:
    Pair(std::shared_ptr<Expression> _first, std::shared_ptr<Expression> _second);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
    std::shared_ptr<Expression> getFirst();
    std::shared_ptr<Expression> getSecond();
};

class PairFirst : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class PairSecond : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Vector : public Value
{
protected:
    std::vector<std::shared_ptr<Expression>> vectorExpression;
public:
    Vector(std::vector<std::shared_ptr<Expression>> _vectorExpression);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
    std::vector<std::shared_ptr<Expression>> getVectorExpression() const;
};

class Matrix : public Value
{
protected:
    std::vector<std::vector<std::shared_ptr<Expression>>> matrixExpression;
public:
    Matrix(std::vector<std::vector<std::shared_ptr<Expression>>> _matrixExpression);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
    std::vector<std::vector<std::shared_ptr<Expression>>> getMatrixExpression() const;
};

class InverseMatrix : public Value
{
private:
    std::shared_ptr<Matrix> matrix;
    std::vector<std::vector<std::shared_ptr<Expression>>> gauss(std::vector<std::vector<std::shared_ptr<Expression>>> matrix) const;
public:
    InverseMatrix(std::shared_ptr<Matrix> _matrix);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class MatrixLU : public Value
{
private:
    std::shared_ptr<Matrix> matrix;
    std::pair<std::vector<std::vector<std::shared_ptr<Expression>>>, std::vector<std::vector<std::shared_ptr<Expression>>>> lowerUpperDecomposition(std::vector<std::vector<std::shared_ptr<Expression>>> matrix) const;
public:
    MatrixLU(std::shared_ptr<Matrix> _matrix);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class TridiagonalMatrix : public Value
{
private:
    std::shared_ptr<Matrix> matrix;
    std::vector<std::vector<std::shared_ptr<Expression>>> tridiagonal(std::vector<std::vector<std::shared_ptr<Expression>>> matrix) const;
public:
    TridiagonalMatrix(std::shared_ptr<Matrix> _matrix);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};
class RealEigenvalues : public Value
{
private:
    std::shared_ptr<Matrix> matrix;
    void determ(std::vector<double> G, std::vector<std::vector<double>> A, double X, double &SL, size_t L) const;
    void bisec(std::vector<double> G, std::vector<std::vector<double>> A, double XL, double XH, double &XM, size_t L) const;
    std::vector<std::shared_ptr<Expression>> eigenvalues(std::vector<std::vector<std::shared_ptr<Expression>>> matrix) const;
public:
    RealEigenvalues(std::shared_ptr<Matrix> _matrix);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};
class Determinant : public Value
{
private:
    std::shared_ptr<Matrix> matrix;
public:
    Determinant(std::shared_ptr<Matrix> _matrix);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class Equation : public BinaryExpression
{
public:
    using BinaryExpression::BinaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};
class Function : public UnaryExpression
{
public:
    using UnaryExpression::UnaryExpression;
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
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
    std::string toString() const noexcept override;
};

class Interpolate : public Vector // Resolution by Lagrange
{
private:
    std::shared_ptr<Number> numInter;
public:
    Interpolate(std::vector<std::shared_ptr<Expression>> _vectorExpression, std::shared_ptr<Number> _numInter);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class ODEFirstOrder : public Expression
{
private:
    std::shared_ptr<Function> funct;
    std::shared_ptr<Pair> initialValue;
    std::shared_ptr<Number> tFinal;
    std::shared_ptr<Variable> variable;
    std::shared_ptr<Pair> rungekuttaMethod(double t, double x, double f, double h, std::shared_ptr<Expression> function, Environment& env, std::shared_ptr<Variable> variable) const;
public:
    ODEFirstOrder(std::shared_ptr<Function> _funct, std::shared_ptr<Pair> _initialValue, std::shared_ptr<Number> _tFinal, std::shared_ptr<Variable> _variable);
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

class FindRootBisection : public Expression
{
private:
    std::shared_ptr<Pair> interval;
    std::shared_ptr<Function> function;
    std::shared_ptr<Variable> variable;
    std::shared_ptr<Number> iterationLimit;
    std::shared_ptr<Number> bisectionMethod(std::shared_ptr<Number> left, std::shared_ptr<Number> right, std::shared_ptr<Function> function, Environment& env) const;
public:
    FindRootBisection(std::shared_ptr<Pair> _interval, std::shared_ptr<Function> _function, std::shared_ptr<Variable> _variable, std::shared_ptr<Number> _iterationLimit = std::make_shared<Number>(100));
    std::shared_ptr<Expression> eval(Environment& env) const override;
    std::string toString() const noexcept override;
};

/*class ODESecondOrder : public Expression
{
private:
    std::shared_ptr<Function> funct;
    std::shared_ptr<Vector> initialValue;
    std::shared_ptr<Number> tFinal;
    std::shared_ptr<Variable> variable;
    std::shared_ptr<Number> rungekuttaMethod(double t, double x, int f, int h, std::shared_ptr<Expression> function, Environment& env, std::shared_ptr<Variable> variable) const;
public:
    ODESecondOrder(std::shared_ptr<Function> _funct, std::shared_ptr<Vector> _initialValue, std::shared_ptr<Number> _tFinal, std::shared_ptr<Variable> _variable);
    std::shared_ptr<Expression> eval(Environment& env) const override;
};*/