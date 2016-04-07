#include "ets_sys.h"
#include "os_type.h"
#include "osapi.h"
#include "mem.h"
#include "user_interface.h"
//#include "lwip/stats.h"

#include "espconn.h"
LOCAL uint16_t server_timeover = 60*60*12; // yes. 12h timeout. so what? :)
LOCAL struct espconn masterconn;

const char *msg_welcome = "Welcome!\n\n";


LOCAL void ICACHE_FLASH_ATTR
shell_tcp_disconcb(void *arg) {
    struct espconn *pespconn = (struct espconn *) arg;

    os_printf("tcp connection disconnected\n");
}

LOCAL void ICACHE_FLASH_ATTR
shell_tcp_recvcb(void *arg, char *pusrdata, unsigned short length)
{
    struct espconn *pespconn = (struct espconn *) arg;

    if(length >= 2 && pusrdata[0] == 0xFF && (pusrdata[1] & 0xF0) == 0xF0) {       
        espconn_sent(pespconn, (uint8*)msg_welcome, os_strlen(msg_welcome));
    } else {
        os_printf(">'%s' ", pusrdata);

        int i;
        for(i = 0; i < length; i++) {
            os_printf("0x%02X ", pusrdata[i]);
        }
        os_printf("\n");
         espconn_sent(pespconn, pusrdata, length); //echo
    }
}

LOCAL void ICACHE_FLASH_ATTR
tcpserver_connectcb(void *arg)
{
    struct espconn *pespconn = (struct espconn *)arg;

    os_printf("tcp connection established\n");

    espconn_regist_recvcb(pespconn, shell_tcp_recvcb);
    // espconn_regist_reconcb(pespconn, tcpserver_recon_cb);
    espconn_regist_disconcb(pespconn, shell_tcp_disconcb);
    // espconn_regist_sentcb(pespconn, tcpclient_sent_cb);
}

void ICACHE_FLASH_ATTR
shell_init(void)
{
    masterconn.type = ESPCONN_TCP;
    masterconn.state = ESPCONN_NONE;
    masterconn.proto.tcp = (esp_tcp *)os_zalloc(sizeof(esp_tcp));
    masterconn.proto.tcp->local_port = 23;
    espconn_regist_connectcb(&masterconn, tcpserver_connectcb);
    espconn_accept(&masterconn);
    espconn_regist_time(&masterconn, server_timeover, 0);

    os_printf("[%s] initializing shell!\n", __func__);
}

