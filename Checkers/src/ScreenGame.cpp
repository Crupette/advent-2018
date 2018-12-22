#include "ScreenGame.h"

#include <Engine/Base.h>
#include <Engine/InputManager.h>
#include <Engine/FPSRegulator.h>
#include <Engine/RendererDefault.h>
#include <Engine/TextureCache.h>
#include <Engine/GuiManager.h>
#include <Engine/ParticleEngine.h>

DecentEngine::FontRenderer ScreenGame::fontRenderer;

ScreenGame::ScreenGame() : m_engine(time(0)){

}
ScreenGame::~ScreenGame(){

}
void ScreenGame::init(){
	m_camera.init(glm::vec2(512.f / 2.f, 544.f / 2.f), 1.f, 0.f);
	DecentEngine::ParticleEngine::useCamera(&m_camera);
	fontRenderer.init("assets/fonts/Vera.ttf", 32);
	m_audioManager.init();

	glClearColor(0.f, 0.f, 0.f, 1.f);
	DecentEngine::Base::getWindow()->setIcon("assets/textures/red.png");
	
	for(size_t y = 0; y < 8; y++)
	for(size_t x = 0; x < 8; x++){
		size_t index = x + y * 8;
		bool usable = true;
		if((index+y) % 2 == 0){
			usable = false;
		}else{
			if(y < 3 || y >= 5){
				m_pieces.emplace_back(glm::uvec2(x, y), y >= 5);
			}
		}
		m_tiles.emplace_back(glm::uvec2(x, y), usable);
	}
}
void ScreenGame::destroy() {
	fontRenderer.destroy();
	m_audioManager.destroy();
}
void ScreenGame::update(){
	m_camera.update(DecentEngine::Base::getWindow());

	if(DecentEngine::InputManager::isKeyPressed(SDL_BUTTON_LEFT)){
		glm::uvec2 mousepos = DecentEngine::InputManager::getMousePosition();
		mousepos.y = 544-mousepos.y;
		glm::uvec2 tilepos = mousepos / glm::uvec2(64);
		for(size_t i = 0; i < m_pieces.size(); i++){
			Piece* piece = &m_pieces[i];
			if(piece->position == tilepos){
				if(piece->player == m_player){
					m_selected = piece;
					return;
				}else{
					m_pieces.erase(m_pieces.begin() + i);
					return;
				}
			}
		}
		if(m_selected == nullptr) return;
		if(positionValid(tilepos) && m_moved == false){
			m_selected->position = tilepos;
			m_selected->object.setPosition(glm::vec2(tilepos) * glm::vec2(64));
			m_selected->object.update();
			m_moved = true;
		}
	}
	if(DecentEngine::InputManager::isKeyPressed(SDLK_ESCAPE)){
		if(m_moved){
			m_selected = nullptr;
			m_player = !m_player;
			m_moved = false;
		}
	}
}
void ScreenGame::render(){
	DecentEngine::RendererDefault::begin(m_camera);

	for(Tile& tile : m_tiles){
		tile.render();
	}
	for(Piece& piece : m_pieces){
		piece.render();
	}

	DecentEngine::RendererDefault::end();
	DecentEngine::RendererDefault::beginShader(m_camera);

	fontRenderer.renderText(std::string("Current player: ") + (m_player ? std::string("RED") : std::string("BLACK")), glm::vec2(5.f, 512.f), glm::vec2(1), glm::uvec4(255));

	DecentEngine::RendererDefault::endShader();
}

bool ScreenGame::positionValid(glm::uvec2 position){
	if(position.x >= 8 || position.y >= 8) return false;
	int index = position.x + position.y * 8;
	if(!m_tiles[index].usable) return false;
	if(isPieceOn(position) != nullptr) return false;
	
	glm::ivec2 distance = glm::ivec2(m_selected->position) - glm::ivec2(position);
	if(std::abs(distance.x) + std::abs(distance.y) == 2){
		return true;
	}else{
		if(std::abs(distance.x) != std::abs(distance.y)) return false;
		printf("%i, %i\n", m_selected->position.x + (distance.x / 2), m_selected->position.y + (distance.y / 2));
		glm::ivec2 inbetween(m_selected->position.x + (distance.x / 2), m_selected->position.y + (distance.y / 2));
		return isPieceOn(inbetween) != nullptr;
	}
}

Piece* ScreenGame::isPieceOn(glm::uvec2 position){
	for(Piece& piece : m_pieces){
		if(piece.position == position) return &piece;
	}
	return nullptr;
}

bool ScreenGame::piecesAdjacent(glm::uvec2 position){
	if(isPieceOn(glm::uvec2(position.x + 1, position.y + 1)) != nullptr ||
	   isPieceOn(glm::uvec2(position.x - 1, position.y + 1)) != nullptr ||
	   isPieceOn(glm::uvec2(position.x + 1, position.y - 1)) != nullptr ||
	   isPieceOn(glm::uvec2(position.x - 1, position.y - 1)) != nullptr ){
		return true;
	}
	return false;
}
