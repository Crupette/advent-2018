#include "ScreenGame.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>
#include <Engine/RendererDefault.h>
#include <Engine/TextureCache.h>
#include <Engine/GuiManager.h>
#include <Engine/ParticleEngine.h>

#include "FireworkBase.h"

DecentEngine::FontRenderer ScreenGame::fontRenderer;

ScreenGame::ScreenGame() : m_engine(time(0)){

}
ScreenGame::~ScreenGame(){

}
void ScreenGame::init(){
	m_camera.init(glm::vec2(1024.f / 2.f, 768.f / 2.f), 1.f, 0.f); 
	glClearColor(0.1f, 0.1f, 0.2f, 1.f);

	DecentEngine::ParticleEngine::useCamera(&m_camera);
}
void ScreenGame::destroy() {
}
void ScreenGame::update(){
	m_camera.update(DecentEngine::Base::getWindow());
	
	if(DecentEngine::InputManager::isKeyPressed(SDL_BUTTON_LEFT)){
		glm::uvec2 mousepos = DecentEngine::InputManager::getMousePosition();
		mousepos.y = 768 - mousepos.y;
		float life = mousepos.y / 200.f;
		DecentEngine::ParticleEngine::addParticle(new FireworkBase(glm::vec2(mousepos.x, 0.f), life));	
	}
	
}
void ScreenGame::render(){

}
