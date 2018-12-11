/**
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-10
 *	Engine Version:		0.6.6
 *	Compiler:		g++ -std=c++17
 **/

#ifndef ELF_H
#define ELF_H

#include <Engine/Object.h>

class Elf {
public:
	Elf(glm::vec2 position);
	~Elf();

	bool update();
	void render();

	void click();

	DecentEngine::Object object;
	bool dead = false;
	float timeAlive = 0;
};

#endif
