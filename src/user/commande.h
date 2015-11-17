#ifndef COMMANDE_H
#define COMMANDE_H

#include "os_type.h"
uint8 BufferInput[128];
typedef struct configuration
{
	uint8 StaSsid[64];
	uint8 StaPwd[64];
	uint8 APSsid[64];
	uint8 APPwd[64];
	uint16 TCPPort;
 	uint16 UDPPort;
	uint8 USE;
} Configuration;

typedef enum messstate
{
	E_ID 		= 0,
	E_SIZE		= 1,
	E_DATA		= 2,
	E_END		= 4,
	E_MAX_STATE 	= 5
} MessState;

MessState Status;

typedef struct mess
{
	uint8 Id;
	uint8 Size;
	uint8 Data[256];
}Mess;
Mess MessageUart;
#define DATA_SIZE_MAX 0xFF

//CMD Data 
#define CMD_DATA	 0x00 //Donnees Transmisent avec une taille MAX de 256

// CMD Definit dans le mode de la puce (STATION OU/ET AP) 
#define CM_MODE	 0x01

//Données possibles
#define DT_AP	 	0x00
#define DT_STA	 	0x01
#define DT_STAAP	0x02

///CMD Pour le mode STATION
#define CM_STASSID 	0x10 
#define CM_STAPWD  	0x11
#define CM_STADEVNAME	0x12
#define CM_STAEN   	0x13

//CMD pour le mode AP
#define CM_APSSID 	0x20
#define CM_APPWD  	0x21
#define CM_APEN   	0x22


//Defenition des port TCP ou UDP
// Acitvation du serveur TCP et selection du port TCP
#define CM_TCPEN 	0x30
#define CM_TCPPORT	0x31  //Donnée du port sur 2 octets

// Acitvation du serveur UDP et selection du port UDP
#define CM_UDPEN 	0x40
#define CM_UDPPORT	0x41  //Donnée du port sur 2 octets


#define CM_RST		0xFF


void ProcessChar(uint8 Dchar,Mess *pmess);

void ProcessMess(Mess *pmess);

#endif

