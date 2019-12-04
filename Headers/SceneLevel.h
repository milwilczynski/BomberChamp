#pragma once
#include "Main.h"
#include "Player.h"
class SceneLevel
{
public:
	typedef vector<Player *> PlayerV;


	SceneLevel();
	~SceneLevel();

	bool Add(Player *player);
	bool Remove(Player *player);
	bool Exists(Player *player);
	vector <Player *> ExplosionCollider();
	vector <Player*> GetPlayersAtLocation(const grim::Vector2 &loc);
	vector <Player*> GetPlayerBomberchamps();
	vector <Player *> GetAllColliders();

	size_t CleanPlayerUp();

	void Update(const float &time);

	void Draw();

	inline size_t Count() const
	{
		return apk_players.size();
	}

private:
	PlayerV apk_players;
};