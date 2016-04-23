
#include "commande.h"
#include "../driver/uart.h"
#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "ip_addr.h"
#include "espconn.h"
#include "user_interface.h"
#include "clientTCP.h"

#include "mem.h"
#define packet_size2   (2 * 1024)
Configuration config;

void ProcessChar(uint8 Dchar,Mess * pmess)
{
	switch(pmess->Status)
	{
		case E_ID:
			if(Dchar > 0)
			{
				pmess->Id = Dchar;
				pmess->Status = E_SIZE;

				os_printf("NEW CMD  !!! \r\n");
				pmess->DataPos = 0;
			}
			break;
		case E_SIZE:				
			pmess->Size = Dchar;
			pmess->Status = E_DATA;
			break;
		case E_DATA:
			pmess->Data[pmess->DataPos] = Dchar;
                        
				pmess->DataPos ++;
			if( pmess->DataPos == pmess->Size)
			{
				ProcessMess(pmess);
				pmess->Status = E_ID;
				pmess->DataPos = 0;
			}
			break;
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

			os_printf("CMD_DATA  !!! \r\n");

	   		os_printf(" pmess->size %d \r\n", pmess->Size);
	   		os_printf(" pmess->Data[0] %d \r\n", pmess->Data[0]);
	   		os_printf(" pmess->Data[1] %d \r\n", pmess->Data[1]);
	   		os_printf(" pmess->Data[2] %d \r\n", pmess->Data[2]);
	   		os_printf(" pmess->Data[3] %d \r\n", pmess->Data[3]);


			os_printf("Data send  !!! \r\n");

			if( pmess->Size!= 0)
			{
 				int8 ret= espconn_send(user_conn, pmess->Data, pmess->Size);
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

