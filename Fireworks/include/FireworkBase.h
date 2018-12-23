/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-23
 *	Engine Version:		0.9.1
 *	Compiler:		g++ -std=c++17
*/

#ifndef FIREWORK_H
#define FIREWORK_H

#include <Engine/Particle.h>

#include <random>

class FireworkBase : public DecentEngine::Particle{
	static std::mt19937 m_engine;
public:
	FireworkBase(glm::vec2 position, float life);
	~FireworkBase();

	bool update();
};

class FireworkSpark : public DecentEngine::Particle{
public:
	FireworkSpark(glm::vec2 position, glm::vec2 velocity, int color, float life);	
	~FireworkSpark();

	bool update();
};

#endif
