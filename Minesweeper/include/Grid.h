/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-1
 *	Compiler:		gcc -std=c++17
 * */

#ifndef GRID_H
#define GRID_H

#include <Engine/SpriteBatch.h>
#include <Engine/Sprite.h>

#include <cstdint>
#include <array>
#include <random>
#include <ctime>

#define GRID_SIZE 40

class Grid {
	struct Block {
		bool flagged = false;
		bool bomb = false;
		bool clicked = false;
	};

	DecentEngine::SpriteBatch m_batch;

	std::array<Block, GRID_SIZE * GRID_SIZE> m_blocks;
	int m_remainingBombs;
	bool m_needsUpdate = true;

	std::mt19937 m_engine;

	int bombAdjacent(uint8_t x, uint8_t y);
	bool testBlock(uint8_t x, uint8_t y);
public:
	Grid();
	~Grid();

	void init(int numBombs);
	void destroy();

	void update();
	void render();

	bool clickBlock(uint8_t x, uint8_t y);
	void flagBlock(uint8_t x, uint8_t y);
};

#endif
