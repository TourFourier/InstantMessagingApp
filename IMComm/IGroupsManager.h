#pragma once
class IGroupsManager
{
public:
	IGroupsManager();
	virtual ~IGroupsManager();

	virtual void CreateUpdateGroup(TGroup& group) = 0;
	virtual const TGroup& FindGroup(GUID guid) = 0;
	virtual void DeleteGroup(TGroup& group) = 0;
};

