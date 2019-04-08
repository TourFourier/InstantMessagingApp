#include "stdafx.h"
#include "afxsock.h"
#include "constants.h"
#include "IMessage.h"
#include "IMessageFactory.h"
#include "ICommunication.h"
#include "CCommunication_TCP.h"


CCommunication_TCP::CCommunication_TCP(IMessageFactory* pMessageFactory) :ICommunication(pMessageFactory) 
{
}


CCommunication_TCP::~CCommunication_TCP()
{
}

void CCommunication_TCP::OnMessageReceived(char* pBuffer, int nLength)
{
	// Notice this function is called on seprate thread then the main thread.
	// 0. Get message type from buffer (notice that in all messsages, first two
	//    members are the GUID and then type (see IMessage class) ie. this will move pointer over to point at type variable in buffer array. 
	//This explains the folowing line:
	EMessageType type = *(EMessageType*)(pBuffer + sizeof(GUID));//move pointer over till reach type;cast to pointer to enum;get content of pointer
	// 1. Create Message object by the type.
	IMessage* pMessage = m_pMessageFactory->CreateMessage(type); // 'pMessage' : Message obj
	pMessage->FromBuffer(pBuffer, nLength);// /Calling mssg obj.'s FromBuffer method which Fills the message obj.'s fields 
	// 2. Call callback
	void* callbacks = m_hashCallbacks[type]; // 'callbacks' : specific callback func
	(*callbacks)(pMessage);
	/*for (int i = 0; i < callbacks.GetSize(); i++)
	{
		void* pfnCallback = callbacks[i];
		(*pfnCallback)(pMessage);// Calling the callback func and passing in message obj. as an argument; the callbacks simply push the message into a queue to be handled by main thread
	}*/
}
// <<<<<<<<<<<Implement ICommunication functions.
//virtual bool Connect(CString sConnectionDetails) = 0;
//virtual bool Disconnect() = 0;
//virtual bool SendMessage(IMessage* pMessage) = 0;