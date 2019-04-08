#pragma once

class CCommunication_TCP :
	public ICommunication
{
private:
	CSocket m_socket;
public:
	CCommunication_TCP(IMessageFactory* pMessageFactory) :ICommunication(pMessageFactory) {}
	~CCommunication_TCP();


	// <<<<<<<<<<<Implement ICommunication functions.
	virtual bool Connect(CString sConnectionDetails) = 0;
	virtual bool Disconnect() = 0;
	virtual bool SendMessage(IMessage* pMessage) = 0;


	// This function is to be called by network card. 
	// It looks for the synch-word, then build up the buffer by the length field, 
	// and eventually calls correct handler by the message type, delivering it the message buffer:
	void OnMessageReceived(char* pBuffer, int nLength);

};

