/***************************
// Module: CUtils
// Creator: mwh
// Time: 2019-11-07
//**************************/

#include "CUtils.h"


using namespace std;


/**********************************************************
*
*���ܣ�ȥǰ�ո�
*
*str��Դ�ַ���
*
*����ֵ��ȥ��ǰ�ո����ַ���
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
*���ܣ�ȥ��ո�
*
*str��Դ�ַ���
*
*����ֵ��ȥ����ո����ַ���
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
*���ܣ�ȥǰ��ո�
*
*str��Դ�ַ���
*
*����ֵ��ȥ��ǰ��ո����ַ���
*
***********************************************************/
string &CUtils::Trim(string &str)
{
    return Rtrim(Ltrim(str));
}


/**********************************************************
*
*���ܣ�ȥ��ָ������
*
*str��Դ�ַ���
*
*����ֵ��ȥ��ָ�����ź���ַ���
*
***********************************************************/
string & CUtils::DelSymbol(string & str)
{
    // TODO: �ڴ˴����� return ���
    char s[12] = "\"";
    string::iterator sit = str.begin();
    while (sit != str.end()) {
        
        string::size_type pos = str.find("\""); //ʹ��find( char )��Ա������λ'x'��λ��
        if (pos != str.npos){
            str.erase(pos, 1); //ʹ��erase( char )��Ա����ɾ��λ��pos���ַ�
        } else { 
            sit++;
        }
       
    }
  
    return str;
}


/**********************************************************
*
*���ܣ�ɾ���ֶκ���ע��
*
*str��Դ�ַ���
*
*����ֵ��ɾ���ֶκ���ע�ͺ���ַ���
*
***********************************************************/

string & CUtils::DelNote(string & str)
{
    // TODO: �ڴ˴����� return ���
    string::size_type pos = str.find("#"); //ʹ��find( char )��Ա������λ'x'��λ��
    if (pos != str.npos){
        str.erase(pos); //ʹ��erase( char )��Ա����ɾ��λ��pos�����ȫ���ַ�
    }
   
    return str;
}
