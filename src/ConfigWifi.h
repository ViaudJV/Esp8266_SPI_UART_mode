#ifndef CONFIGWIFI__H
#define CONFIGWIFI__H

#define SSID_MAX_SIZE     32
#define WIFIKEY_MAX_SIZE  64
#define HOST_MAX_SIZE     64


class ConfigWifi
{
 private:
  unsigned int m_saveposition; 
 public:
  char m_ssid[SSID_MAX_SIZE];
  char m_wifiKey[WIFIKEY_MAX_SIZE];
  char m_host[HOST_MAX_SIZE];

 public:
   ConfigWifi(){m_saveposition = 0;};
  ~ConfigWifi(){};
   void SetSavePosition(unsigned int saveposition){m_saveposition = saveposition;};
   bool Save(); 
   bool Restore(); 
   bool Reset(); 
  
};

#endif
