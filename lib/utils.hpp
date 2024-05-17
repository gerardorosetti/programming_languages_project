#pragma once

#include <iostream>
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
};

class Expression;
class Statement;

using Environment = std::forward_list<std::pair<char, std::shared_ptr<Expression>>>;

using ExpressionPtr = std::shared_ptr<Expression>;
using StatementPtr = std::shared_ptr<Statement>;