#pragma once
class IMessageFactory
{
public:
	IMessageFactory();
	~IMessageFactory();

	virtual IMessage* CreateMessage(int type) = 0;
};

