#pragma once 
#include "expressions.hpp"

class Statement
{
public:
    Statement(std::shared_ptr<Expression>);
    virtual void execute() const = 0;
    virtual ~Statement() {}
protected:
    std::shared_ptr<Expression> exp;
};

class Display : public Statement
{
public:
    using Statement::Statement;
    void execute() const override;
};