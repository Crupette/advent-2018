/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-22
 *	Engine Version:		0.9.1
 *	Compiler:		g++ -std=c++17
 * */
#ifndef CAT_H
#define CAT_H

#include <Engine/Object.h>

class Cat {
public:
	Cat(glm::vec2 position, int skin);
	~Cat();

	bool update();
	void render();

	DecentEngine::Object object;
	float life = 1.f;
};

#endif
