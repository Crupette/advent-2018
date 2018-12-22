/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-21
 *	Engine Version:		0.9.1
 *	Compiler:		g++ -std=c++17
 * */

#ifndef TILE_H
#define TILE_H

#include <Engine/Sprite.h>

class Tile {
public:
	Tile(glm::uvec2 position, bool usable);
	~Tile();

	void render();

	DecentEngine::Sprite sprite;
	bool usable;
};

#endif
