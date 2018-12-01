/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-11-30
 *	Compiler:		g++ -std=c++17
 * */

#ifndef ASTEROID_H
#define ASTEROID_H

#include <Engine/Object.h>
#include <Engine/SpriteBatch.h>

class Asteroid {
	static int m_texId;
public:
	Asteroid(const glm::vec2& position, const glm::vec2& size, float rotVelocity);
	~Asteroid();

	void update();
	void render(DecentEngine::SpriteBatch& batch);

	DecentEngine::Object object;
};

#endif
