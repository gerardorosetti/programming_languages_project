#pragma once

#include "expressions.hpp"

class Statement
{
public:
    virtual void execute() const = 0;
    virtual ~Statement() {}
};

class Display : public Statement
{
public:
    Display(std::shared_ptr<Expression>);
    void execute() const override;
private:
    std::shared_ptr<Expression> exp;
};

class Print :public Statement
{
public:
    Print(std::string);
    void execute() const override;
private:
    std::string str;
};