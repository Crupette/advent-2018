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

#include "Piece.h"

class ScreenGame : public DecentEngine::Screen {
	DecentEngine::Camera m_camera;
	DecentEngine::AudioManager m_audioManager;

	std::mt19937 m_engine;

	std::vector<Piece> m_pieces;
public:
	ScreenGame();
	~ScreenGame();

	void init();
	void destroy();

	void update();
	void render();

	Piece* getPiece(int x, int y);

	static DecentEngine::FontRenderer fontRenderer;

};

#endif
