#pragma once
#include "SetPlayers.h"




class Bomb
	: public SetPlayers
{
public:
	Bomb();
	virtual void SetLocation(const grim::Vector2& loc) override;
	virtual void Draw() override;


private:
	Sprite apk_sprite;
};

class BombController
	: public SetPlayersControllers
{
public:
	BombController();


	virtual void Update(const float& time) override;
private:
	float apk_explode_time;
};

class Explosion
	: public SetPlayers
{
public:
	Explosion();

	virtual void SetLocation(const grim::Vector2& loc) override;
	virtual void Draw() override;


private:
	Sprite apk_sprite;
};

class ExplosionController
	: public SetPlayersControllers
{
public:
	ExplosionController();

	virtual void Update(const float& time) override;
private:
	float apk_lifeTime;
};
