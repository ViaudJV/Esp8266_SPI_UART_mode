
#include "commande.h"
#include "../driver/uart.h"
#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "ip_addr.h"
#include "espconn.h"
#include "user_interface.h"

Configuration config;
uint8 DataPos = 0;
void ProcessChar(uint8 Dchar,Mess * pmess)
{
	switch(Status)
	{
		case E_ID:
			pmess->Id = Dchar;
			Status = E_SIZE;
			DataPos = 0;
			break;
		case E_SIZE:				
			pmess->Size = Dchar;
			Status = E_DATA;
			break;
		case E_DATA:
			pmess->Data[DataPos] = Dchar;
                        DataPos ++;
			if( DataPos & pmess->Size)
			{
				break;
			}
		case E_END:
			ProcessMess(pmess);
			Status = E_ID;
		default:
			break;
	}
}


void ProcessMess(Mess * pmess)
{
	 
	switch(pmess->Id)
	{
		case CMD_DATA:
			{
			uint8 i = 0;
			while( i != pmess->Size )
				{		
			            uart_tx_one_char(UART0,  pmess->Data[i]);
				    i++;
				}
			break;
			}
		case CM_MODE:
			{
				if(  pmess->Data[0] <= 0x03)
					wifi_set_opmode( pmess->Data[0]);
				break;
			}
		case CM_STASSID:
			{
				if(!config.USE)
				{
					config.USE = 0x01;
					os_memset(config.StaSsid,0x00,sizeof(config.StaSsid));
					os_memcpy(config.StaSsid, pmess->Data,pmess->Size);
					config.USE = 0x00;
				}	
	        		break;
			}
		case CM_STAPWD :
			{
				if(!config.USE)
				{
					config.USE = 0x01;
					os_memset(config.StaPwd,0x00,sizeof(config.StaPwd));
					os_memcpy(config.StaPwd, pmess->Data,pmess->Size);
					config.USE = 0x00;
				}
				break;
			}
		case CM_STAEN :
			{
				if(!config.USE)
				{
					config.USE = 0x01;
					if( pmess->Data[0])
					{

					//    station_config configurationSTA;
					   
					    static struct station_config configurationSTA;
					    configurationSTA.bssid_set= 0;
					    os_memcpy( &configurationSTA.ssid, config.StaSsid, 32 );
					    os_memcpy( &configurationSTA.password, config.StaPwd, 64 );
					    wifi_station_set_config( &configurationSTA );
					    wifi_station_connect();
					}
					else
					{
					    wifi_station_disconnect();
					}
					config.USE = 0x00;
				}
				break;
			}
		case CM_APSSID:
			{
				if(!config.USE)
				{
					config.USE = 0x01;
					os_memset(config.APSsid,0x00,sizeof(config.APSsid));
					os_memcpy(config.APSsid, pmess->Data, pmess->Size);
					config.USE = 0x00;
				}	
	        		break;
			}
		case CM_APPWD :
			{
				if(!config.USE)
				{
					config.USE = 0x01;
					os_memset(config.APPwd,0x00,sizeof(config.APPwd));
					os_memcpy(config.APPwd, pmess->Data, pmess->Size);
					config.USE = 0x00;
				}
				break;
			}
		case CM_APEN :
			{
				if(!config.USE)
				{
					config.USE = 0x01;
					if( pmess->Data[0])
					{

					    struct softap_config configurationAP;
					    os_memcpy( &configurationAP.ssid, config.StaSsid, 32 );
					    os_memcpy( &configurationAP.password, config.StaPwd, 64 );
					    wifi_softap_set_config( &configurationAP );
					    wifi_station_connect();
					}
					config.USE = 0x00;
				}
				break;
			}
		case CM_TCPEN :
			{
				if(!config.USE)
				{
					config.USE = 0x01;
					if( pmess->Data[0])
					{
					
					}
					config.USE = 0x00;
				} 
				break;
			}
		case CM_UDPEN:
			break;
		case CM_UDPPORT:
			{			
				if(!config.USE)
				{
					config.USE = 0x01;
					config.UDPPort = 0;
					config.UDPPort = (uint16)( pmess->Data[0]) + ((uint16) pmess->Data[1]) << 8;
					config.USE = 0x00;
				} 
				break;
			}
		case CM_TCPPORT:
			{
				if(!config.USE)
				{
					config.USE = 0x01;
					config.TCPPort = 0;
					config.TCPPort = (uint16)( pmess->Data[0]) + ((uint16) pmess->Data[1])<<8;
					config.USE = 0x00;
				} 
			break;
			}
		default:
			//Do nothing
			break;

	}
}

