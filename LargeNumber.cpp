#include "LargeNumber.h"
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

// null constructor
LargeNumber::LargeNumber()
{
}
// LargeNumber a("123456")
LargeNumber::LargeNumber(const string &raw) : number(raw)
{
}
// copy constructor
LargeNumber::LargeNumber(const LargeNumber &ref) : number(ref.number) {}
// destructor
LargeNumber::~LargeNumber() {}

// addition
LargeNumber LargeNumber::operator+(const LargeNumber &num) const
{
    int carry = 0;
    bool positive = true;
    string s1 = number, s2 = num.number;
    if (number[0] == '-' && num.number[0] != '-')
    {
        string positive_number;
        for (int i = 1; i < number.size(); i++)
            positive_number += number[i];
        return LargeNumber(num.number) - LargeNumber(positive_number);
    }
    else if (number[0] != '-' && num.number[0] == '-')
    {
        string positive_number;
        for (int i = 1; i < num.number.size(); i++)
            positive_number += num.number[i];
        return LargeNumber(number) - LargeNumber(positive_number);
    }
    else if (number[0] == '-' && num.number[0] == '-')
    {
        positive = false;
        s1 = "";
        s2 = "";
        for (int i = 1; i < number.size(); i++)
            s1 += number[i];
        for (int i = 1; i < num.number.size(); i++)
            s2 += num.number[i];
    }

    if (s1.size() <= s2.size())
    {
        string temp = s1;
        s1 = s2;
        s2 = temp;
    }

    unsigned int i = s1.size();
    unsigned int j = s2.size();

    while (j > 0)
    {
        int temp = carry + s1[i - 1] + s2[j - 1] - '0' - '0';
        temp >= 10 ? carry = 1, temp %= 10 : carry = 0;
        s1[i - 1] = char(temp + '0');
        i--;
        j--;
    }
    while (i > 0)
    {
        int temp = carry + s1[i - 1] - '0';
        temp >= 10 ? carry = 1, temp %= 10 : carry = 0;
        s1[i - 1] = char(temp + '0');
        i--;
    }
    if (carry == 1)
        s1 = "1" + s1;
    for (int i = 0; i < s1.size(); i++)
    {
        if (s1[i] != '0')
        {
            s1.erase(0, i);
            break;
        }
    }
    if (positive)
        return LargeNumber(s1);
    else
        return LargeNumber("-" + s1);
}

// substraction
LargeNumber LargeNumber::operator-(const LargeNumber &num) const
{
    string s1 = number, s2 = num.number;
    bool positive = true;
    int borrow = 0;
    if (number[0] == '-' && num.number[0] != '-')
        return LargeNumber(number) + LargeNumber("-" + num.number);
    if (number[0] != '-' && num.number[0] == '-')
    {
        string positive_number;
        for (int i = 1; i < num.number.size(); i++)
            positive_number += num.number[i];
        return LargeNumber(number) + LargeNumber(positive_number);
    }
    if (number[0] == '-' && num.number[0] == '-')
    {
        s1 = "";
        s2 = "";
        for (int i = 1; i < number.size(); i++)
            s2 += number[i];
        for (int i = 1; i < num.number.size(); i++)
            s1 += num.number[i];
    }

    if (s1.size() < s2.size())
    {
        string temp = s1;
        s1 = s2;
        s2 = temp;
        positive = false;
    }
    else if (s1.size() == s2.size())
    {
        for (int i = 0; i < s1.size(); i++)
            if (s1[i] < s2[i])
            {
                string temp = s1;
                s1 = s2;
                s2 = temp;
                positive = false;
                break;
            }
            else
            {
                if (number[i] == num.number[i])
                    continue;
                else if (number[i] > num.number[i])
                    break;
            }
    }
    unsigned long i = s1.size();
    unsigned long j = s2.size();
    while (j > 0)
    {
        int temp = s1[i - 1] - s2[j - 1] - '0' + '0' - borrow;
        temp < 0 ? borrow = 1, temp += 10 : borrow = 0;
        s1[i - 1] = char(temp + '0');
        i--;
        j--;
    }
    while (i > 0)
    {
        int temp = s1[i - 1] - '0' - borrow;
        temp < 0 ? borrow = 1, temp += 10 : borrow = 0;
        s1[i - 1] = char(temp + '0');
        i--;
    }
    for (int i = 0; i < s1.size(); i++)
    {
        if (s1[i] != '0')
        {
            s1.erase(0, i);
            break;
        }
    }
    if (positive)
        return LargeNumber(s1);
    else
        return LargeNumber("-" + s1);
}

// multiplication
LargeNumber LargeNumber::operator*(const LargeNumber &num) const
{
    string s1 = number, s2 = num.number;
    bool positive = true;

    if (number[0] == '-' && num.number[0] != '-')
    {
        positive = false;
        s1 = "";
        for (int i = 1; i < number.size(); i++)
            s1 += number[i];
    }
    else if (number[0] != '-' && num.number[0] == '-')
    {
        positive = false;
        s2 = "";
        for (int i = 1; i < num.number.size(); i++)
            s2 += num.number[i];
    }
    else if (number[0] == '-' && num.number[0] == '-')
    {
        s1 = "";
        s2 = "";
        for (int i = 1; i < number.size(); i++)
            s1 += number[i];
        for (int i = 1; i < num.number.size(); i++)
            s2 += num.number[i];
    }

    if (number.size() <= num.number.size())
    {
        string temp = s1;
        s1 = s2;
        s2 = temp;
    }

    LargeNumber ans("0");
    for (int i = 0; i < s2.size(); i++)
    {
        LargeNumber temp_ans("0");
        int addtime = s2[s2.size() - 1 - i] - '0';
        for (int j = 0; j < addtime; j++)
            temp_ans = temp_ans + LargeNumber(s1);
        for (int j = 0; j < i; j++)
            temp_ans.number += '0';
        ans = ans + temp_ans;
    }
    if (positive)
        return ans;
    else
        return LargeNumber("-" + ans.number);
}

// quotient
LargeNumber LargeNumber::operator/(const LargeNumber &num) const
{
    string s1 = number, s2 = num.number;
    bool positive = true;
    if (number[0] == '-' && num.number[0] != '-')
    {
        positive = false;
        s1 = "";
        for (int i = 1; i < number.size(); i++)
            s1 += number[i];
    }
    else if (number[0] != '-' && num.number[0] == '-')
    {
        positive = false;
        s2 = "";
        for (int i = 1; i < num.number.size(); i++)
            s2 += num.number[i];
    }
    else if (number[0] == '-' && num.number[0] == '-')
    {
        s1 = "";
        s2 = "";
        for (int i = 1; i < number.size(); i++)
            s1 += number[i];
        for (int i = 1; i < num.number.size(); i++)
            s2 += num.number[i];
    }
    if (!theformerisbigger(s1, s2))
        return LargeNumber("0");
    LargeNumber quotient(""); // store numbers
    LargeNumber sub_s1("");
    // function to compare two string
    for (int i = 0; i < s1.size(); i++)
    {
        int sub_quotient = 0;
        string s(1, s1[i]);
        sub_s1 = sub_s1 + LargeNumber(s);
        while (theformerisbigger(sub_s1.number, s2))
        {
            sub_s1 = sub_s1 - LargeNumber(s2);
            sub_quotient++;
        }
        quotient.number += char(sub_quotient + '0');
    }
    for (int i = 0; i < quotient.number.size(); i++)
    {
        if (quotient.number[i] != '0')
        {
            quotient.number.erase(0, i);
            break;
        }
    }
    if (positive)
        return quotient;
    else
        return LargeNumber("-" + quotient.number);
}

bool LargeNumber::theformerisbigger(string &s1, string &s2) const
{
    if (s1.size() < s2.size())
        return false;
    if (s1.size() > s2.size())
        return true;
    for (int i = 0; i < s1.size(); i++)
        if (s1[i] < s2[i])
            return false;
        else
        {
            if (s1[i] == s2[i])
                continue;
            else if (s1[i] > s2[i])
                break;
        }
    return true;
}

// remainder
LargeNumber LargeNumber::operator%(const LargeNumber &num) const
{
    LargeNumber a(number);
    LargeNumber b(num.number);
    return a - (a / b) * b;
}

// copier
LargeNumber LargeNumber::operator=(const LargeNumber &num)
{
    number = num.number;
    return LargeNumber(number);
}
