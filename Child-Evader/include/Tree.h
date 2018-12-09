/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-9
 *	Engine Version:		0.6.6
 *	Compiler:		g++ -std=c++17
 * */

#ifndef TREE_H
#define TREE_H

#include <Engine/Object.h>

class Tree {
public:
	Tree(glm::vec2 position);
	~Tree();

	void render();

	DecentEngine::Object object;
	int presents = 0;
	bool full = false;
};

#endif
