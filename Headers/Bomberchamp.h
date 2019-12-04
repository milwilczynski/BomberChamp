#pragma once

#include "SetPlayers.h"

enum Direction
{
	DLeft = 0,
	DRight = 1,
	DUp = 2,
	DDown = 3
};

class Bomberchamp
	: public SetPlayers
{
public:
	explicit Bomberchamp(bool firstPlayer);
	virtual void SetLocation(const grim::Vector2& loc) override;
	virtual void Draw() override;
	bool IsExplosionColliding();

	void SetDirection(Direction direction, bool firstPlayer);

	bool IsColliding();

	inline Direction GetDirection() const
	{
		return apk_direction;
	}

private:
	Sprite apk_sprite;
	Direction apk_direction;
};

class BomberChampController
	: public SetPlayersControllers
{
public:
	explicit BomberChampController(bool firstPlayer);


	virtual void Update(const float& time) override;
private:
	bool MoveLeft(const float &tim);
	bool MoveRight(const float &tim);
	bool MoveUp(const float &tim);
	bool MoveDown(const float &tim);

	bool apk_isPressed;
	const float apk_moveSpeed;
	float apk_bombTime;
	bool apk_firstPlayer;
	const float apk_bombInterval;
};
