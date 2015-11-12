
#include "commande.h"

uint8 DataPos = 0;
void ProcessChar(uint8 Dchar)
{
	switch(Status)
	{
		case E_ID:
			Message.Id = Dchar;
			Status = E_SIZE;
			DataPos = 0;
			break;
		case E_SIZE:				
			Message.Size = Dchar;
			Status = E_DATA;
			break;
		case E_DATA:
			Message.Data[DataPos] = Dchar;
                        DataPos ++;
			if( DataPos & Message.Size)
			{
				break;
			}
		case E_END:
			ProcessMess();
			Status = E_ID;
		default:
			break;
	}
}


ProcessMess()
{
	switch(Message.Id)
	{
		case CM_MODE:
		case CM_STASSID:
	        case CM_STAPWD :
		case CM_STAEN :
		case CM_TCPEN : 
		case CM_UDPEN:
		case CM_UDPPORT:
		case CM_TCPPORT:
		default:
			break;

	}
}

