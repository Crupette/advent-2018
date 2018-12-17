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

#include "Present.h"

class ScreenGame : public DecentEngine::Screen {
	DecentEngine::Camera m_camera;
	DecentEngine::AudioManager m_audioManager;

	std::mt19937 m_engine;
	float m_timer = 0;

	std::vector<Present> m_presents;
	int m_requested = 0;
	int m_chances = 3;
	bool m_loss = false;

	DecentEngine::Sprite m_background;
public:
	ScreenGame();
	~ScreenGame();

	void init();
	void destroy();

	void update();
	void render();

	static DecentEngine::FontRenderer fontRenderer;
	static int m_score;
};

#endif
