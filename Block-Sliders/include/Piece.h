/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-20
 *	Engine Version:		0.9.1
 *	Compiler:		g++ -std=c++17
 * */

#ifndef PIECE_H
#define PIECE_H

#include <Engine/Object.h>

class Piece {
	glm::uvec2 m_oldPosition;
	float m_progress = 0.f;
public:
	Piece(glm::uvec2 position, char character);
	~Piece();

	void update();
	void render();
	void renderText();

	void moveTo(glm::uvec2 newPosition);

	DecentEngine::Object object;
	bool animating = false;
	bool exists = true;
	glm::uvec2 tilePosition;

	char character;
};

#endif
