#pragma once

#include "expressions.hpp"

class Statement
{
public:
    virtual void execute(std::shared_ptr<Expression>, std::string) const = 0;
    virtual ~Statement() {}
};
//Singleton
class Display : public Statement
{
public:
    static Display& getInstance();
    void execute(std::shared_ptr<Expression>, std::string name = "") const override;
private:
    Display() {}
    Display(const Display&) = delete;
    Display& operator= (const Display&) = delete;
};