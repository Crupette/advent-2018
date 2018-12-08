/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-7
 *	Engine Version:		0.5.6
 *	Compiler:		g++ -std=c++17
 * */

#ifndef REINDEER_H
#define REINDEER_H

#include <Engine/Object.h>

class Reindeer {
public:
	Reindeer(glm::vec2 position);
	~Reindeer();

	void update();
	void render();

	void bounce();

	DecentEngine::Object object;
};

#endif
