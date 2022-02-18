//Expr.h
//Declaration of class expr_node, binary_node, uni_node, Expr
//Modify class expr_node, uni_node, and binary node when implementing Part.E

#ifndef EXPR_FILE
#define EXPR_FILE

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "LargeNumber.h"
using namespace std;

class Expr;
class expr_node;
class uni_node;
class binary_node;
class LargeNumber;

class Expr
{

public:
    Expr(const Expr &expr);
    Expr(const string &operand);
    Expr(const string &op, Expr left, Expr right);
    ~Expr();
    Expr &operator=(const Expr &expr);
    LargeNumber eval() const;
    string getString() const;
    void subst(const string &from, const string &to);
    void unhook();

protected:
    expr_node *p;
};

class expr_node
{
public:
    expr_node() : count(1) {}
    virtual ~expr_node() {}
    virtual LargeNumber eval() const = 0;
    virtual void subst(const string &, const string &) = 0;
    virtual string getString() const = 0;
    int count;
};

class uni_node : public expr_node
{
private:
    string value;

public:
    uni_node(const string &_val);
    ~uni_node();
    LargeNumber eval() const;
    void subst(const string &from, const string &to);
    string getString() const;
};

class binary_node : public expr_node
{
private:
    string op;
    Expr lchild;
    Expr rchild;

public:
    binary_node(const string &_op, Expr lch, Expr rch);
    ~binary_node(); // should also delete its subtree recursively
    LargeNumber eval() const;
    void subst(const string &from, const string &to);
    string getString() const;
};

#endif