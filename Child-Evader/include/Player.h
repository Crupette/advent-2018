/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-9
 *	Engine Version:		0.6.6
 *	Compiler:		g++ -std=c++17
 * */

#ifndef PLAYER_H
#define PLAYER_H

#include <Engine/Object.h>

class Player {
public:
	Player() {}
	~Player() {}

	void init();
	void update();
	void render();

	DecentEngine::Object object;
};

#endif
