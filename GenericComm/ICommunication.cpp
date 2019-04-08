#include "stdafx.h"
#include <atlstr.h>
#include <map>
#include <vector>
#include "constants.h"
#include "IMessage.h"
#include "IMessageFactory.h"
#include "ICommunication.h"


ICommunication::ICommunication(IMessageFactory* pMessageFactory)
{
	m_pMessageFactory = pMessageFactory;
}


ICommunication::~ICommunication()
{
}

void ICommunication::RegisterCallback(EMessageType eMessageType, void* pfnCallback)
{
	m_hashCallbacks.insert(std::pair<EMessageType, void*>(eMessageType, pfnCallback));
	//m_hashCallbacks[eMessageType] = pfnCallback;
}

void ICommunication::RemoveCallback(EMessageType eMessageType, void* pfnCallback)
{
	m_hashCallbacks.erase(eMessageType);
}