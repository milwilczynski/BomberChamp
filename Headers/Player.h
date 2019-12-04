#pragma once
#include "Main.h"
#include "Definitions.h"
class GameClass;

class Player
{
public:
	inline Player()
		: apk_rotation(0),
		apk_destroyed(false)
	{
		
	}

	inline virtual ~Player() {}

	inline virtual void SetLocation(const grim::Vector2 &loc)
	{
		apk_location = loc;
	}

	inline virtual void SetRotation(const float &rot)
	{
		apk_rotation = rot;
	}

	inline virtual void Move(const grim::Vector2 &move)
	{
		this->SetLocation(apk_location + move);
	}

	inline virtual void Rotate(const float &move)
	{
		this->SetRotation(apk_rotation + move);
	}

	inline void Destroy()
	{
		apk_destroyed = true;
	}

	inline virtual void Update(const float &time)
	{
		
	}

	virtual void Draw() = 0;

	

	inline grim::Vector2 GetLocation() const
	{
		return apk_location;	
	}

	inline float GetRotation() const
	{
		return apk_rotation;
	}

	inline bool IsDestroyed() const
	{
		return apk_destroyed;
	}
protected:
	grim::Vector2 apk_location;
	float apk_rotation;
	bool apk_destroyed;
};