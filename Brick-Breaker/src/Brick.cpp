#include "Brick.h"

#include <ctime>

#include <Engine/RendererDefault.h>

std::mt19937 Brick::m_engine(time(0));

Brick::Brick(const glm::vec2& position){
	object.init(position, glm::vec2(51.2f, 20.f), 0.f, "assets/textures/brick.png");
	static glm::uvec4 colors[7] = {
		glm::uvec4(255, 0, 0, 255),
		glm::uvec4(255, 128, 0, 255),
		glm::uvec4(255, 255, 0, 255),
		glm::uvec4(0, 255, 0, 255),
		glm::uvec4(0, 128, 255, 255),
		glm::uvec4(0, 0, 255, 255),
		glm::uvec4(128, 0, 255, 255)
	};

	std::uniform_int_distribution<int> s_color(0, 6);
	object.sprite.color = colors[s_color(m_engine)];
}

Brick::~Brick(){

}

void Brick::render(){
	DecentEngine::RendererDefault::addObject(&object);
}
