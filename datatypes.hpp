#include <cstdint>
#include <set>
#include <iostream>
#include <cmath>

// Interfaz Expresion
class Expresion {
public:
    virtual double evaluar() const = 0;
    virtual ~Expresion() {}
};

// Implementación de expresión Seno
class Seno : public Expresion {
private:
    Expresion* expresionInterior; // Expresión dentro del seno

public:
    Seno(Expresion* exp) : expresionInterior(exp) {}

    double evaluar() const override {
        return std::sin(expresionInterior->evaluar());
    }
};

class Matrix {

private:
    uint64_t rows;
    uint64_t colums;

};

class Point {

private:
    double x;
    double y;

};

class SetOfPoints {

private:
    std::set<Point> points_set;
};

class Equation {
    std::string rigth_side_exp;
    std::string left_side_exp;
};

class Function {

private:
    std::string exp;
};

class SystemOfEquations {

};

class FirstOrderDifferentialEquation {

};

class HigherOrderDifferentialEquation {

};

class IntegerValue {

};

class RealValue {

};

class Interval {

};

class Integral {

};

class Constants {

};

class Variable {

};