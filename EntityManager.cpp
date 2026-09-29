#include "EntityManager.h" 
#include "Player.h" 
#include "Enemy.h" 
 

void EntityManager::AddEntity(std::unique_ptr<Entity> entity)
{
	entities.push_back(std::move(entity));
}

void EntityManager::Update(float dt)
{
	for (auto& entity : entities)
	{
		entity->Update(dt);
	}
}

Player* EntityManager::GetPlayer()
{
	for (auto& entity : entities)
	{
		Player* player = dynamic_cast<Player*>(entity.get());
		if (player != nullptr)
		{
			return player;
		}
	}
	return nullptr;
}

Enemy* EntityManager::GetEnemy()
{
	for (auto& entity : entities)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(entity.get());
		if (enemy != nullptr)
		{
			return enemy;
		}
	}
	return nullptr;
}

void EntityManager::RemoveDeadEntities()
{
	for (auto it = entities.begin(); it != entities.end();)
	{
		if (!(*it)->IsAlive())
		{
			it = entities.erase(it);
		}
		else
		{
			++it;
		}
	}
}
