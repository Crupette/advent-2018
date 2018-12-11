#include "ScreenGame.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>
#include <Engine/RendererDefault.h>
#include <Engine/TextureCache.h>
#include <Engine/GuiManager.h>

DecentEngine::FontRenderer ScreenGame::fontRenderer;

ScreenGame::ScreenGame() : m_engine(time(0)){

}
ScreenGame::~ScreenGame(){

}
void ScreenGame::init(){
	m_camera.init(glm::vec2(1024.f / 2.f, 768.f / 2.f), 1.f, 0.f); 
	fontRenderer.init("assets/fonts/Vera.ttf", 32);

	glClearColor(0.5f, 0.5f, 1.f, 1.f);
	m_shelf.init(glm::vec2(0.f), glm::vec2(1024.f, 200.f), 0.f, glm::uvec4(139, 69, 19, 255), "blank");
	
	for(size_t i = 0; i < 8; i++){
		m_elfs.emplace_back(glm::vec2(i * 128, 150.f));
	}
}
void ScreenGame::destroy() {
	fontRenderer.destroy();
}
void ScreenGame::update(){
	m_camera.update(DecentEngine::Base::getWindow());

	for(size_t i = 0; i < m_elfs.size(); i++){
		if(!m_elfs[i].update()){
			m_elfs.erase(m_elfs.begin() + i);
		}
		if(DecentEngine::InputManager::isKeyPressed(SDL_BUTTON_LEFT)){
			glm::vec2 mousepos = (glm::vec2)DecentEngine::InputManager::getMousePosition();
			mousepos.y = 768.f - mousepos.y;
			glm::vec4 bounds = m_elfs[i].object.aabb.getBounds();
			if(mousepos.x > bounds.x && mousepos.x < bounds.x + bounds.z && mousepos.y > bounds.y && mousepos.y < bounds.y + bounds.w && !m_elfs[i].dead){
				m_elfs[i].click();
				m_score++;
			}
		}
	}
	if(m_elfs.size() < 8){
		m_timer += DecentEngine::FPSRegulator::getDelta();
		if(m_timer >= 0.5f){
			m_timer = 0.f;
			std::uniform_int_distribution<int> pos(0, 7);
			float x = pos(m_engine) * 128;
			bool held = true;
			while(held){
				bool occupied = false;
				for(Elf& elf : m_elfs){
					if(elf.object.getPosition().x == x){
						occupied = true;
						break;
					}
				}
				if(!occupied) held = false;
				if(held) x = pos(m_engine) * 128;
			}
			m_elfs.emplace_back(glm::vec2(x, 150.f));
		}	
	}
}
void ScreenGame::render(){
	DecentEngine::RendererDefault::begin(m_camera);

	DecentEngine::RendererDefault::addSprite(&m_shelf);

	for(Elf& elf : m_elfs){
		elf.render();
	}

	DecentEngine::RendererDefault::end();
	DecentEngine::RendererDefault::beginShader(m_camera);

	fontRenderer.renderText(std::string("Score: ") + std::to_string(m_score), glm::vec2(5.f, 768 - 37), glm::vec2(1.f), glm::uvec4(255));

	DecentEngine::RendererDefault::endShader();
}
