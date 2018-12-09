#include "Tree.h"

#include <Engine/RendererDefault.h>

Tree::Tree(glm::vec2 position){
	object.init(position, glm::vec2(128.f), 0.f, "assets/textures/tree.png");
}

Tree::~Tree(){

}

void Tree::render(){
	DecentEngine::RendererDefault::addObject(&object);
}
