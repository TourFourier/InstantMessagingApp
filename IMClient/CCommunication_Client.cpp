#include "stdafx.h"
#include "afxsock.h"
#include <rpc.h>
#include "../GenericCommunication/CMefathimSocket.h"
#include "../GenericCommunication/ICommunication.h"
#include "../GenericCommunication/CCommunication_TCP.h"
#include "../GenericCommunication/CSafeMessageQueue.h"
#include "../IMComm/structsAndConstants.h"
#include "../GenericCommunication/IMessage.h"
#include "../IMComm/MTextMessage.h"
#include "../IMComm/MGroupCreateUpdate.h"
#include "../IMComm/MAcknowledgeMessage.h"
#include "../IMComm/CMessageFactory_WhatsApp.h"

#include "CCommunication_Client.h"


//CCommunication_Client::CCommunication_Client(){}
CCommunication_Client* CCommunication_Client::s_pCCommunicationClient = NULL;

CCommunication_Client::~CCommunication_Client()
{
}

void CCommunication_Client::OnTextMessageReceived(MTextMessage* pMessage)
{
	CCommunication_Client::GetInstance()->m_queueTextMessages.Push(pMessage);
}

void CCommunication_Client::OnGroupCreateUpdateReceived(MGroupCreateUpdate* pMessage)
{
	CCommunication_Client::GetInstance()->m_queueGroupCreateUpdateMessages.Push(pMessage);
}

void CCommunication_Client::OnAcknowledgeReceived(MAcknowledgeMessage* pMessage)
{
	CCommunication_Client::GetInstance()->m_queueAcknowledge.Push(pMessage);
}

void CCommunication_Client::Register()
{
	//since RegisterCallback is an inherited method, using "this->" makes it clear that this method exists in this object(even though it is technically unnecessary)
	this->RegisterCallback(EMessageType::TEXT_MESSAGE, CCommunication_Client::GetInstance()->OnTextMessageReceived);
	this->RegisterCallback(EMessageType::CREATE_UPDATE_GROUP, CCommunication_Client::GetInstance()->OnGroupCreateUpdateReceived);
	this->RegisterCallback(EMessageType::ACKNOWLEDGE, CCommunication_Client::GetInstance()->OnAcknowledgeReceived);
}

// IMPLEMENTATION WILL INC CREATING A TEXT MSSG OBJ(using factory) AND CALLING TObUFFER AND THEN SENDMESSAGE()
void CCommunication_Client::SendTextMessage(const TTextMessage& text) 
{
	MTextMessage* pMTextmessage = new MTextMessage(1,text);
	char* cBuffer = new char[pMTextmessage->Size()];
	pMTextmessage->ToBuffer(cBuffer);
	m_socket.Send(cBuffer, sizeof(cBuffer));
};
void CCommunication_Client::SendGroupCreateUpdate(const TGroup& group) {};
void CCommunication_Client::SendAck(const TTextMessage& textMessageToAck) {};