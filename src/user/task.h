

#define PRIO_UART 1
#define PRIO_SPI 0


#define TASK_LENGHT 10

#define SPI_BUFF 32
#define TCP_BUFF 32


#define MISO_EVENT 0
#define TCP_EVENT 1
uint8_t positiondebut;
uint8_t positionfin; 
uint8_t DataSPIBuf[SPI_BUFF][SPI_BUFF];	
os_event_t    uart_recvTaskQueue[TASK_LENGHT];
os_event_t    all_recvTaskQueue[TASK_LENGHT];

void ICACHE_FLASH_ATTR uart_recvTask(os_event_t *events);


void ICACHE_FLASH_ATTR all_recvTask(os_event_t *events);
