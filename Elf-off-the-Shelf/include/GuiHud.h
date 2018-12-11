/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-9
 *	Engine Version:		0.6.6
 *	Compiler:		g++ -std=c++17
 * */

#ifndef GUIHUD_H
#define GUIHUD_H

#include <Engine/Gui.h>

class GuiHud : public DecentEngine::Gui{
public:
	GuiHud();
	~GuiHud();

	void init();
	void update();
	void render();
};

#endif
