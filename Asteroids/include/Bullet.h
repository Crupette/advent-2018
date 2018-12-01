/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-11-30
 *	Compiler:		g++ -std=c++17
 * */

#ifndef BULLET_H
#define BULLET_H

#include <Engine/Object.h>
#include <Engine/SpriteBatch.h>

class Bullet {
	float m_life;
public:
	Bullet(const glm::vec2& position, float rotation);
	~Bullet() {}

	bool update();
	void render(DecentEngine::SpriteBatch& batch);

	DecentEngine::Object object;
};

#endif
