#pragma once
class CCommunication_Client :
	public CCommunication_TCP
{
	/*protected:
	CHashTable<EMessageType, CList<void*>> m_hashCallbacks;
	IMessageFactory* m_pMessageFactory;
public:
	
	
	void RegisterCallback(EMessageType eMessageType, void* pfnCallback)
	{
		m_hashCallbacks.Insert(eMessageType, pfnCallback);
	}
	
	void RemoveCallback(EMessageType eMessageType, void* pfnCallback)
	{
		m_hashCallbacks.Remove(eMessageType, pfnCallback);
	}	
	
	virtual bool SendMessage(IMessage* pMessage) = 0;
	
	//Constructor
	ICommunication(IMessageFactory* pMessageFactory)
	{
		m_pMessageFactory = pMessageFactory;
	}
};


class CCommunication_TCP : public ICommunication
{
private:
	CSocket m_socket;
public:
	CCommunication_TCP(IMessageFactory* pMessageFactory) :ICommunication(pMessageFactory) {}

	// Implement ICommunication functions.

	// This function is to be called by network card. 1
	// It looks for the synch-word, then build up the buffer by the length field, 
	// and eventually calls correct handler by the message type, delivering it the message buffer:
	void OnMessageReceived(BYTE* pBuffer, int nLength)
	{
		// Notice this function is called on seprate thread then the main thread.
		// 0. Get message type from buffer (notice that in all messsages, first two
		//    members are the GUID and then type (see IMessage class) ie. this will move pointer over to point at type variable in buffer array. 
		//This explains the folowing line:
		EMessageType type = *(EMessageType*)(pBuffer + sizeof(GUID));//move pointer over till reach type;cast to pointer to enum;get content of pointer
		// 1. Create Message object by the type.
		IMessage* pMessage = m_pMessageFactory->CreateMessage(type); // 'pMessage' : Message obj
		pMessage->FromBuffer(pBuffer, nLength);// /Calling mssg obj.'s FromBuffer method which Fills the message obj.'s fields using the inputed buffer
		// 2. Call callback
		CList<void*> callbacks = m_hashCallbacks[type]; // 'callbacks' : specific callback func
		for (int i = 0; i < callbacks.GetSize(); i++)
		{
			void* pfnCallback = callbacks[i];
			(*pfnCallback)(pMessage);// Calling the callback func and passing in message obj. as an argument; the callbacks simply push the message into a queue to be handled by main thread
		}
	}
};*/
public:
	CCommunication_Client();
	~CCommunication_Client();
	// Implement these; inherited from ICommunication interface
	virtual bool Connect(CString sConnectionDetails);
	virtual bool Disconnect();

private:
	static CCommunication_Client* s_pCCommunicationClient = NULL; // SINGLETON; 

	// Creating queues of objects (text message, acknowledge and group) for INCOMING messages
	CSafeMessageQueue m_queueTextMessages;
	CSafeMessageQueue m_queueGroupCreateUpdateMessages;
	CSafeMessageQueue m_queueAcknowledge;

	// This function fills a hash table(declared in  'IComm', the sabba)with message type and corresponding callback function    [5]*****************************************************************
	void Register()
	{
		//since RegisterCallback is an inherited method, using "this->" makes it clear that this method exists in this object(even though it is technically unnecessary)
		this->RegisterCallback(EMessageType::TEXT_MESSAGE, OnTextMessageReceived);
		this->RegisterCallback(EMessageType::CREATE_UPDATE_GROUP, OnGroupCreateUpdateReceived);
		this->RegisterCallback(EMessageType::ACKNOWLEDGE, OnAcknowledgeReceived);
	}

	// These are the callback functions ie. for when a new message or ack or group  occur
	void OnTextMessageReceived(MTextMessage* pMessage)
	{
		m_queueTextMessages.Push(pMessage);
	}
	void OnGroupCreateUpdateReceived(MGroupCreateUpdate* pMessage)
	{
		m_queueGroupCreateUpdateMessages.Push(pMessage);
	}
	void OnAcknowledgeReceived(MAcknowledgeMessage* pMessage)
	{
		m_queueAcknowledge.Push(pMessage);
	}

public:
	static CCommunication_Client* GetInstance()  // SINGLETON               [1] *****************************************************************************************************************
	{
		if (s_pCCommunicationClient == NULL)
		{
			s_pCCommunicationClient = new CCommunication_Client;
		}
		return s_pCCommunicationClient;
	}

	//Constructor; constructor of CCommunication_Client calls constructor of 'abba' ie. CCommunication_TCP, and passes in as an argument to the abba constructor a CMessageFactory_WhatsApp object
CCommunication_Client(): CCommunication_TCP(new CMessageFactory_WhatsApp)     //[2]***************************************************************************************
{
	Register();
}

		// Getters for the queues 
					   const CSafeMessageQueue& GetTextMessagesQueue() { return m_queueTextMessages; }
					   const CSafeMessageQueue& GetGroupCreateUpdateMessagesQueue() { return m_queueGroupCreateUpdateMessages; }
					   const CSafeMessageQueue& GetAcknowledgeMessagesQueue() { return m_queueAcknowledge; }

					   // methods for OUTGOING messages; MUST IMPLEMENT
					   void SendTextMessage(const TTextMessage& text); // argument: struct (3) // IMPLEMENTATION WILL INC CREATING A TEXT MSSG OBJ(using factory) AND CALLING TObUFFER METHOD
					   void SendGroupCreateUpdate(const TGroup& group); // argument: struct (2)
					   void SendAck(const TTextMessage& textMessageToAck); // argument: struct (3)
};

