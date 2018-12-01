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

#include "Grid.h"

class ScreenGame : public DecentEngine::Screen {
	DecentEngine::SpriteBatch m_batch;
	DecentEngine::ShaderHandler* m_shader;

	DecentEngine::Camera m_camera;

	DecentEngine::FontRenderer m_fontRenderer;

	Grid m_grid;

	bool m_lossed = false;
public:
	ScreenGame();
	~ScreenGame();

	void init();
	void destroy();

	void update();
	void render();
};

#endif
