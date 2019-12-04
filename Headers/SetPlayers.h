#pragma once
#include "Player.h"
class SetPlayersControllers;

class SetPlayers
	:public Player
{
public:
	explicit SetPlayers(SetPlayersControllers *controller);

	virtual ~SetPlayers() override;

	void ResetController(SetPlayersControllers *controller);

	virtual void Update(const float &time) override;


protected:
	SetPlayersControllers *apk_controller;

};

class SetPlayersControllers
{
public:
	SetPlayersControllers();

	virtual ~SetPlayersControllers();

	virtual void Update(const float &time) = 0;

	inline bool IsInUse() const
	{
		return apk_owner != nullptr;
	}


	friend class SetPlayers;

private:
	bool SetOwner(SetPlayers *owner);

protected:
	SetPlayers* apk_owner;

};