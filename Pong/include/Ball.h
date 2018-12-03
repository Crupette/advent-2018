/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-2
 *	Engine Version:		0.2.0
 *	Compiler:		g++ -std=c++17	
 * */

#ifndef BALL_H
#define BALL_H

#include <Engine/Object.h>

#include <random>
#include <ctime>

class Ball{
	std::mt19937 m_engine;
public:
	Ball();
	~Ball();
	
	void init();
	
	void update();
	void render();

	void bounce();

	DecentEngine::Object object;
};

#endif
