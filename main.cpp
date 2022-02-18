#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <list>
#include "Expr.h"
using namespace std;

bool tokenizer(const string &str, vector<string> &tokens);
void Plant_Expression_Tree(vector<string> &tokens, list<Expr> &plant_tree);

int main(int argc, char *argv[])
{

    string str;
    vector<string> tokens;
    list<Expr> plant_tree;
    plant_tree.push_back(Expr("0"));
    cout << "ans = " << plant_tree.back().getString() << endl;
    cout << ">>> ";
    getline(cin, str);
    while (tokenizer(str, tokens))
    {
        Plant_Expression_Tree(tokens, plant_tree);
        cout << "ans= " << plant_tree.back().getString() << endl;
        cout << ">>> ";
        getline(cin, str);
        tokens.clear();
    }

    return 0;
}

bool tokenizer(const string &str, vector<string> &tokens)
{
    char *c_str = new char[str.length() + 1];
    strcpy(c_str, str.c_str());
    char *token;
    token = strtok(c_str, " ");
    while (token != NULL)
    {
        if (strcmp(token, "quit") == 0)
            return false;
        tokens.push_back(token);
        token = strtok(NULL, " ");
    }
    delete[] c_str;
    return true;
}

void Plant_Expression_Tree(vector<string> &tokens, list<Expr> &plant_tree)
{
    Expr ans = plant_tree.back();
    plant_tree.pop_back();
    for (int i = tokens.size() - 1; i >= 0; i--)
    {
        if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/" || tokens[i] == "%")
        {
            Expr left = plant_tree.back();
            plant_tree.pop_back();
            Expr right = plant_tree.back();
            plant_tree.pop_back();
            plant_tree.push_back(Expr(tokens[i], left, right));
        }
        else if (tokens[i] == "ans")
        {
            plant_tree.push_back(ans);
        }
        else if (tokens[i] == "eval")
        {
            string eval = plant_tree.back().eval().number;
            plant_tree.pop_back();
            plant_tree.push_back(Expr(eval));
        }
        else if (tokens[i] == "subst")
        {
            Expr tree = plant_tree.back();
            plant_tree.pop_back();
            Expr from = plant_tree.back();
            plant_tree.pop_back();
            Expr to = plant_tree.back();
            plant_tree.pop_back();
            tree.subst(from.getString(), to.getString());
            plant_tree.push_back(tree);
        }
        else
        {
            plant_tree.push_back(Expr(tokens[i]));
        }
    }
    return;
}