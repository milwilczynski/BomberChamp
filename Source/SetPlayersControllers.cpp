#include "../Headers/SetPlayers.h"

SetPlayersControllers::SetPlayersControllers()
	:apk_owner(nullptr)
{
	
}

SetPlayersControllers::~SetPlayersControllers()
{
	
}

bool SetPlayersControllers::SetOwner(SetPlayers *owner)
{
	if(!apk_owner)
	{
		apk_owner = owner;
		return true;
	}
	return false;
}
