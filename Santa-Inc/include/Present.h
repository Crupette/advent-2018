/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-17
 *	Engine Version:		0.9.1
 *	Compiler:		g++ -std=c++17
 * */

#ifndef PRESENT_H
#define PRESENT_H

#include <Engine/Object.h>

class Present {
public:
	Present(int id);
	~Present();

	void update();
	void render();

	DecentEngine::Object object;
	int id;
	bool clicked = false;
};

#endif
