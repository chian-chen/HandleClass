#include <iostream>
#include <cstring>
#include <string>
#include "Expr.h"
using namespace std;

//  ************
//  class uni_node
//      string value;

uni_node::uni_node(const string &_val) : value(_val)
{
}

uni_node::~uni_node()
{
}

LargeNumber uni_node::eval() const
{
    return LargeNumber(value);
}

void uni_node::subst(const string &from, const string &to)
{
    if (from == "+" || from == "-" || from == "*" || from == "/" || from == "%")
        return;
    if (to == "+" || to == "-" || to == "*" || to == "/" || to == "%")
        return;
    if (value == from)
        value = to;
    return;
}

string uni_node::getString() const
{
    return value;
}

//  ************
//  class binary_node
//      string op;
//      Expr lchild;
//      Expr rchild;

binary_node::binary_node(const string &_op, Expr lch, Expr rch) : op(_op), lchild(lch), rchild(rch)
{
}

binary_node::~binary_node()
{
}

LargeNumber binary_node::eval() const
{
    if (op == "+")
        return lchild.eval() + rchild.eval();
    else if (op == "-")
        return lchild.eval() - rchild.eval();
    else if (op == "*")
        return lchild.eval() * rchild.eval();
    else if (op == "/")
        return lchild.eval() / rchild.eval();
    else
        return lchild.eval() % rchild.eval();
}

void binary_node::subst(const string &from, const string &to)
{
    lchild.subst(from, to);
    rchild.subst(from, to);
    return;
}

string binary_node::getString() const
{
    return op + " " + lchild.getString() + " " + rchild.getString();
}

//  ************
//  class Expr
//      expr_node *p;

Expr::Expr(const Expr &expr)
{
    p = expr.p;
    p->count++;
}
Expr::Expr(const string &operand)
{
    p = new uni_node(operand);
}

Expr::Expr(const string &op, Expr left, Expr right)
{
    p = new binary_node(op, left, right);
}
Expr::~Expr()
{
    unhook();
}
Expr &Expr::operator=(const Expr &expr)
{
    if (p != expr.p)
    {
        unhook();
        p = expr.p;
        (p->count++);
    }
    return *this;
}
LargeNumber Expr::eval() const
{
    return p->eval();
}
string Expr::getString() const
{
    return p->getString();
}
void Expr::subst(const string &from, const string &to)
{
    p->subst(from, to);
}

void Expr::unhook()
{
    --(p->count);
    if (p->count == 0)
        delete p;
}