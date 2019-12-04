#pragma once
#include "../Headers/Bomb.h"
#include "../Headers/Game.h"
#include "../Headers/Background.h"
#include "../Headers/Bomberchamp.h"


Bomb::Bomb()
	:SetPlayers(new BombController)
{
	apk_sprite.setTexture(*(TextureClass::CheckTexture("Bomb")));
	apk_sprite.setScale(40.f/48.f, 40.f/48.f);
}

void Bomb::SetLocation(const grim::Vector2& loc)
{
	SetPlayers::SetLocation(loc);
	apk_sprite.setPosition(loc.x, loc.y);
}


void Bomb::Draw()
{
	GameClass::Instance().GetWindow().draw(apk_sprite);
}

BombController::BombController()
	:apk_explode_time(1.5f)
{
	
}

void BombController::Update(const float& time)
{

	apk_explode_time -= time;
	if(apk_explode_time <= 0 )
	{
		apk_owner->Destroy();

		{
			auto *explosion = new Explosion();
			explosion->SetLocation(apk_owner->GetLocation() + grim::Vector2f(0, 0));
			GameClass::Instance().GetCurrentLevel()->Add(explosion);
		}
		{
			auto *explosion = new Explosion();
			explosion->SetLocation(apk_owner->GetLocation() + grim::Vector2(0, -40));
			GameClass::Instance().GetCurrentLevel()->Add(explosion);
		}
		{
			auto *explosion = new Explosion();
			explosion->SetLocation(apk_owner->GetLocation() + grim::Vector2(0,40));
			GameClass::Instance().GetCurrentLevel()->Add(explosion);
		}
		{
			auto *explosion = new Explosion();
			explosion->SetLocation(apk_owner->GetLocation() + grim::Vector2(-40, 0));
			GameClass::Instance().GetCurrentLevel()->Add(explosion);
		}
		{
			auto *explosion = new Explosion();
			explosion->SetLocation(apk_owner->GetLocation() + grim::Vector2(40, 0));
			GameClass::Instance().GetCurrentLevel()->Add(explosion);
		}
	}
}

// Eksplocja

Explosion::Explosion()
	:SetPlayers(new ExplosionController)
{
	apk_sprite.setTexture(*(TextureClass::CheckTexture("Expload")));
	apk_sprite.setScale(40.f / 48.f, 40.f / 48.f);

}

void Explosion::SetLocation(const grim::Vector2& loc)
{

	SetPlayers::SetLocation(loc);
	apk_sprite.setPosition(loc.x, loc.y);
	
	bool zabited = false;
	FloatRect Collider(sf::Vector2f(loc.x, loc.y), sf::Vector2f(40, 40));

	auto bombers = GameClass::Instance().GetCurrentLevel()->GetPlayerBomberchamps();
	for (auto *bomber : bombers)
	{
		auto *b = dynamic_cast<Bomberchamp*>(bomber);
		if (b->IsExplosionColliding()) {
			b->Destroy();
			zabited = true;
		}
		if (zabited)
		{
			b->Destroy();
			GameClass::Instance().SetPause();
		}
	}

	auto players = GameClass::Instance().GetCurrentLevel()->GetPlayersAtLocation(loc);
	for(auto *player : players)
	{
		auto *tile = dynamic_cast<Background*>(player);
		
		if ((tile && tile->GetType() == BackgroundType::TExpload))
		{
			player->Destroy();
		}
	}

	
}

void Explosion::Draw()
{
	GameClass::Instance().GetWindow().draw(apk_sprite);
}

ExplosionController::ExplosionController()
	:apk_lifeTime(0.7f)
{

}

void ExplosionController::Update(const float& time)
{
	apk_lifeTime -= time;
	if (apk_lifeTime <= 0)
	{
		apk_owner->Destroy();
	}
}
