/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-7
 *	Engine Version:		0.5.6
 *	Compiler:		g++ -std=c++17
 * */

#ifndef PRESENT_H
#define PRESENT_H

#include <Engine/Object.h>

#include <random>

class Present {
	static std::mt19937 m_engine;
public:
	Present(glm::vec2 position);
	~Present();

	void update();
	void render();

	DecentEngine::Object object;
};

#endif
