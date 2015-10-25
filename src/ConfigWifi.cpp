

#include "EEPROM.h"
#include "ESP8266WiFi.h"

#include "ConfigWifi.h"
bool ConfigWifi::Save()
{
      EEPROM.begin(512);
      delay(10);
      EEPROM.put(m_saveposition, m_ssid);
      delay(10);
      EEPROM.put(m_saveposition + SSID_MAX_SIZE, m_wifiKey);
      delay(10);
      EEPROM.put(m_saveposition + SSID_MAX_SIZE + WIFIKEY_MAX_SIZE , m_host);
      delay(10);
      yield();
      EEPROM.end(); 
}

bool ConfigWifi::Restore()
{

 EEPROM.begin(512);
  delay(100);
  for(int i = 0 ; i < SSID_MAX_SIZE ; i++)
  {
    m_ssid[i] = EEPROM.read(m_saveposition + i);   
  }
 int start_position = SSID_MAX_SIZE + m_saveposition;
  for(int i = 0 ; i < WIFIKEY_MAX_SIZE ; i++)
  {
   m_wifiKey[i] = EEPROM.read(start_position + i );   
  }
  
  start_position = WIFIKEY_MAX_SIZE + SSID_MAX_SIZE + m_saveposition;  
  
  for(int i = 0 ; i < HOST_MAX_SIZE ; i++)
  {
   m_host[i] = EEPROM.read(start_position + i );   
  }
  
  yield();
  EEPROM.end();  
}


bool ConfigWifi::Reset()
{
     EEPROM.begin(512);
     unsigned int position_end = SSID_MAX_SIZE + WIFIKEY_MAX_SIZE + HOST_MAX_SIZE;
      for (int i = 0; i < position_end; i++)
      {
        EEPROM.write(i, 0);  
      }
     EEPROM.end()  ;
}

