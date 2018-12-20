#ifndef SCREENGAME_H
#define SCREENGAME_H

#include <Engine/Screen.h>
#include <Engine/SpriteBatch.h>
#include <Engine/ShaderHandler.h>
#include <Engine/Camera.h>
#include <Engine/FontRenderer.h>
#include <Engine/Object.h>
#include <Engine/AudioManager.h>

#include "Snowball.h"

#include <vector>
#include <random>
#include <ctime>

class ScreenGame : public DecentEngine::Screen {
	DecentEngine::Camera m_camera;
	DecentEngine::AudioManager m_audioManager;

	std::mt19937 m_engine;

	Snowball m_snowball;
	DecentEngine::Object m_cannon;
	DecentEngine::Sprite m_floor;
	DecentEngine::Sprite m_equator;

	int m_money = 0;
	int m_costPower = 10;
	int m_costAero = 10;
public:
	ScreenGame();
	~ScreenGame();

	void init();
	void destroy();

	void update();
	void render();

	int getMoney() {return m_money; }
	int getCostPower() { return m_costPower; }
	int getCostAero() { return m_costAero; }

	void buyPower();
	void buyAero();

	static DecentEngine::FontRenderer fontRenderer;

};

#endif
