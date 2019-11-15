/***************************
// Module: CUtils
// Creator: mwh
// Time: 2019-11-07
//**************************/

#include "CUtils.h"


using namespace std;


/**********************************************************
*
*功能：去前空格
*
*str：源字符串
*
*反回值：去除前空格后的字符串
*
***********************************************************/
string &CUtils::Ltrim(string &str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(),
        std::not1(std::ptr_fun(::isspace))));

    return str;

}

/**********************************************************
*
*功能：去后空格
*
*str：源字符串
*
*反回值：去除后空格后的字符串
*
***********************************************************/
string &CUtils::Rtrim(string &str)
{
    str.erase(std::find_if(str.rbegin(), str.rend(),
        std::not1(std::ptr_fun(::isspace))).base(),
        str.end());

    return str;

}

/**********************************************************
*
*功能：去前后空格
*
*str：源字符串
*
*反回值：去除前后空格后的字符串
*
***********************************************************/
string &CUtils::Trim(string &str)
{
    return Rtrim(Ltrim(str));
}


/**********************************************************
*
*功能：去掉指定符号
*
*str：源字符串
*
*反回值：去掉指定符号后的字符串
*
***********************************************************/
string & CUtils::DelSymbol(string & str)
{
    // TODO: 在此处插入 return 语句
    char s[12] = "\"";
    string::iterator sit = str.begin();
    while (sit != str.end()) {
        
        string::size_type pos = str.find("\""); //使用find( char )成员函数定位'x'的位置
        if (pos != str.npos){
            str.erase(pos, 1); //使用erase( char )成员函数删除位于pos的字符
        } else { 
            sit++;
        }
       
    }
  
    return str;
}


/**********************************************************
*
*功能：删除字段后面注释
*
*str：源字符串
*
*反回值：删除字段后面注释后的字符串
*
***********************************************************/

string & CUtils::DelNote(string & str)
{
    // TODO: 在此处插入 return 语句
    string::size_type pos = str.find("#"); //使用find( char )成员函数定位'x'的位置
    if (pos != str.npos){
        str.erase(pos); //使用erase( char )成员函数删除位于pos后面的全部字符
    }
   
    return str;
}
