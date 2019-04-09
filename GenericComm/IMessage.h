#pragma once


class  IMessage
{
private:
	 static const int SIZE_GUID = sizeof(GUID);
	 static const int SIZE_INT = sizeof(int);

protected:
	GUID* m_guid;
	int m_nMessageType;

public:
	IMessage();
	IMessage(GUID *guid, int messageType);
	virtual ~IMessage();

	const GUID* GetGuid() { return m_guid; }
	virtual EMessageType GetType() { return (EMessageType)m_nMessageType; }
	virtual int Size() = 0;
	virtual bool ToBuffer(char* pBuffer, int nLength);
	virtual bool FromBuffer(char* pBuffer, int nLength);
};

