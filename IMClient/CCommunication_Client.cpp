#include "stdafx.h"
#include "CMefathimSocket.h"
#include "ICommunication.h"
#include "CCommunication_TCP.h"
#include "CSafeMessageQueue.h"
#include "structsAndConstants.h"
#include <rpc.h>
#include "IMessage.h"
#include "MTextMessage.h"
#include "MGroupCreateUpdate.h"
#include "MAcknowledgeMessage.h"
#include "CMessageFactory_WhatsApp.h"

#include "CCommunication_Client.h"


//CCommunication_Client::CCommunication_Client(){}


CCommunication_Client::~CCommunication_Client()
{
}

void CCommunication_Client::OnTextMessageReceived(MTextMessage* pMessage)
{
	m_queueTextMessages.Push(pMessage);
}

void CCommunication_Client::OnGroupCreateUpdateReceived(MGroupCreateUpdate* pMessage)
{
	m_queueGroupCreateUpdateMessages.Push(pMessage);
}

void CCommunication_Client::OnAcknowledgeReceived(MAcknowledgeMessage* pMessage)
{
	m_queueAcknowledge.Push(pMessage);

}

void CCommunication_Client::Register()
{
	//since RegisterCallback is an inherited method, using "this->" makes it clear that this method exists in this object(even though it is technically unnecessary)
	this->RegisterCallback(EMessageType::TEXT_MESSAGE, OnTextMessageReceived);
	this->RegisterCallback(EMessageType::CREATE_UPDATE_GROUP, OnGroupCreateUpdateReceived);
	this->RegisterCallback(EMessageType::ACKNOWLEDGE, OnAcknowledgeReceived);
}

// IMPLEMENTATION WILL INC CREATING A TEXT MSSG OBJ(using factory) AND CALLING TObUFFER AND THEN SENDMESSAGE()
void CCommunication_Client::SendTextMessage(const TTextMessage& text) 
{
	MTextMessage* pMTextmessage = new MTextmessage(text);
	char* cBuffer = new char[pMTextmessage->Size()];
	pMTextmessage->ToBuffer(cBuffer);


};
void CCommunication_Client::SendGroupCreateUpdate(const TGroup& group) {};
void CCommunication_Client::SendAck(const TTextMessage& textMessageToAck) {};