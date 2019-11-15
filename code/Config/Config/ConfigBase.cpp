/***************************
// Module: ConfigBase
// Creator: mwh
// Time: 2019-11-07
// File: ConfigBase
//**************************/



#include "ConfigBase.h"
#include <iostream> // ��׼��
#include <fstream> // �ļ���д��
#include <time.h> // ʱ��
#include <regex> // ������ʽͷ�ļ�
#include "CUtils.h"


#define TIME_FORMAT "[%m-%d %H:%M:%S]  "
#define TIME_FORMAT_LENGTH 160
#define ARR_SIZE(A) (sizeof(A)/sizeof(A[0]))

//��ʱ����
#define FORMAT_LOG(fmt, ...)                                                                                       \
    char BUF_FORMAT_LOG[1024];                                                                                          \
    strftime(BUF_FORMAT_LOG, TIME_FORMAT_LENGTH, TIME_FORMAT, &GameTick());                                            \
    uint32_t BUF_LEN = TIME_FORMAT_LENGTH - 1;                                                                            \
    snprintf(&BUF_FORMAT_LOG[BUF_LEN], ARR_SIZE(BUF_FORMAT_LOG) - BUF_LEN, fmt, ##__VA_ARGS__); \
    return std::move(BUF_FORMAT_LOG);
    



//#define LOG_ERROR(msg, ... ) do {  FORMAT_LOG(msg, ##__VA_ARGS__); AddError(BUF_FORMAT_LOG); } while(false)
#define  LOG_ERROR(msg)  AddError(msg)

ConfigBase::ConfigBase(std::string name):sFileName_(name)
{ }


ConfigBase::~ConfigBase()
{ 

    auto it = mBaseConfig_.begin();
    for ( auto & outerItr :mBaseConfig_){

        auto inItr = outerItr.second;
       if (!inItr.empty()){
           inItr.clear();
       }
    }
    mBaseConfig_.clear();
}

void AddError(const char * msg, bool local_display)
{
    char BUF_FORMAT_LOG[TIME_FORMAT_LENGTH];
    memset(BUF_FORMAT_LOG, 0x00, sizeof(BUF_FORMAT_LOG)); //��ʼ��
    tm  tmp = GameTick();
    strftime(BUF_FORMAT_LOG, TIME_FORMAT_LENGTH, TIME_FORMAT,&tmp );

    strcat(BUF_FORMAT_LOG, msg);
    fputs(BUF_FORMAT_LOG, stdout);
    fputc('\n', stdout);
}

bool ConfigBase::LoadConfig()
{

    std::ifstream  readFile; //�ļ����
    readFile.open(sFileName_,std::ios::in);

    if (!readFile){
        LOG_ERROR("���ش���: Config�ļ���ȡʧ��, �����ļ�·��");
        return false;
    }

    std::string handleKey = "";
    char szline[TIME_FORMAT_LENGTH];

    // 0x0A ���з�
    while (!readFile.eof() && readFile.getline(szline, sizeof(szline), 0x0A)) {
        std::string sStr = std::string(szline);
        std::string nStr = CUtils::DelNote(sStr); //ȥ������ע��
        std::string &sline = CUtils::Trim(nStr); // ȥ���ո�
        if (sline.empty() || sline[0] == '#') {  // ����ע����
            continue;
        }

        if ('>' == sline[sline.size() - 1]) {
            handleKey = "";
            continue;
        }
        if ('<' == sline[0]) {
            handleKey = sline.substr(1, sline.size() - 1); 
            std::unordered_map<std::string, ConfigSetting> mBlock;
            mBaseConfig_.insert({handleKey,mBlock});    // initializer list insertion ��ʼ��ͷkeyֵ
            continue;
        }
        
        if (handleKey.empty()){
            LOG_ERROR("config �ļ����ô���");
            return false;
        }
        
        string::size_type pos = sline.find("=");
        if (string::npos == pos) {
            continue;
        }
        
        std::string strtemp = sline.substr(0, pos);
        std::string skey = CUtils::Trim(strtemp);
        strtemp = sline.substr(pos + 1, sline.size() - pos - 1);
        std::string s = CUtils::Trim(strtemp);
        std::string sValue = CUtils::DelSymbol(s);

        bool flag = CheckStrPattern(sValue);
        ConfigSetting configSet;
        EnableDefHint(configSet,sValue, flag);


        std::unordered_map<std::string, std::unordered_map<std::string, ConfigSetting>>::iterator itBlock = mBaseConfig_.begin();
        
        if (itBlock  != mBaseConfig_.end()) { //��������

            auto iter = mBaseConfig_.lower_bound(handleKey);
            if (iter != mBaseConfig_.end() && handleKey == iter->first) {
                iter->second.insert(std::make_pair(skey, configSet));
            }
        }
       
    }
    GetBaseConfig(); //����
    return false;
}

void ConfigBase::EnableDefHint(ConfigSetting &confg,const std::string sValue,bool flag)
{
    
    if (sValue.empty()){
        confg.AsBool = true;
        confg.AsFloat = 0.0f;
        confg.AsInt = 0;
        confg.AsString = sValue;
        confg.AsUInt32 = 0;
    }
     else if (flag) {
        confg.AsBool = true;     
        confg.AsFloat = std::stof(sValue);
        confg.AsInt = std::stoi(sValue);
        confg.AsString = sValue;
        confg.AsUInt32 = (uint32_t)std::stoul(sValue);
        
    } else {
        if (strcmp(sValue.c_str(),"false") == 0)
        {
            confg.AsBool = false;
        }else if (strcmp(sValue.c_str(), "true") == 0){
            confg.AsBool = true;
        } else { 
            confg.AsBool = true;
        }
        
        confg.AsFloat = 0.0f;
        confg.AsInt = 0;
        confg.AsString = sValue;
        confg.AsUInt32 = 0;
    }

}

uint32_t ConfigBase::GetUInt32Default(const char * block, const char * name, const int def)
{

    uint32_t asValue = 0;

    auto iterBlock = mBaseConfig_.find(block);
    if (iterBlock != mBaseConfig_.end()){
        auto iterSet = iterBlock->second.find(name);
        if (iterSet != iterBlock->second.end()){
            asValue = iterSet->second.AsUInt32;

        }

    }
    return uint32_t(asValue);
}

std::string ConfigBase::GetStringDefault(const char * block, const char * name, const int def)
{
    std::string asStr = "";
    auto iterBlock = mBaseConfig_.find(block);
    if (iterBlock != mBaseConfig_.end()) {
        auto iterSet = iterBlock->second.find(name);
        if (iterSet != iterBlock->second.end()) {
            asStr = iterSet->second.AsString;

        }
    }
    return std::string(asStr);
}

int ConfigBase::GetIntDefault(const char * block, const char * name, const int def)
{

    int asInt = 0;
    auto iterBlock = mBaseConfig_.find(block);
    if (iterBlock != mBaseConfig_.end()) {
        auto iterSet = iterBlock->second.find(name);
        if (iterSet != iterBlock->second.end()) {
            asInt = iterSet->second.AsInt;

        }
    }
    return asInt;
}

float ConfigBase::GetFloatDefault(const char * block, const char * name, const int def)
{
    float asFloat = 0.0f;
    auto iterBlock = mBaseConfig_.find(block);
    if (iterBlock != mBaseConfig_.end()) {
        auto iterSet = iterBlock->second.find(name);
        if (iterSet != iterBlock->second.end()) {
            asFloat = iterSet->second.AsFloat;

        }
    }
    return asFloat;
}

bool ConfigBase::GetBoolDefault(const char * block, const char * name, const int def)
{
    bool asBool = false;
    auto iterBlock = mBaseConfig_.find(block);
    if (iterBlock != mBaseConfig_.end()) {
        auto iterSet = iterBlock->second.find(name);
        if (iterSet != iterBlock->second.end()) {
            asBool = iterSet->second.AsBool;

        }
    }
    return asBool;
}

bool ConfigBase::CheckStrPattern(std::string str)
{
    std::string pattern {"[0-9]"}; // fixed telephone
    std::regex re(pattern);

    /* std::regex_match:
        �ж�һ��������ʽ(����re)�Ƿ�ƥ�������ַ�����str,����Ҫ������֤�ı�
        ע�⣬���������ʽ����ƥ�䱻��������ȫ�������򷵻�false;����������б��ɹ�ƥ�䣬����true
    */
    bool ret = std::regex_match(str, re);
    if (ret) {
        return true;
    }

    return false;
}

void ConfigBase::GetBaseConfig()
{
    auto at = mBaseConfig_;
}

 tm GameTick()
{
     time_t now;
     time(&now);// ��ͬ��now = time(NULL)
    struct tm g_localTime;
    g_localTime = *(localtime(&now));
    return g_localTime;
}

void RefreshGlobalTime()
{ }
