#include "stdafx.h"
#include "constants.h"
#include "IMessage.h"
#include <rpc.h>


IMessage::IMessage()
{
	m_guid = new GUID;
}
IMessage::IMessage(GUID* guid, int messageType)
{
	m_guid = guid;
	m_nMessageType = messageType;
}


IMessage::~IMessage()
{
}
