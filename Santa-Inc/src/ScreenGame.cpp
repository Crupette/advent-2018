#include "ScreenGame.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>
#include <Engine/RendererDefault.h>
#include <Engine/TextureCache.h>
#include <Engine/GuiManager.h>
#include <Engine/ParticleEngine.h>

DecentEngine::FontRenderer ScreenGame::fontRenderer;
int ScreenGame::m_score = 0;

ScreenGame::ScreenGame() : m_engine(time(0)){

}
ScreenGame::~ScreenGame(){

}
void ScreenGame::init(){
	m_camera.init(glm::vec2(1024.f / 2.f, 768.f / 2.f), 1.f, 0.f); 
	glClearColor(0.1f, 0.1f, 0.2f, 1.f);
	fontRenderer.init("assets/fonts/Vera.ttf", 32);
	m_audioManager.init();

	DecentEngine::ParticleEngine::useCamera(&m_camera);

	m_background.init(glm::vec2(0), glm::vec2(1024, 768), 0.f, glm::uvec4(255), "assets/textures/background.png");
	m_requested = 0;

	m_audioManager.getSound("assets/sounds/conveyor.ogg").begin(-1);
}
void ScreenGame::destroy() {
}
void ScreenGame::update(){
	m_camera.update(DecentEngine::Base::getWindow());
	if(m_loss) return;
	m_timer += DecentEngine::FPSRegulator::getDelta() + (0.1f * (m_score / 100.f));
	if(m_timer >= 1.f){
		m_timer = 0.f;
		std::uniform_int_distribution<int> id(0, 5);
		m_presents.emplace_back(id(m_engine));
		m_audioManager.getSound("assets/sounds/machine.ogg").begin();
	}

	for(size_t i = 0; i < m_presents.size(); i++){
		m_presents[i].update();
		if(DecentEngine::InputManager::isKeyPressed(SDL_BUTTON_LEFT)){
			glm::uvec2 mousepos = DecentEngine::InputManager::getMousePosition();
			glm::vec2 newmpos = glm::vec2(mousepos.x, 768 - mousepos.y);
			glm::vec4 bounds = m_presents[i].object.aabb.getBounds();
			if(newmpos.x > bounds.x && newmpos.x < bounds.x + bounds.z && newmpos.y > bounds.y && newmpos.y < bounds.y + bounds.w){
				m_presents[i].clicked = true;
				m_presents[i].object.translateVelocity(glm::vec2(0.f, 1000.f));
				if(m_presents[i].id == m_requested){
					m_score++;
					m_audioManager.getSound("assets/sounds/good.ogg").begin();
				}else{
					m_chances--;
					if(m_chances <= 0){
						m_loss = true;
					}
					m_audioManager.getSound("assets/sounds/bad.ogg").begin();
				}
				std::uniform_int_distribution<int> request(0, 5);
				m_requested = request(m_engine);
			}
		}
		if(m_presents[i].object.getPosition().x > 1124.f){
			m_presents.erase(m_presents.begin() + i);
		}
	}
}
void ScreenGame::render(){
	DecentEngine::RendererDefault::begin(m_camera);

	DecentEngine::RendererDefault::addSprite(&m_background);

	for(Present& present : m_presents){
		present.render();
	}

	DecentEngine::RendererDefault::end();
	DecentEngine::RendererDefault::beginShader(m_camera);

	std::string reads[6] = {
		"For Christmas, I want a Car!",
		"I dont know, money I guess?",
		"A singular BRI",
		"I never get to see the snow",
		"One day, I want to be Santa!",
		"I dont know, Suprise me!"
	};

	fontRenderer.renderText(reads[m_requested], glm::vec2(200, 768 - 320), glm::vec2(1.f), glm::uvec4(0x5d, 0x5d, 0x9d, 0xff));
	fontRenderer.renderText(std::string("Chances Left: ") + std::to_string(m_chances), glm::vec2(200, 768 - 352), glm::vec2(1.f), glm::uvec4(0xad, 0x2d, 0x2d, 0xff));
	fontRenderer.renderText(std::string("Score: ") + std::to_string(m_score), glm::vec2(5, 768 - 37), glm::vec2(1.f), glm::uvec4(255));

	DecentEngine::RendererDefault::endShader();
}
