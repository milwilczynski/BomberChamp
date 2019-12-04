#include "../Headers/SceneLevel.h"
#include "../Headers/Background.h"
#include "../Headers/Bomb.h"
#include "../Headers/Bomberchamp.h"


SceneLevel::SceneLevel()
{
	
}

SceneLevel::~SceneLevel()
{
	this->CleanPlayerUp();
}

bool SceneLevel::Add(Player *player)
{
	if(player)
	{
		if(!this->Exists(player))
		{
			apk_players.push_back(player);
			return true;
		}
	}
	return false;
}

bool SceneLevel::Remove(Player *player)
{
	if (player)
	{

		auto playerIt = find(apk_players.begin(), apk_players.end(), player);
		if (playerIt != apk_players.end())
		{
			apk_players.erase(playerIt);
			return true;
		}
	}
	return false;
}

bool SceneLevel::Exists(Player *player)
{
	return find(apk_players.begin(), apk_players.end(), player) != apk_players.end();
}

size_t SceneLevel::CleanPlayerUp()
{
	size_t playerCount = apk_players.size();
	for(auto *player : apk_players)
	{
		delete player;
	}
	return playerCount;
}

void SceneLevel::Update(const float &time)
{
	for(auto i = 0u; i < apk_players.size(); i++)
	{
		apk_players[i]->Update(time);
		if(apk_players[i]->IsDestroyed())
		{
			delete apk_players[i];
			apk_players.erase(apk_players.begin()+i);
			i--;
		}
	}
}
vector<Player*> SceneLevel::GetPlayerBomberchamps()
{

	vector<Player*> players;
	for (auto *player : apk_players)
	{
		auto *bomber = dynamic_cast<Bomberchamp*>(player);
		if (bomber) {
			players.push_back(player);
		}
	}
	return players;
}

vector<Player*> SceneLevel::GetPlayersAtLocation(const grim::Vector2& loc)
{

	vector<Player*> players;
	for(auto *player : apk_players)
	{
		if(player -> GetLocation() == loc)
		{
			players.push_back(player);
		}
	}
	return players;
}

vector <Player *> SceneLevel::ExplosionCollider()
{
	vector<Player*> players;
	for (auto *player : apk_players) {

		auto *explosion = dynamic_cast<Explosion *>(player);
		if (explosion)
		{
			players.push_back(player);
		}

	}
	return players;
}

vector <Player *> SceneLevel::GetAllColliders()
{
	vector<Player*> players;
	for (auto *player : apk_players) {

		auto *tile = dynamic_cast<Background*>(player);
		auto *bomb = dynamic_cast<Bomb *>(player);
		if(tile && (tile->GetType() != BackgroundType::TGround))
		{
			players.push_back(player);
		}




	}
	return players;
}
void SceneLevel::Draw()
{
	for (auto *player : apk_players)
	{
		player->Draw();
	}
}