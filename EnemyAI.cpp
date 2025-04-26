#include "EnemyAI.h"
#include <cmath>

EnemyAI::EnemyAI(Projectile& enemyProjectile)
	:enemyProjectile(enemyProjectile) {
}

void EnemyAI::Update(Character& enemy, Character& player, Tile& tileMap)
{
	if (!enemy.isAlive()) return;
	if (player.isAlive())
	{
		float dx = player.getRect().x - enemy.getRect().x;
		float distance = sqrt(pow(dx, 2) + pow(player.getRect().y - enemy.getRect().y, 2));

		bool facingRight = (dx > 0);
		enemy.setDirection(facingRight);

		if (distance <= ATTACK_RANGE && !enemy.getAttackState() && !enemy.getJumpState())
		{
			if (attackTimer > 300)
			{
				CollisionManager::handleCollisions(enemy, tileMap);
				enemy.setAttackState(true);
				enemyProjectile.setActive(true);
				enemyProjectile.setDirection(facingRight);

				if (facingRight)
				{
					enemyProjectile.setDest(enemy.getRect().x + 110, enemy.getRect().y - 50, 100, 100);
				}
				else {
					enemyProjectile.setDest(enemy.getDest().x - 10, enemy.getDest().y - 50, 100, 100);
				}
				attackTimer = 0;
			}
			attackTimer++;
		}

		if (distance <= DETECTION_RANGE)
		{
			if (enemy.getDirection()) // facingRight
			{
				enemy.setVelocityX(3 * speed);
			}
			else enemy.setVelocityX(-0.8 * speed);

			CollisionManager::handleCollisions(enemy, tileMap);
		}

		if (!enemyProjectile.isActive()) {
			enemy.setAttackState(false);
		}
	}
	else
	{
		enemy.setVelocityX(0);
	}
}