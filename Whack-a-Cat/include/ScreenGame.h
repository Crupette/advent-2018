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

#include "Cat.h"

class ScreenGame : public DecentEngine::Screen {
	DecentEngine::Camera m_camera;
	DecentEngine::AudioManager m_audioManager;

	std::mt19937 m_engine;

	DecentEngine::Sprite m_background;

	std::vector<Cat> m_cats;
	
	float m_timer = 1.f;
	int m_score = 0;
	int m_clicks = 0;
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
