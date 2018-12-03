/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-3
 *	Engine Version:		0.2.0
 *	Compiler:		g++ -std=c++17
 * */

#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H

#include <Engine/Object.h>

#include <random>

class Snowflake {
	static std::mt19937 m_engine;
public:
	Snowflake();
	~Snowflake();

	bool update();
	void render();

	DecentEngine::Object object;
};

#endif
