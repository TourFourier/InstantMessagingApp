#pragma once
#include <map>


class ICommunication
{
protected:
	std::map<EMessageType, void*> m_hashCallbacks; // TODO: Change value to vector of function pointers
	IMessageFactory* m_pMessageFactory;
public:
	virtual bool Connect(CString sConnectionDetails) = 0;
	virtual bool Disconnect() = 0;

	void RegisterCallback(EMessageType eMessageType, void* pfnCallback);

	void RemoveCallback(EMessageType eMessageType, void* pfnCallback);

	virtual bool SendMessage(IMessage* pMessage) = 0;

	//Constructor
	ICommunication(IMessageFactory* pMessageFactory);

	~ICommunication();

};


