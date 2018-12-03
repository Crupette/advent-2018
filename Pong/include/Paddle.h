/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-2
 *	Engine Version:		0.2.0
 *	Compiler:		g++ -std=c++17
 * */

#ifndef PADDLE_H
#define PADDLE_H

#include <Engine/Object.h>

#include "Ball.h"

#include <random>
#include <ctime>

class Paddle {
	bool m_side;
	static std::mt19937 m_engine;
public:
	Paddle(bool side);
	~Paddle();

	void init();
	
	void update(Ball& ball);
	void render();

	DecentEngine::Object object;	
};

#endif
