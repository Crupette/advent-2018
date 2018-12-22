#include "Tile.h"

#include <Engine/RendererDefault.h>

Tile::Tile(glm::uvec2 position, bool usable) : usable(usable) {
	sprite.init(glm::vec2(position.x * 64, position.y * 64), glm::vec2(64), 0.f, glm::uvec4(128, 64, 0, 255), "blank");
	if(!usable){
		sprite.color = glm::uvec4(255);	
	}
}

Tile::~Tile(){

}

void Tile::render(){
	DecentEngine::RendererDefault::addSprite(&sprite);
}
