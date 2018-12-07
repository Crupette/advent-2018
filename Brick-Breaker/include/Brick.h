/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-6
 *	Engine Version:		0.5.6
 *	Compiler:		g++ -std=c++17
 * */

#ifndef BRICK_H
#define BRICK_H

#include <Engine/Object.h>

#include <random>

class Brick {
	static std::mt19937 m_engine;
public:
	Brick(const glm::vec2& position);
	~Brick();

	void render();

	DecentEngine::Object object;
};

#endif
