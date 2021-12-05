#include "Gun.h"
#include "InputState.h"
#include "Body.h"
#include "Collider.h"
#include "Projectile.h"

Gun::Gun(float fireRate, float projectileSize, bool isAI, const std::string& projectileTag, const std::string& texture) : Component("Gun"), position(glm::vec3(0.0f, 0.0f, 0.0f)), rotation(0.0f), gom(&Engine::getInstance().gameObjectManager),
	FireRate(fireRate), projectileSize(projectileSize), mTime(0.0f), mIsAI(isAI), projectileTag(projectileTag), projectileTexture(texture)
{
	setParent(gom->find("Ship"));
}

Gun::~Gun()
{
	/*while (!projectiles.empty())
	{
		destroyProjectile(projectiles.back());
	}*/
}

void Gun::update(float deltaTime)
{
	position = getGameObject()->transform->position;
	rotation = getGameObject()->transform->rotation;

	mTime += deltaTime;

	if (mTime >= FireRate)
	{
		if (!mIsAI && InputState::KeyPressed::space)
		{
			projectiles.push_back(createAndFireProjectile(projectileSize));
		}
		else if(mIsAI)
		{
			projectiles.push_back(createAndFireAIProjectile(projectileSize));
		}

		mTime = 0.0f;
	}
}

GameObject* Gun::createAndFireProjectile(float size)
{
	GameObject* gameObject = gom->create(position, "Projectile");
	gameObject->transform->rotate(rotation);
	gameObject->transform->scale(glm::vec3(size, size, 0.0f));
	gameObject->addComponent(new Body());
	gameObject->addComponent(new Projectile(rotation, 250.0f));
	gameObject->addComponent(new Collider(glm::vec2(position.x, position.y), size / 2.0f));
	gameObject->getComponent<Collider>()->setTag(projectileTag);
	gameObject->init();
	gameObject->sprite->swapTexture(projectileTexture);

	return gameObject;
}

GameObject* Gun::createAndFireAIProjectile(float size)
{
	GameObject* gameObject = gom->create(position, "Projectile");
	gameObject->transform->rotate(45.0f);
	gameObject->transform->scale(glm::vec3(size, size, 0.0f));
	gameObject->addComponent(new Body());
	gameObject->addComponent(new Projectile(45.0f, 250.0f));
	gameObject->addComponent(new Collider(glm::vec2(position.x, position.y), size / 2.0f));
	gameObject->getComponent<Collider>()->setTag(projectileTag);
	gameObject->init();
	gameObject->sprite->swapTexture(projectileTexture);

	return gameObject;
}