#include "World.h"

#include <Engine/TextureCache.h>

#include <ctime>
#include <utility>

TileMap World::m_tiles;
std::vector<DecentEngine::AABB> World::m_colliders;

DecentEngine::SpriteBatch World::m_batch;
bool World::m_update = true;

std::mt19937 World::m_engine(time(0));

void World::init(){
	m_batch.init();
	for(int i = -10; i < 11; i++){
		m_tiles.emplace(glm::vec2(i, 0), std::make_pair(true, false));
	}
}
void World::destroy(){
	m_batch.destroy();
}

void World::update(){
	if(m_update){
		m_colliders.clear();
		for(auto it = m_tiles.begin(); it != m_tiles.end(); it++){
			if(!it->second.first) continue;
			m_colliders.emplace_back(glm::vec4(it->first.x * 50.f, it->first.y * 50.f, 50.f, 50.f), 0.f);
		}
	}	
}
void World::render(){
	if(m_update){
		m_update = false;
		m_batch.begin();

		static GLuint tileTexture = DecentEngine::TextureCache::getTexture("assets/textures/tile.png");
		static GLuint goldTexture = DecentEngine::TextureCache::getTexture("assets/textures/gold.png");

		for(auto it = m_tiles.begin(); it != m_tiles.end(); it++){
			if(!it->second.first) continue;
			if(it->second.second){
				m_batch.addSprite(glm::vec4(it->first.x * 50.f, it->first.y * 50.f, 50.f, 50.f), glm::vec4(0, 0, 1, 1), glm::uvec4(255), 0.f, 0, tileTexture);
				m_batch.addSprite(glm::vec4(it->first.x * 50.f, it->first.y * 50.f, 50.f, 50.f), glm::vec4(0, 0, 1, 1), glm::uvec4(255), 0.f, 0, goldTexture);
			}else{
				m_batch.addSprite(glm::vec4(it->first.x * 50.f, it->first.y * 50.f, 50.f, 50.f), glm::vec4(0, 0, 1, 1), glm::uvec4(255), 0.f, 0, tileTexture);
			}
		}

		m_batch.end();
	}
	
	 m_batch.renderBatches();
}

bool World::tileExists(int x, int y){
	auto it = m_tiles.find(glm::vec2(x, y));
	return !(it == m_tiles.end());
}
bool World::mineTile(int x, int y){
	auto it = m_tiles.find(glm::vec2(x, y));
	bool gold = it->second.second;
	if(it->second.first == false) return false;
	it->second.first = false;
	if(y < 0) createTile(x, y+1);
	createTile(x, y-1);	
	createTile(x+1, y);
	createTile(x-1, y);
	m_update = true;
	return gold;
}
void World::createTile(int x, int y){
	auto it = m_tiles.find(glm::vec2(x, y));
	if(it != m_tiles.end()) return;
	std::uniform_int_distribution<int> chance(1, 5 - (y / 100));
	m_tiles.emplace(glm::vec2(x, y), std::make_pair(true, chance(m_engine) == 1 ? true : false));
}
