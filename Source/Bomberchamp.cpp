#include "../Headers/Bomberchamp.h"
#include "../Headers/Game.h"
#include "../Headers/TextureClass.h"
#include "../Headers/Bomb.h"

Bomberchamp::Bomberchamp(bool firstPlayer)
	:SetPlayers(new BomberChampController(firstPlayer))
{
	if (firstPlayer) {
		apk_sprite.setTexture(*(TextureClass::CheckTexture("Bomberchamp_F")));
		apk_sprite.setOrigin(32, 91);
		apk_sprite.setScale(2.f / 3.f, 2.f / 3.f);
	}
	else {
		apk_sprite.setTexture(*(TextureClass::CheckTexture("Bomberchamp2_F")));
		apk_sprite.setOrigin(32, 32);
		apk_sprite.setScale(2.f / 3.f, 2.f / 3.f);
	}

}

void Bomberchamp::Draw()
{
	GameClass::Instance().GetWindow().draw(apk_sprite);
}
bool Bomberchamp::IsExplosionColliding() {

	FloatRect collider(sf::Vector2f(apk_location.x-15, apk_location.y-10), sf::Vector2f(30, 30));

	auto explosions = GameClass::Instance().GetCurrentLevel()->ExplosionCollider();

	for (auto *exp : explosions)
	{
		grim::Vector2 tileLoc = exp->GetLocation();
		FloatRect tileCollider(sf::Vector2f(tileLoc.x, tileLoc.y), sf::Vector2f(40, 40));
		cout << "x: " << tileLoc.x << " y: " << tileLoc.y << endl;

		
	    
		if (tileCollider.intersects(collider))
		{
			return true;
		}
	}
	return false;
}

bool Bomberchamp::IsColliding()
{
	FloatRect collider(sf::Vector2f(apk_location.x - 15, apk_location.y - 10), sf::Vector2f(30,30));

	auto tiles = GameClass::Instance().GetCurrentLevel()->GetAllColliders();

	for(auto *tile : tiles)
	{
		grim::Vector2 tileLoc = tile->GetLocation();
		FloatRect tileCollider(sf::Vector2f(tileLoc.x, tileLoc.y), sf::Vector2f(40, 40));
		if(tileCollider.intersects(collider))
		{
			return true;
		}
	}
	return false;
}

void Bomberchamp::SetDirection(Direction direction, bool firstPlayer)
{
	if(apk_direction != direction)
	{

		/* set.scale -1, 1 ustawia grafike na odwrot niz side right, prosta sztuczka na odbicie tekstury :)
		 * B - Back, S - Side, F - Front		 */
		apk_direction = direction;
		if(apk_direction == DUp)
		{
			if (firstPlayer)
			{
				apk_sprite.setTexture(*(TextureClass::CheckTexture("Bomberchamp_B")));
			}
			else
			{
				apk_sprite.setTexture(*(TextureClass::CheckTexture("Bomberchamp2_B")));
			}
			apk_sprite.setScale(2.f / 3.f, 2.f / 3.f);
		}

		if(apk_direction == DDown)
		{
			if (firstPlayer)
			{
				apk_sprite.setTexture(*(TextureClass::CheckTexture("Bomberchamp_F")));
			}
			else
			{
				apk_sprite.setTexture(*(TextureClass::CheckTexture("Bomberchamp2_F")));
			}
			apk_sprite.setScale(2.f / 3.f, 2.f / 3.f);
		}

		if(apk_direction == DRight)
		{
			if (firstPlayer)
			{
				apk_sprite.setTexture(*(TextureClass::CheckTexture("Bomberchamp_S")));
			}
			else
			{
				apk_sprite.setTexture(*(TextureClass::CheckTexture("Bomberchamp2_S")));
			}
			apk_sprite.setScale(2.f / 3.f, 2.f / 3.f);
		}

		if(apk_direction == DLeft)
		{
			if (firstPlayer)
			{
				apk_sprite.setTexture(*(TextureClass::CheckTexture("Bomberchamp_S")));
			}
			else
			{
				apk_sprite.setTexture(*(TextureClass::CheckTexture("Bomberchamp2_S")));
			}
			apk_sprite.setScale(-2.f / 3.f, 2.f / 3.f);
		}
		
	}
}

void Bomberchamp::SetLocation(const grim::Vector2& loc)
{
	SetPlayers::SetLocation(loc);
	apk_sprite.setPosition(loc.x, loc.y);

}

BomberChampController::BomberChampController(bool firstPlayer)
	:apk_moveSpeed(200),
	apk_firstPlayer(firstPlayer),
	apk_bombInterval(0.5f),
	apk_bombTime(0.5f)
{
	
}

void BomberChampController::Update(const float& time)
{
	auto *own = dynamic_cast<Bomberchamp*>(apk_owner);

	apk_bombTime -= time;
	if(apk_firstPlayer)
	{
		if (Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::A) &&  !Keyboard::isKeyPressed(Keyboard::D))
		{
			this->MoveUp(-apk_moveSpeed * time);
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D))
		{
			this->MoveDown(apk_moveSpeed * time);
		}
		if (Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::D))
		{
			this->MoveLeft(-apk_moveSpeed * time);
		}
		if (Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::A))
		{
			this->MoveRight(apk_moveSpeed * time);
		}

		if(Keyboard::isKeyPressed(Keyboard::Space) && apk_bombTime <= 0)
		{
			apk_bombTime = apk_bombInterval;
			auto *bomb = new Bomb();
			grim::Vector2f loc = apk_owner->GetLocation();
			loc.x = (int(loc.x) / 40) * 40;
			loc.y = (int(loc.y) / 40) * 40;
			bomb->SetLocation(loc);
			GameClass::Instance().GetCurrentLevel()->Add(bomb);
		}
	}
	else
	{
		
		if (Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Down))
		{
			
			this->MoveUp(-apk_moveSpeed * time);	
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left))
		{
			this->MoveDown(apk_moveSpeed * time);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Down) && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Right))
		{
			this->MoveLeft(-apk_moveSpeed * time);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Down) && !Keyboard::isKeyPressed(Keyboard::Up))
		{
			this->MoveRight(apk_moveSpeed * time);
		}

		if (Keyboard::isKeyPressed(Keyboard::RControl) && apk_bombTime <= 0)
		{
			apk_bombTime = apk_bombInterval;
			auto *bomb = new Bomb();
			grim::Vector2f loc = apk_owner->GetLocation();
			loc.x = (int(loc.x) / 40) * 40;
			loc.y = (int(loc.y) / 40) * 40;
			bomb->SetLocation(loc);
			GameClass::Instance().GetCurrentLevel()->Add(bomb);
		}
	}
	
	
}
bool BomberChampController::MoveLeft(const float& tim)
{
	
	auto *own = dynamic_cast<Bomberchamp*>(apk_owner);
	auto location = apk_owner->GetLocation();
	
	apk_owner->Move(grim::Vector2( tim, 0));
	own->SetDirection(DLeft, apk_firstPlayer);


	if (own->IsColliding())
		apk_owner->Move(grim::Vector2(-tim, 0));



	return false;
}

bool BomberChampController::MoveRight(const float& tim)
{
	auto *own = dynamic_cast<Bomberchamp*>(apk_owner);
	auto location = apk_owner->GetLocation();

	apk_owner->Move(grim::Vector2(  tim, 0));
	own->SetDirection(DRight, apk_firstPlayer);

	if (own->IsColliding())
		apk_owner->Move(grim::Vector2(-tim, 0));

	return false;
}

bool BomberChampController::MoveUp(const float& tim)
{
	auto *own = dynamic_cast<Bomberchamp*>(apk_owner);
	auto location = apk_owner->GetLocation();

	apk_owner->Move(grim::Vector2(0,   tim));
	own->SetDirection(DUp, apk_firstPlayer);

	if (own->IsColliding())
		apk_owner->Move(grim::Vector2(0, -tim));

	//if (own->IsExplosionColliding())
		//apk_owner->Destroy(); 

	return false;
}

bool BomberChampController::MoveDown(const float& tim)
{
	auto *own = dynamic_cast<Bomberchamp*>(apk_owner);
	auto location = apk_owner->GetLocation();


	apk_owner->Move(grim::Vector2(0,  tim));
	own->SetDirection(DDown, apk_firstPlayer);


	if (own->IsColliding())
		apk_owner->Move(grim::Vector2(0, -tim));

	return false;
}
