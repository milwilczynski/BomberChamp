#pragma once
#include "SetPlayers.h"

enum BackgroundType
{
	TGround = 0,
	TExpload = 1,
	TSolid = 2
};

class Background
	: public SetPlayers
{
public:
	explicit Background(BackgroundType type);

	virtual void SetLocation(const grim::Vector2& loc) override;
	virtual void Draw() override;


	inline BackgroundType GetType() const
	{
		return apk_type;
	}

private:
	Sprite apk_sprite;
	BackgroundType apk_type;
};

class BackgroundController
	: public SetPlayersControllers
{
public:
	explicit BackgroundController();


	virtual void Update(const float& time) override;
private:

};
