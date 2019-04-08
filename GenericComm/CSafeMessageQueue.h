#pragma once


class  CSafeMessageQueue
{
	CRITICAL_SECTION m_cs;
	std::queue<IMessage&> m_qMessageQueue;
public:
	CSafeMessageQueue();
	~CSafeMessageQueue();

	void Push(IMessage& message);
	IMessage& Pop();
};

