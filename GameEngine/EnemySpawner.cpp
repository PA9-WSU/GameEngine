#include "EnemySpawner.h"
#include "Engine.h"
#include "WindowManager.h"
#include "Collider.h"
#include "AsteroidMovement.h"
#include "Body.h"
#include "Gun.h"
#include <cstdlib>

EnemySpawner::EnemySpawner(int count, int time) : Component("EnemySpawner"), spawnCount(count), spawnTime(time),
	gom(&Engine::getInstance().gameObjectManager)
{
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::update(float deltaTime)
{
	static float timer = 0.0f;

	timer += deltaTime;

	if (timer >= spawnTime)
	{
		int width, height;
		glfwGetWindowSize(WindowManager::getInstance().getWindow(), &width, &height);

		timer = 0.0f;
		
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		GameObject* enemyShip = gom->create(position, "EnemyShip");
		enemyShip->transform->trans(glm::vec3((float)width - 10.0f, 10.0f, 0.0f));
		enemyShip->transform->rotate(0.0f);
		enemyShip->addComponent(new Body());
		enemyShip->addComponent(new AsteroidMovement());
		enemyShip->addComponent(new Collider(enemyShip->transform->position, enemyShip->transform->scalar.x));
		enemyShip->addComponent(new Gun(0.75f, (float)((std::rand() % 360) + 1), 25.0f, true, "Enemy", "firefox.png"));

		enemyShip->getComponent<AsteroidMovement>()->setForwardSpeed(50.0f);
		enemyShip->getComponent<Collider>()->setTag("Enemy");
		enemyShip->sprite->swapTexture("alien.png");
	}
}
