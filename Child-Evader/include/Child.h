/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-9
 *	Engine Version:		0.6.6
 *	Compiler:		g++ -std=c++17
 * */

#ifndef CHILD_H
#define CHILD_H

#include <Engine/Object.h>

class Child {
public:
	Child(glm::vec2 position);
	~Child();

	void update(glm::vec2 nearestPlayer, glm::vec2 nearestTree, bool treeFull);
	void render();

	DecentEngine::Object object;
	bool presents = false;
};

#endif
