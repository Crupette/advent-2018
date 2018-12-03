#include "Snowflake.h"

#include <ctime>

#include <Engine/RendererDefault.h>

std::mt19937 Snowflake::m_engine(time(0));

Snowflake::Snowflake(){
	std::uniform_real_distribution<float> posx(50.f, 1024.f - 60.f);
	std::uniform_real_distribution<float> size(40.f, 80.f);
	std::uniform_real_distribution<float> rot(-90.f, 90.f);

	object.init(glm::vec2(posx(m_engine), 1014.f), glm::vec2(size(m_engine)), glm::vec2(0.f, -100.f), rot(m_engine), rot(m_engine), "assets/textures/snowflake.png"); 
}

Snowflake::~Snowflake(){

}

bool Snowflake::update(){
	if(object.getPosition().y <= 0.f){
		return true;
	}
	object.update();
	return false;
}

void Snowflake::render(){
	DecentEngine::RendererDefault::addObject(&object);
}
