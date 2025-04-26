#pragma once
#include "Character.h"
#include "Projectile.h"
#include "Tile.h"
#include "CollisionManager.h"

class EnemyAI
{
public:
	EnemyAI(Projectile& enemyProjectile);
	void Update(Character& enemy, Character& player, Tile& tileMap);
	int attackTimer = 200;
private:
	Projectile& enemyProjectile;
	const float DETECTION_RANGE = 600.0f;
	const float ATTACK_RANGE = 150.0f;
	float speed = 1.0f;
	bool isAttacking = false;
};