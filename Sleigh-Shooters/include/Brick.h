/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-7
 *	Engine Version:		0.5.6
 *	Compiler:		g++ -std=c++17
 * */

#ifndef BRICK_H
#define BRICK_H

#include <Engine/Object.h>

class Brick {
public:
	Brick(glm::vec2 position);
	~Brick();

	void render();

	DecentEngine::Object object;
	int health = 3;
};

#endif
