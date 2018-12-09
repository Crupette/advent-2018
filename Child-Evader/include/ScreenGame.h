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
#include "Tree.h"
#include "Child.h"

class ScreenGame : public DecentEngine::Screen {
	DecentEngine::Camera m_camera;

	Player m_player;
	std::vector<Tree> m_trees;
	std::vector<Child> m_children;	

	std::mt19937 m_engine;

	bool m_loss = false;
public:
	ScreenGame();
	~ScreenGame();

	void init();
	void destroy();

	void update();
	void render();

	double treeDistance();

	static DecentEngine::FontRenderer fontRenderer;

};

#endif
