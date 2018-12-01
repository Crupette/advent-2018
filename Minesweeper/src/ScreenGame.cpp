#include "ScreenGame.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>

ScreenGame::ScreenGame() {

}
ScreenGame::~ScreenGame(){

}
void ScreenGame::init(){
	m_shader = new DecentEngine::ShaderHandler();

	m_shader->addShader(GL_VERTEX_SHADER, "assets/shaders/base.vert");
	m_shader->addShader(GL_FRAGMENT_SHADER, "assets/shaders/base.frag");

	m_shader->buildProgram();

	m_shader->addAttribute("position");
	m_shader->addAttribute("color");
	m_shader->addAttribute("uv");

	m_batch.init();

	m_camera.init(glm::vec2(800 / 2, 850 / 2), 1.f, 0.f);	

	m_fontRenderer.init("assets/fonts/Vera.ttf", 32);

	m_grid.init(90);
}
void ScreenGame::destroy() {
	m_batch.destroy();
	m_grid.destroy();

	delete m_shader;
}
void ScreenGame::update(){
	m_camera.update(DecentEngine::Base::getWindow());

	if(m_lossed) return;

	if(DecentEngine::InputManager::isKeyPressed(SDL_BUTTON_LEFT)){
		glm::uvec2 mousepos = DecentEngine::InputManager::getMousePosition();
		mousepos = glm::uvec2(mousepos.x, 850 - mousepos.y);
		mousepos /= glm::uvec2(800 / GRID_SIZE);
		if(m_grid.clickBlock(mousepos.x, mousepos.y)){
			m_lossed = true;
		}
	}

	if(DecentEngine::InputManager::isKeyPressed(SDL_BUTTON_RIGHT)){
		glm::uvec2 mousepos = DecentEngine::InputManager::getMousePosition();
		mousepos = glm::uvec2(mousepos.x, 850 - mousepos.y);
		mousepos /= glm::uvec2(800 / GRID_SIZE);
		m_grid.flagBlock(mousepos.x, mousepos.y);
	}

	m_grid.update();
}
void ScreenGame::render(){
	m_shader->use();

	m_camera.loadUniform(m_shader);
	glActiveTexture(GL_TEXTURE0);

	m_batch.begin();

	m_batch.end();
	m_batch.renderBatches();

	m_grid.render();
	if(m_lossed){
	m_fontRenderer.setText("You lost!", glm::vec2(700/2, 850-40), glm::vec2(1), glm::uvec4(255, 0, 0, 255));
	m_fontRenderer.render();
	}

	m_shader->unuse();
}
