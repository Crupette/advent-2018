/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-6
 *	Engine Version:		0.5.6
 *	Compiler:		g++ -std=c++17
 * */

#ifndef BALL_H
#define BALL_H

#include <random>

#include <Engine/Object.h>

class Ball {
	static std::mt19937 m_engine;
public:
	Ball(const glm::vec2& position, const glm::vec2& velocity, bool diverge);
	~Ball();

	void update();
	void render();

	void bounce(bool dirx, bool diry);

	DecentEngine::Object object;
};

#endif
