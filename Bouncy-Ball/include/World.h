/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-13
 *	Engine Version:		0.8.0
 *	Compiler:		g++ -std=c++17
 * */

#ifndef WORLD_H
#define WORLD_H

#include <Engine/Object.h>

#include <random>
#include <vector>

class World {
	static std::mt19937 m_engine;
public:
	static void init();
	static void destroy();

	static void update(glm::vec2 playerPosition);
	static void render();

	static std::vector<DecentEngine::Object> terrain;
};

#endif
