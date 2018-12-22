#ifndef SCREENGAME_H
#define SCREENGAME_H

#include <Engine/Screen.h>
#include <Engine/SpriteBatch.h>
#include <Engine/ShaderHandler.h>
#include <Engine/Camera.h>
#include <Engine/FontRenderer.h>
#include <Engine/Object.h>
#include <Engine/AudioManager.h>

#include <vector>
#include <random>
#include <ctime>

#include "Tile.h"
#include "Piece.h"

class ScreenGame : public DecentEngine::Screen {
	DecentEngine::Camera m_camera;
	DecentEngine::AudioManager m_audioManager;

	std::mt19937 m_engine;

	std::vector<Tile> m_tiles;
	std::vector<Piece> m_pieces;

	bool m_player = false;
	bool m_moved = false;
	Piece* m_selected = nullptr;	
public:
	ScreenGame();
	~ScreenGame();

	void init();
	void destroy();

	void update();
	void render();

	static DecentEngine::FontRenderer fontRenderer;
	
	bool positionValid(glm::uvec2 position);
	Piece* isPieceOn(glm::uvec2 position);
	bool piecesAdjacent(glm::uvec2 position);
};

#endif
