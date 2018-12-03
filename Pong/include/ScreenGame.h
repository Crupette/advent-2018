#ifndef SCREENGAME_H
#define SCREENGAME_H

#include <Engine/Screen.h>
#include <Engine/SpriteBatch.h>
#include <Engine/ShaderHandler.h>
#include <Engine/Camera.h>
#include <Engine/FontRenderer.h>

#include <vector>
#include <random>
#include <ctime>

#include "Paddle.h"
#include "Ball.h"

class ScreenGame : public DecentEngine::Screen {
	DecentEngine::Camera m_camera;

	DecentEngine::FontRenderer m_fontRenderer;

	Paddle m_player, m_ai;
	Ball m_ball;

	int m_plrPoints = 0;
	int m_aiPoints = 0;
public:
	ScreenGame();
	~ScreenGame();

	void init();
	void destroy();

	void update();
	void render();
};

#endif
