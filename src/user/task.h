

#define PRIO_UART 1
#define PRIO_SPI 0


#define TASK_LENGHT 10

#define SPI_BUFF 32
#define UDP_BUFF 64


#define MISO_EVENT 0
#define UDP_EVENT 1

extern uint8_t positiondebut;
extern uint8_t positionfin;
extern uint8_t DataSPIBuf[SPI_BUFF][SPI_BUFF];



extern uint8_t positiondebutUDP;
extern uint8_t positionfinUDP;
extern uint8_t DataUDPBuf[UDP_BUFF][UDP_BUFF];



os_event_t    uart_recvTaskQueue[TASK_LENGHT];
os_event_t    all_recvTaskQueue[TASK_LENGHT];

void ICACHE_FLASH_ATTR uart_recvTask(os_event_t *events);


void ICACHE_FLASH_ATTR all_recvTask(os_event_t *events);
