#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "ip_addr.h"
#include "espconn.h"
#include "user_interface.h"
#include "user_config.h"
#include "../driver/uart.h"


void uart0_rx_intr_handler(void *para)
{
	
}

void wifi_callback( System_Event_t *evt )
{
    os_printf( "%s: %d\n", __FUNCTION__, evt->event );
    
		char toto[7] = "hello\n\0";
		//uart0_tx_buffer(toto, 7);
    switch ( evt->event )
    {
        case EVENT_STAMODE_CONNECTED:
        {
		
		char toto[7] = "hello\n\0";
		//uart0_tx_buffer(toto, 7);
	   	os_printf("connect to ssid %s, channel %d\n",
			evt->event_info.connected.ssid,
			evt->event_info.connected.channel);
	    	break;
        }

        case EVENT_STAMODE_DISCONNECTED:
        {
	    os_printf("disconnect from ssid %s, reason %d\n",
	                evt->event_info.disconnected.ssid,
	                evt->event_info.disconnected.reason);
	    
	    deep_sleep_set_option( 0 );
	    system_deep_sleep( 60 * 1000 * 1000 );  // 60 seconds

	    break;
        }

        case EVENT_STAMODE_GOT_IP:
        {
            os_printf("ip:" IPSTR ",mask:" IPSTR ",gw:" IPSTR,
                        IP2STR(&evt->event_info.got_ip.ip),
                        IP2STR(&evt->event_info.got_ip.mask),
                        IP2STR(&evt->event_info.got_ip.gw));
            os_printf("\n");
            break;
        }
        
        default:
        {
            break;
        }
    }
}


void user_init( void )
{
    static struct station_config config;
    uart_div_modify( 0, UART_CLK_FREQ / ( 115200 ) );
    os_printf( "%s\n", __FUNCTION__ );
    //uart_init(115200,9600);
    wifi_station_set_hostname( HOSTNAME );
    wifi_set_opmode_current( SOFTAP_MODE );
    gpio_init();
//os_printf sur Uart0

    //uart0_tx_buffer("init\n", 5);
    config.bssid_set = 1;
    os_memcpy( &config.ssid, SSID, 14 );
    os_memcpy( &config.password, PASSWORD, 9 );
    wifi_station_set_config( &config );
    wifi_station_connect();
   // wifi_set_event_handler_cb( wifi_callback );



}

