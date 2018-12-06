#include "ScreenGame.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>
#include <Engine/RendererDefault.h>
#include <Engine/TextureCache.h>
#include <Engine/GuiManager.h>

#include "World.h"
#include "GuiHud.h"

DecentEngine::FontRenderer ScreenGame::fontRenderer;

ScreenGame::ScreenGame(){

}
ScreenGame::~ScreenGame(){

}
void ScreenGame::init(){
	m_camera.init(glm::vec2(0, 0), 1.f, 0.f);	
	fontRenderer.init("assets/fonts/Vera.ttf", 32);

	m_sky.init(glm::vec2(0), glm::vec2(1024, 768), 0.f, glm::uvec4(0, 128, 255, 255), "blank");

	World::init();

	m_player.init();

	DecentEngine::GuiManager::addGui("hud", new GuiHud());
}
void ScreenGame::destroy() {
	fontRenderer.destroy();

	World::destroy();
}
void ScreenGame::update(){
	glm::vec2 mousePosition = DecentEngine::InputManager::getMousePosition();
	mousePosition = glm::vec2(mousePosition.x, 768 - mousePosition.y);
	mousePosition += glm::vec2(m_camera.getPosition().x - 1024 / 2.f, m_camera.getPosition().y - 768 / 2.f);
	glm::ivec2 tilePosition = glm::ivec2((int)(mousePosition.x) / 50, (int)(mousePosition.y) / 50);

	if(mousePosition.x < 0.f) tilePosition.x--;
	if(mousePosition.y < 0.f) tilePosition.y--;

	if(DecentEngine::InputManager::isKeyDown(SDL_BUTTON_LEFT)){
		printf("%i, %i\n", tilePosition.x, tilePosition.y);
		if(World::tileExists(tilePosition.x, tilePosition.y)){
			if(World::mineTile(tilePosition.x, tilePosition.y)){
				m_player.money++;
			}
		}
	}
	World::update();

	m_player.update();
	m_camera.setPosition(m_player.object.getPosition());
	m_camera.update(DecentEngine::Base::getWindow());
	m_sky.position.x = m_camera.getPosition().x - 1024 / 2.f;

}
void ScreenGame::render(){
	DecentEngine::RendererDefault::begin(m_camera);
	
	DecentEngine::RendererDefault::addSprite(&m_sky);

	m_player.render();

	DecentEngine::RendererDefault::end();
	DecentEngine::RendererDefault::beginShader(m_camera);

	World::render();

	DecentEngine::RendererDefault::endShader();
}
