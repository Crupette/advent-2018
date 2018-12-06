/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-5
 *	Engine Version:		0.4.6
 *	Compiler:		g++ -std=c++17
 * */

#ifndef GUI_HUD_H
#define GUI_HUD_H

#include <Engine/Gui.h>

class GuiHud : public DecentEngine::Gui {
public:
	GuiHud();
	~GuiHud();

	void update();
	void render();
};

#endif
