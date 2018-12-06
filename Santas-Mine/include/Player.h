/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-5
 *	Engine Version:		0.4.3
 *	Compiler:		g++ -std=c++17
 * */

#ifndef PLAYER_H
#define PLAYER_H

#include <Engine/Object.h>

class Player {
public:
	Player();
	~Player();

	void init();
	void update();
	void render();

	DecentEngine::Object object;
	static int money;
	static int maxDepth;
};

#endif
