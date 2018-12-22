/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-21
 *	Engine Version:		0.9.1
 *	Compiler:		g++ -std=c++17
 * */

#ifndef PIECE_H
#define PIECE_H

#include <Engine/Object.h>

class Piece {
public:
	Piece(glm::uvec2 position, bool player);
	~Piece();

	void render();

	DecentEngine::Object object;
	glm::uvec2 position;
	bool player;
	bool king;
};

#endif
