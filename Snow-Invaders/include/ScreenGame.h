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
#include "Bullet.h"
#include "Snowflake.h"

class ScreenGame : public DecentEngine::Screen {
	DecentEngine::Camera m_camera;

	DecentEngine::FontRenderer m_fontRenderer;
	
	Player m_player;

	std::vector<Bullet> m_bullets;
	std::vector<Snowflake> m_snow;
	
	std::mt19937 m_engine;

	int m_round = 1;
	int m_remaining = 0;

	float m_timer = 0.f;

	bool m_loss = false;
public:
	ScreenGame();
	~ScreenGame();

	void init();
	void destroy();

	void update();
	void render();
};

#endif
