#pragma once


class  IMessage
{
protected:
	GUID m_guid;
	int m_nMessageType;
public:
	IMessage();
	virtual ~IMessage();

	const GUID& GetGuid() { return m_guid; }
	virtual EMessageType GetType() { return (EMessageType)m_nMessageType; }
	virtual int Size() = 0;
	virtual bool ToBuffer(char* pBuffer, int nLength);
	virtual bool FromBuffer(char* pBuffer, int nLength);
};

