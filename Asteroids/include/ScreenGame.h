#ifndef SCREENGAME_H
#define SCREENGAME_H

#include <Engine/Screen.h>
#include <Engine/SpriteBatch.h>
#include <Engine/ShaderHandler.h>
#include <Engine/Camera.h>
#include <Engine/FontRenderer.h>

#include "Player.h"
#include "Asteroid.h"
#include "Bullet.h"

#include <vector>
#include <random>
#include <ctime>

class ScreenGame : public DecentEngine::Screen {
	DecentEngine::SpriteBatch m_batch;
	DecentEngine::ShaderHandler* m_shader;

	DecentEngine::Camera m_camera;

	DecentEngine::FontRenderer m_fontRenderer;

	Player m_player;

	std::vector<Asteroid> m_asteroids;
	std::vector<Bullet> m_bullets;

	std::mt19937 m_engine;

	int m_score = 0;
	int m_lives = 5;
	float m_immortalTime = 0.f;

	void destroyAsteroid(size_t j);
public:
	ScreenGame();
	~ScreenGame();

	void init();
	void destroy();

	void update();
	void render();
};

#endif
