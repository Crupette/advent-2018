#ifndef SCREENGAME_H
#define SCREENGAME_H

#include <Engine/Screen.h>
#include <Engine/SpriteBatch.h>
#include <Engine/ShaderHandler.h>
#include <Engine/Camera.h>
#include <Engine/FontRenderer.h>
#include <Engine/Object.h>

#include <vector>
#include <random>
#include <ctime>

#include "Elf.h"

class ScreenGame : public DecentEngine::Screen {
	DecentEngine::Camera m_camera;

	std::mt19937 m_engine;
	DecentEngine::Sprite m_shelf;

	std::vector<Elf> m_elfs;
	int m_score = 0;
	float m_timer = 0;
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
