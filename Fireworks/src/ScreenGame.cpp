#include "ScreenGame.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>
#include <Engine/RendererDefault.h>
#include <Engine/TextureCache.h>
#include <Engine/GuiManager.h>
#include <Engine/ParticleEngine.h>

#include "ParticleSnow.h"

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

	std::uniform_real_distribution<float> x(0.f, 1024.f);
	std::uniform_real_distribution<float> size(5.f, 10.f);
	DecentEngine::ParticleEngine::addParticle(new ParticleSnow(x(m_engine), size(m_engine)));
	DecentEngine::ParticleEngine::addParticle(new ParticleSnow(x(m_engine), size(m_engine)));
	DecentEngine::ParticleEngine::addParticle(new ParticleSnow(x(m_engine), size(m_engine)));
	DecentEngine::ParticleEngine::addParticle(new ParticleSnow(x(m_engine), size(m_engine)));
}
void ScreenGame::render(){
}
