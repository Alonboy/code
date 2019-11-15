#pragma once

#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>



extern time_t UNIXTIME;		/* update this every loop to avoid the time() syscall! */
tm GameTick();
void RefreshGlobalTime();
void AddError(const char* msg, bool local_display = true);


struct ConfigSetting
{
    uint32_t AsUInt32; // תuint32_t
    std::string AsString; // תstring
    int AsInt; // תint
    float AsFloat; // תfloat
    bool AsBool; // תbool
};

struct ConfigBlock
{
    std::unordered_map<std::string, ConfigSetting> block;
};

class ConfigBase
{
public:
    ConfigBase(std::string name);
    virtual ~ConfigBase();
    
public:

    bool LoadConfig();
    void EnableDefHint(ConfigSetting &confg, const std::string sValue, bool flag); //  ת��������������
    uint32_t GetUInt32Default(const char * block, const char* name, const int def);
    std::string GetStringDefault(const char * block, const char* name, const int def);
    int GetIntDefault(const char * block, const char* name, const int def);
    float GetFloatDefault(const char * block, const char* name, const int def);
    bool GetBoolDefault(const char * block, const char* name, const int def);
    bool CheckStrPattern(std::string str);
    void GetBaseConfig();
private:
    //std::unordered_map<std::string, ConfigBlock> baseConfig_;
    std::unordered_map<std::string, std::unordered_map<std::string, ConfigSetting>> mBaseConfig_;
    std::string sFileName_;
};



