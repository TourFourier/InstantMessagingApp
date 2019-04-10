#pragma once


class  IMessage
{
protected:
	int m_guid;
	int m_nMessageType;

public:
	IMessage();
	IMessage(int guid, int messageType);
	virtual ~IMessage();

	 static const int SIZE_GUID = sizeof(int);
	 static const int SIZE_INT = sizeof(int);
	const int GetGuid() { return m_guid; }
	virtual int GetType() { return m_nMessageType; }
	virtual int Size() = 0;
	virtual bool ToBuffer(char* cBuffer)=0;
	virtual bool FromBuffer(char* pBuffer)=0;
};

