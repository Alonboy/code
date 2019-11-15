#pragma once
#include <iostream>

#include <algorithm>
#include <functional>
using namespace  std;
namespace  CUtils
{


    inline string& ltrim(string &str)
    {
        string::iterator p = find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isspace)));
        str.erase(str.begin(), p);
        return str;
    }

    inline string& rtrim(string &str)
    {
        string::reverse_iterator p = find_if(str.rbegin(), str.rend(), not1(ptr_fun<int, int>(isspace)));
        str.erase(p.base(), str.end());
        return str;
    }

    inline string& trim(string &str)
    {
        ltrim(rtrim(str));
        return str;
    }

    string &Ltrim(string &str);
    string &Rtrim(string &str);
    string &Trim(string &str);
    string &DelSymbol(string &str);
    string &DelNote(string &str);
};

