#ifndef COMMANDE_H
#define COMMANDE_H

#include "os_type.h"
uint8 BufferInput[128];


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
Mess Message;
#define DATA_SIZE_MAX 0xFF

//CMD Data 
#define DATA	 0x00 //Donnees Transmisent avec une taille MAX de 256

// CMD Definit dans le mode de la puce (STATION OU/ET AP) 
#define CM_MODE	 0x01

//Données possibles
#define DT_AP	 0x00
#define DT_STA	 0x01
#define DT_STAAP	 0x02

///CMD Pour le mode STATION
#define CM_STASSID 0x02 
#define CM_STAPWD  0x03
#define CM_STAEN	0x04

//CMD pour le mode AP
#define CM_APSSID 0x06 
#define CM_APPWD  0x07
#define CM_APEN   0x08


//Defenition des port TCP ou UDP
// Acitvation du serveur TCP et selection du port TCP
#define CM_TCPEN 	0x09
#define CM_TCPPORT	0x0A  //Donnée du port sur 2 octets

// Acitvation du serveur UDP et selection du port UDP
#define CM_UDPEN 	0x0B
#define CM_UDPPORT	0x0C  //Donnée du port sur 2 octets


#define CM_RST		0xFF


void ProcessChar(uint8 Dchar);

#endif

