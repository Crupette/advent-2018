#include "ScreenGame.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>
#include <Engine/RendererDefault.h>
#include <Engine/TextureCache.h>
#include <Engine/GuiManager.h>

#include "GuiHud.h"

DecentEngine::FontRenderer ScreenGame::fontRenderer;

ScreenGame::ScreenGame() : m_engine(time(0)){

}
ScreenGame::~ScreenGame(){

}
void ScreenGame::init(){
	m_camera.init(glm::vec2(0.f, 0.f), 1.f, 0.f); 
	fontRenderer.init("assets/fonts/Vera.ttf", 32);

	glClearColor(0.9f, 0.9f, 0.9f, 1.f);

	m_player.init();
	
	std::uniform_int_distribution<int> chance(-2000, 2000);
	for(size_t i = 0; i < 5; i++){
		m_trees.emplace_back(glm::vec2(chance(m_engine), chance(m_engine)));
	}
	m_children.emplace_back(glm::vec2(chance(m_engine), chance(m_engine)));

	DecentEngine::GuiManager::addGui("hud", new GuiHud());
}
void ScreenGame::destroy() {
	fontRenderer.destroy();
}
void ScreenGame::update(){
	if(m_loss) return;
	m_player.update();
	m_camera.setPosition(m_player.object.getPosition());
	m_camera.update(DecentEngine::Base::getWindow());
	
	bool allfull = true;

	for(Child& child : m_children){
		Tree* nearestTree;
		double distance = 10000.0;
		for(Tree& tree : m_trees){
			double cdist = std::sqrt(std::pow(tree.object.getPosition().x - child.object.getPosition().x, 2) + std::pow(tree.object.getPosition().y - child.object.getPosition().y, 2));
			if(cdist < distance || tree.full){
				nearestTree = &tree;
				distance = cdist;
				if(nearestTree->full) break;
			}
		}
		if(!child.presents) allfull = false;
		child.update(m_player.object.getPosition(), nearestTree->object.getPosition(), nearestTree->full);
		if(DecentEngine::AABB::checkRect(nearestTree->object.aabb, m_player.object.aabb)){
			if(nearestTree->full && !child.presents){
				nearestTree->presents--;
				child.presents = true;
			}
		}
		if(DecentEngine::AABB::checkRect(m_player.object.aabb, child.object.aabb)){
			m_loss = true;
		}
	}

	for(Tree& tree : m_trees){
		if(DecentEngine::InputManager::isKeyPressed(SDLK_SPACE) && !tree.full){
			if(DecentEngine::AABB::checkRect(tree.object.aabb, m_player.object.aabb)){
				tree.presents++;
				printf("Tree presents: %i\n", tree.presents);
				if(tree.presents >= 50) tree.full = true;
			}
		}
		if(allfull){
			tree.full = false;
			tree.presents = 0;
			for(Child& child : m_children){
				child.presents = false;
			}
		}
	}
	if(allfull){
		std::uniform_int_distribution<int> chance(-2000, 2000);
		m_children.emplace_back(glm::vec2(chance(m_engine), chance(m_engine)));
	}
}
void ScreenGame::render(){
	DecentEngine::RendererDefault::begin(m_camera);

	m_player.render();

	for(Tree& tree : m_trees){
		tree.render();
	}
	for(Child& child : m_children){
		child.render();
	}

	DecentEngine::RendererDefault::end();
	DecentEngine::RendererDefault::beginShader(m_camera);

	DecentEngine::RendererDefault::endShader();
}

double ScreenGame::treeDistance(){
	glm::vec2 nearestTree;
	double distance = 10000.0;
	for(Tree& tree : m_trees){
		double cdist = std::sqrt(std::pow(tree.object.getPosition().x - m_player.object.getPosition().x, 2) + std::pow(tree.object.getPosition().y - m_player.object.getPosition().y, 2));
		if(cdist < distance && !tree.full){
			nearestTree = tree.object.getPosition();
			distance = cdist;
		}
	}
	return distance;
}
