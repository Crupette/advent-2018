#include "Piece.h"

#include <Engine/RendererDefault.h>

Piece::Piece(glm::uvec2 position, bool player) : position(position), player(player){
	object.init(glm::vec2(position) * glm::vec2(64), glm::vec2(64), 0.f, player ? "assets/textures/red.png" : "assets/textures/black.png");
}

Piece::~Piece(){

}

void Piece::render(){
	DecentEngine::RendererDefault::addObject(&object);
}
