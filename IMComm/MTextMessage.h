#pragma once

class MTextMessage :
	public IMessage
{
private:
		TTextMessage m_msgText;  
public:
	MTextMessage();
	MTextMessage(GUID guid, int messageType, TTextMessage& message) : IMessage(guid, messageType) {}
   ~MTextMessage();
	const TTextMessage& GetTextMessage() { return m_msgText; }

	// Returns absolute size of message object in bytes
	virtual int Size();
	// Logic for extracting from a buffer
	virtual bool ToBuffer();
	// Logic for creating a buffer
	virtual bool FromBuffer(char* pBuffer, int nLength);	
};


