/*
 *	Created By:		Jon Santmyer
 *	Creation Date:		2018-11-30
 *	Compiler:		g++ -std=c++17
 * */

#ifndef PLAYER_H
#define PLAYER_H

#include <Engine/Object.h>
#include <Engine/SpriteBatch.h>

class Player {
public:
	Player();
	~Player();

	void init();

	void update();
	void render(DecentEngine::SpriteBatch& batch);

	DecentEngine::Object object;
};

#endif
