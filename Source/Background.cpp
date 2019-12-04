#include "../Headers/Background.h"
#include "../Headers/Game.h"
#include "../Headers/TextureClass.h"

Background::Background(BackgroundType type)
	:SetPlayers(new BackgroundController),
	apk_type(type)
{
	if(type == BackgroundType::TGround)
		apk_sprite.setTexture(*(TextureClass::CheckTexture("Tile_Ground")));
	
	else if(type == BackgroundType::TExpload)
		apk_sprite.setTexture(*(TextureClass::CheckTexture("Tile_Expload")));
	
	else if(type == BackgroundType::TSolid)
		apk_sprite.setTexture(*(TextureClass::CheckTexture("Tile_Solid")));


	apk_sprite.setScale(40.f/64.f, 40.f/ 64.f);
}

void Background::Draw()
{
	GameClass::Instance().GetWindow().draw(apk_sprite);
}



void Background::SetLocation(const grim::Vector2& loc)
{
	SetPlayers::SetLocation(loc);
	apk_sprite.setPosition(loc.x, loc.y);

}

BackgroundController::BackgroundController()
{

}

void BackgroundController::Update(const float& time)
{


}
