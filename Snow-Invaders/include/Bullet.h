/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-3
 *	Engine Version:		0.2.0
 *	Compiler:		g++ -std=c++17
 * */

#ifndef BULLET_H
#define BULLET_H

#include <Engine/Object.h>

class Bullet {
public:
	Bullet(float x);
	~Bullet();

	bool update();
	void render();

	DecentEngine::Object object;
};

#endif
