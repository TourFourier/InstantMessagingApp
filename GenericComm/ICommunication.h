#pragma once


class ICommunication
{
public:
	ICommunication();
	~ICommunication();

protected:
	std::map<EMessageType, CList<void*>> m_hashCallbacks;
	IMessageFactory* m_pMessageFactory;
public:
	virtual bool Connect(CString sConnectionDetails) = 0;
	virtual bool Disconnect() = 0;

	void RegisterCallback(EMessageType eMessageType, void* pfnCallback)
	{
		m_hashCallbacks.insert(eMessageType, pfnCallback);
	}

	void RemoveCallback(EMessageType eMessageType, void* pfnCallback)
	{
		m_hashCallbacks.erase(eMessageType, pfnCallback);
	}

	virtual bool SendMessage(IMessage* pMessage) = 0;

	//Constructor
	ICommunication(IMessageFactory* pMessageFactory)
	{
		m_pMessageFactory = pMessageFactory;
	}
};

