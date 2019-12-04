#include "../Headers/SetPlayers.h"

SetPlayers::SetPlayers(SetPlayersControllers *controller)
	:apk_controller(nullptr)
{
	if(controller && controller->SetOwner(this))
	{
		apk_controller = controller;
	}
}


SetPlayers::~SetPlayers()
{
	if (apk_controller)
		delete apk_controller;
}

void SetPlayers::ResetController(SetPlayersControllers *controller)
{
	if (controller != apk_controller)
	{
		if (apk_controller)
			delete apk_controller;

		if (controller && controller->SetOwner(this))
		{
			apk_controller = controller;
		}
		else
			apk_controller = nullptr;
	}
}

void SetPlayers::Update(const float &time)
{
	if (apk_controller) 
	{
		apk_controller->Update(time);
	}
}