#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "ip_addr.h"
#include "espconn.h"
#include "clientUDP.h"
#include "user_interface.h"
#include "mem.h"

#define NET_DOMAIN "cn.bing.com"
#define pheadbuffer "GET / HTTP/1.1\r\nUser-Agent: curl/7.37.0\r\nHost: %s\r\nAccept: *///*\r\n\r\n"

#define packet_size   (2 * 1024)

os_timer_t test_timer;
esp_udp user_udp;
ip_addr_t udp_server_ip;
LOCAL struct espconn ptrespconn;

/******************************************************************************
 * FunctionName : user_udp_recv_cb
 * Description  : receive callback.
 * Parameters   : arg -- Additional argument to pass to the callback function
 * Returns      : none
*******************************************************************************/

LOCAL void ICACHE_FLASH_ATTR
user_udp_recv_cb(void *arg, char *pusrdata, unsigned short length)
{
   //received some data from tcp connection
   
    os_printf("tcp recv !!! %s \r\n", pusrdata);
   
}

/******************************************************************************
 * FunctionName : user_udp_sent_cb
 * Description  : data sent callback.
 * Parameters   : arg -- Additional argument to pass to the callback function
 * Returns      : none
*******************************************************************************/
LOCAL void ICACHE_FLASH_ATTR
user_udp_sent_cb(void *arg)
{
   //data sent successfully

//    os_printf("udp sent succeed !!! \r\n");
}

/******************************************************************************
 * FunctionName : user_esp_platform_sent
 * Description  : Processing the application data and sending it to the host
 * Parameters   : pespconn -- the espconn used to connetion with the host
 * Returns      : none
*******************************************************************************/

LOCAL void ICACHE_FLASH_ATTR
user_sent_data_udp(struct espconn *pespconn)
{
    char *pbuf = (char *)os_zalloc(packet_size);

    os_sprintf(pbuf, pheadbuffer, NET_DOMAIN);

   espconn_sendto(pespconn, pbuf, os_strlen(pbuf));
   
   os_free(pbuf);

}

/******************************************************************************
 * FunctionName : user_udp_connect_cb
 * Description  : A new incoming tcp connection has been connected.
 * Parameters   : arg -- Additional argument to pass to the callback function
 * Returns      : none
*******************************************************************************/

LOCAL void ICACHE_FLASH_ATTR
user_udp_connect_cb(void *arg)
{
    struct espconn *pespconn = arg;
    user_conn_udp = arg;
    os_printf("connect succeed !!! \r\n");
  
    user_sent_data_udp(pespconn);
}


/******************************************************************************
 * FunctionName : user_check_ip_udp
 * Description  : check whether get ip addr or not
 * Parameters   : none
 * Returns      : none
*******************************************************************************/

void ICACHE_FLASH_ATTR
user_check_ip_udp(void)
{
    struct ip_info ipconfig;

   //disarm timer first
    os_timer_disarm(&test_timer);

   //get ip info of ESP8266 station
    wifi_get_ip_info(STATION_IF, &ipconfig);

    if (wifi_station_get_connect_status() == STATION_GOT_IP && ipconfig.ip.addr != 0)
   {
      os_printf("got ip !!! \r\n");

      // Connect to tcp server as NET_DOMAIN
      user_udp_conn.proto.udp = &user_udp;
      user_udp_conn.type = ESPCONN_UDP;
  
	const char esp_udp_server_ip[4] = {192, 168, 1, 10}; // remote IP of TCP server

       os_memcpy(user_udp_conn.proto.udp->remote_ip, esp_udp_server_ip, 4);

       user_udp_conn.proto.udp->remote_port = 55056;  // remote port
     
       user_udp_conn.proto.udp->local_port = espconn_port(); //local port of ESP8266
 
 	espconn_regist_recvcb(&user_udp_conn, user_udp_recv_cb);
    	espconn_regist_sentcb(&user_udp_conn, user_udp_sent_cb);

        espconn_create(&user_udp_conn);   // create udp
	user_sent_data_udp(&user_udp_conn);




    }
   else
   {

           //re-arm timer to check ip
            os_timer_setfn(&test_timer, (os_timer_func_t *)user_check_ip_udp, NULL);
            os_timer_arm(&test_timer, 100, 0);
    }
}


/******************************************************************************
 * FunctionName : user_set_station_config
 * Description  : set the router info which ESP8266 station will connect to
 * Parameters   : none
 * Returns      : none
******************************************************************************/

void ICACHE_FLASH_ATTR
user_set_station_config_udp(void)
{

   os_timer_disarm(&test_timer);
    os_timer_setfn(&test_timer, (os_timer_func_t *)user_check_ip_udp, NULL);
    os_timer_arm(&test_timer, 2000, 0);

}

