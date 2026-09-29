#pragma once

class Player;
class Enemy;

class CollisionSystem
{
public:
	void Update(Player& player);
	void Update(Enemy& enemy);
};

