#include "stdafx.h"
#include <rpc.h>
#include "structsAndConstants.h"
#include "IMessage.h"
#include "MTextMessage.h"


MTextMessage::MTextMessage()
{
}

MTextMessage::MTextMessage(GUID guid, int messageType, TTextMessage& message) : IMessage(guid, messageType)
{
	m_msgText.m_sText = message.m_sText;
	m_msgText.m_userDestination = message.m_userDestination;
	m_msgText.m_groupDestination = message.m_groupDestination;
}


MTextMessage::~MTextMessage()
{
}


int MTextMessage::Size()
{
	int size;

	size += IMessage::SIZE_GUID;// 16
	size += IMessage::SIZE_INT;// 4
	size += sizeof(m_msgText);// Variant

	return size;
}

bool MTextMessage::ToBuffer()
{
	char* cBuffer = new char[this->Size()];
	*(GUID*)cBuffer = m_guid;
	*(int*)(cBuffer + IMessage::SIZE_GUID) = (int)EMessageType::TEXT_MESSAGE;
	*(TTextMessage*)(cBuffer + IMessage::SIZE_GUID + IMessage::SIZE_INT) = m_msgText;

	return cBuffer;
}

bool MTextMessage::FromBuffer(char* pBuffer, int nLength)
{
	m_guid = *(GUID*)pBuffer;
	m_nMessageType = *(int*)(pBuffer + IMessage::SIZE_GUID);
	m_msgText = *(TTextMessage*)(pBuffer + IMessage::SIZE_GUID + IMessage::SIZE_INT);
	// Note: the size of the text struct will differ depends on the text message and recipients...
	//...therefor must adjust to read that much of buffer or have a sync word/#                     
}
