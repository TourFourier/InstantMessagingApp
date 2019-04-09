#pragma once
class MAcknowledgeMessage :
	public IMessage
{
private:
	GUID m_guidOriginalMessage;
public:
	MAcknowledgeMessage();
	// Consider also calling IMessage's non-default constructor and passing it arguments, like i did in MTextMessage.h
	MAcknowledgeMessage(GUID guidOriginalMessage);
   ~MAcknowledgeMessage();

   const GUID GetOriginalMessageGUID() { return m_guidOriginalMessage; }

   virtual int Size() = 0;
   virtual bool ToBuffer();
   virtual bool FromBuffer(char* pBuffer, int nLength);
};

