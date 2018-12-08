#include "Present.h"

#include <ctime>

#include <Engine/RendererDefault.h>

std::mt19937 Present::m_engine(time(0));

Present::Present(glm::vec2 position){
	object.init(position, glm::vec2(24.f), glm::vec2(0.f, 768.f), 180.f, 180.f, "assets/textures/present.png");
	static glm::uvec4 colors[7] {
		glm::uvec4(255, 0, 0, 255),
		glm::uvec4(255, 128, 0, 255),
		glm::uvec4(255, 255, 0, 255),
		glm::uvec4(0, 255, 0, 255),
		glm::uvec4(0, 128, 255, 255),
		glm::uvec4(0, 0, 255, 255),
		glm::uvec4(128, 0, 255, 255)
	};
	std::uniform_int_distribution<int> color(0, 6);
	object.sprite.color = colors[color(m_engine)];
}

Present::~Present(){

}

void Present::update(){
	object.update();
}

void Present::render(){
	DecentEngine::RendererDefault::addObject(&object);
}
