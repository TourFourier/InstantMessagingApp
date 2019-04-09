#include "stdafx.h"
#include "ICommunication.h"
#include "CCommunication_TCP.h"
#include "CSafeMessageQueue.h"
#include "structsAndConstants.h"
#include <rpc.h>
#include "IMessage.h"
#include "MTextMessage.h"
#include "MGroupCreateUpdate.h"
#include "MAcknowledgeMessage.h"
#include "CMessageFactory_WhatsApp.h"

#include "CCommunication_Client.h"


CCommunication_Client::CCommunication_Client()
{
}


CCommunication_Client::~CCommunication_Client()
{
}
