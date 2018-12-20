/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-19
 *	Engine Version:		0.9.1
 *	Compiler:		g++ -std=c++17
 * */

#ifndef SNOWBALL_H
#define SNOWBALL_H

#include <Engine/Object.h>

class Snowball {
public:
	Snowball();
	~Snowball();

	void init();
	
	void update();
	void render();

	void launch(glm::vec2 position, glm::vec2 heading);

	bool launched = false;
	bool landed = false;

	float power = 10.f;
	float aerodynamics = 1.05f;

	DecentEngine::Object object;
};

#endif
