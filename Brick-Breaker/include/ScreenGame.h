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

#include "Player.h"
#include "Brick.h"
#include "Ball.h"

class ScreenGame : public DecentEngine::Screen {
	DecentEngine::Camera m_camera;

	Player m_player;

	std::vector<Brick> m_bricks;
	std::vector<Ball> m_balls;

	int m_score = 0;
	bool m_loss = false;
public:
	ScreenGame();
	~ScreenGame();

	void init();
	void destroy();

	void update();
	void render();

	static DecentEngine::FontRenderer fontRenderer;

};

#endif
