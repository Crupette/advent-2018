#include "Present.h"
#include "ScreenGame.h"

#include <Engine/RendererDefault.h>

Present::Present(int id) : id(id){
	static std::string textures[6] = {
		"assets/textures/toy-1.png",
		"assets/textures/toy-2.png",
		"assets/textures/toy-3.png",
		"assets/textures/toy-4.png",
		"assets/textures/toy-5.png",
		"assets/textures/toy-6.png"
	};

	object.init(glm::vec2(-100, 100), glm::vec2(100.f), 0.f, textures[id]);
	object.setVelocity(glm::vec2(300 + (100 * (ScreenGame::m_score / 10.f)), 0));
}

Present::~Present(){

}

void Present::update(){
	object.update();
	if(clicked){
		object.translateVelocity(glm::vec2(0.f, -100.f));
	}
}

void Present::render(){
	DecentEngine::RendererDefault::addObject(&object);
}
