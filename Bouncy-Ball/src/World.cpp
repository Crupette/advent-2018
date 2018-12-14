#include "World.h"

#include <Engine/RendererDefault.h>

#include <ctime>

std::vector<DecentEngine::Object> World::terrain;

std::mt19937 World::m_engine(time(0));

void World::init(){
	std::uniform_int_distribution<int> height(50, 300);
	for(int x = -10; x < 10; x++){
		terrain.push_back(DecentEngine::Object());
		terrain.back().init(glm::vec2(x * 128.f, 0.f), glm::vec2(128.f, height(m_engine)), 0.f, "blank");
		terrain.back().sprite.color = glm::uvec4(0, 0, 0, 255);
	}
}

void World::destroy(){

}

void World::update(glm::vec2 playerPosition){
	glm::ivec2 intpos = (glm::ivec2)(playerPosition);
	glm::ivec2 tilepos = intpos / glm::ivec2(128.f);

	std::uniform_int_distribution<int> height(50, 300);

	for(int x = tilepos.x - 10; x < tilepos.x + 10; x++){
		bool exists = false;
		for(size_t i = 0; i < terrain.size(); i++){
			if(x == (int)terrain[i].getPosition().x / 128){
				exists = true;
				break;
			}
			if(terrain[i].getPosition().x < tilepos.x - 11){
				terrain.erase(terrain.begin() + i);
			}
		}
		if(!exists){
			terrain.push_back(DecentEngine::Object());
			terrain.back().init(glm::vec2(x * 128.f, 0.f), glm::vec2(128.f, height(m_engine)), 0.f, "blank");
			terrain.back().sprite.color = glm::uvec4(0, 0, 0, 255);
		}
	}
}

void World::render(){
	for(DecentEngine::Object& object : terrain){
		DecentEngine::RendererDefault::addObject(&object);
	}
}
