#include "ScreenGame.h"

#include "GuiHud.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>
#include <Engine/RendererDefault.h>
#include <Engine/TextureCache.h>
#include <Engine/GuiManager.h>
#include <Engine/ParticleEngine.h>

DecentEngine::FontRenderer ScreenGame::fontRenderer;

ScreenGame::ScreenGame() : m_engine(time(0)){

}
ScreenGame::~ScreenGame(){

}
void ScreenGame::init(){
	m_camera.init(glm::vec2(1024.f / 2.f, 768.f / 2.f), 1.f, 0.f); 
	fontRenderer.init("assets/fonts/Vera.ttf", 32);
	m_audioManager.init();

	glClearColor(0.5f, 0.5f, 0.7f, 1.f);
	DecentEngine::Base::getWindow()->setIcon("assets/textures/ball.png");
	
	DecentEngine::ParticleEngine::useCamera(&m_camera);

	m_snowball.init();
	m_cannon.init(glm::vec2(0.f), glm::vec2(64.f, 128.f), 0.f, "assets/textures/cannon.png");
	m_floor.init(glm::vec2(0.f), glm::vec2(1024.f, 10.f), 0.f, glm::uvec4(255), "blank");
	m_equator.init(glm::vec2(100000.f, 10.f), glm::vec2(64.f, 256.f), 0.f, glm::uvec4(255), "assets/textures/equator.png");

	DecentEngine::GuiManager::addGui("hud", new GuiHud());
}
void ScreenGame::destroy() {
	fontRenderer.destroy();
	m_audioManager.destroy();
}
void ScreenGame::update(){
	m_camera.setPosition(glm::vec2(std::max(1024/2.f, m_snowball.object.getPosition().x), std::max(768.f/2.f, m_snowball.object.getPosition().y)));
	m_camera.update(DecentEngine::Base::getWindow());

	glm::uvec2 tmpmouse = DecentEngine::InputManager::getMousePosition();
	glm::vec2 mousePos(tmpmouse.x, 768 - tmpmouse.y);

	float rotation = std::atan2(mousePos.y, mousePos.x);
	float degrees = rotation * (180 / 3.141592);
	m_cannon.setRotation(degrees - 90);

	if(DecentEngine::InputManager::isKeyPressed(SDL_BUTTON_LEFT)){
		if(!m_snowball.launched){
			m_snowball.launch(glm::vec2(0, 10), DecentEngine::getHeading(degrees));
		}
	}

	m_floor.position = glm::vec2(m_camera.getPosition().x - 1024.f / 2.f, 0);
	
	m_snowball.update();

	if(m_snowball.object.getPosition().y < 0.f){
		if(!m_snowball.landed) m_money += m_snowball.object.getPosition().x / 100.f;
		m_snowball.landed = true;
		m_snowball.launched = false;
	}
}
void ScreenGame::render(){
	DecentEngine::RendererDefault::begin(m_camera);

	m_snowball.render();
	
	DecentEngine::RendererDefault::addObject(&m_cannon);
	DecentEngine::RendererDefault::addSprite(&m_floor);
	DecentEngine::RendererDefault::addSprite(&m_equator);

	DecentEngine::RendererDefault::end();
}

void ScreenGame::buyPower(){
	if(m_money >= m_costPower){
		m_money -= m_costPower;
		m_costPower += 50;
		m_snowball.power += 0.05f;
	}
}

void ScreenGame::buyAero(){
	if(m_money >= m_costAero){
		m_money -= m_costAero;
		m_costAero += 50;
		m_snowball.aerodynamics -= 0.005f;
	}
}
