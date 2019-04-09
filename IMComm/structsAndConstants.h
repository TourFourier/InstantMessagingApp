#pragma once

#include <atlstr.h>
#include <rpc.h>
#include <vector>



// Represents one user
struct TUser 
{
	GUID guid; // "Global unique id"  a unique id that identifies this user globally
	CString sName;
	CString sPhoneNumber;
};


// Represents a list of users
struct TGroup 
{
	GUID guid;
	// Simple implementation: For every change in group we send all numbers.
	std::vector<TUser> nlistUsers;
};


// Represents one message
struct TTextMessage 
{
	CString m_sText; // message to send
	TUser m_userDestination; // to which user we are sending, in event we are sending to individual user/s
	TGroup m_groupDestination; // to which group, in event where sending to whole group 
};



enum EMessageType
{
	TEXT_MESSAGE = 0,
	CREATE_UPDATE_GROUP = 1,
	ACKNOWLEDGE = 2
};


