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
	m_camera.init(glm::vec2(1024.f / 2.f, 1024.f / 2.f), 1.f, 0.f); 
	fontRenderer.init("assets/fonts/Vera.ttf", 32);
	m_audioManager.init();

	glClearColor(0.f, 0.f, 0.f, 1.f);
	DecentEngine::Base::getWindow()->setIcon("assets/textures/piece.png");
	
	DecentEngine::ParticleEngine::useCamera(&m_camera);

	std::string characters = "capthoadfrrlgefedgcmhaoerhrilrarcgfnalmnieisyinegatyabnerzhwsldemmajpkermytnoqtvtsasssgdmnqhjopqwxn";
	for(int y = 0; y < 10; y++)
	for(int x = 0; x < 10; x++){
		if(x == 0 && y == 0){
			m_pieces.emplace_back(glm::uvec2(0), ' ');
			m_pieces.back().exists = false;
		}else{
			size_t index = x + y * 10;
			m_pieces.emplace_back(glm::uvec2(x, y), characters[index-1]);
		}
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
		mousepos.y = 1024 - mousepos.y;
		for(Piece& piece : m_pieces){
			if(piece.animating || !piece.exists) continue;
			glm::vec2 piecepos = piece.object.getPosition();
			glm::uvec2 cache = piece.tilePosition;
			if(mousepos.x > piecepos.x && mousepos.x < piecepos.x + 102.4f && mousepos.y > piecepos.y && mousepos.y < piecepos.y + 102.4f){
				Piece* px = getPiece(piece.tilePosition.x + 1, piece.tilePosition.y);
				Piece* nx = getPiece(piece.tilePosition.x - 1, piece.tilePosition.y);
				Piece* py = getPiece(piece.tilePosition.x, piece.tilePosition.y + 1);
				Piece* ny = getPiece(piece.tilePosition.x, piece.tilePosition.y - 1);
				if(px != nullptr){
					if(!px->exists){
						piece.moveTo(px->tilePosition);
						px->moveTo(cache);
						printf("Moving right\n");
					}
				}
				if(py != nullptr){
					if(!py->exists){
						piece.moveTo(py->tilePosition);
						py->moveTo(cache);
						printf("Moving up\n");
					}
				}
				if(ny != nullptr){
					if(!ny->exists){
						piece.moveTo(ny->tilePosition);
						ny->moveTo(cache);
						printf("Moving down\n");
					}
				}
				if(nx != nullptr){
					if(!nx->exists){
						piece.moveTo(nx->tilePosition);
						nx->moveTo(cache);
						printf("Moving left\n");
					}
				}
				printf("Clicked on\n");
				return;
			}
		}
	}

	for(Piece& piece : m_pieces){
		piece.update();
	}
}
void ScreenGame::render(){
	DecentEngine::RendererDefault::begin(m_camera);

	for(Piece& piece : m_pieces){
		if(!piece.exists) continue;
		piece.render();
	}

	DecentEngine::RendererDefault::end();
	DecentEngine::RendererDefault::beginShader(m_camera);

	for(Piece& piece : m_pieces){
		if(!piece.exists) continue;
		piece.renderText();
	}

	DecentEngine::RendererDefault::endShader();
}

Piece* ScreenGame::getPiece(int x, int y){
	if(x < 0 || x >= 10 || y < 0 || y >= 10) return nullptr;
	for(Piece& piece : m_pieces){
		if(piece.tilePosition.x == x && piece.tilePosition.y == y){
			return &piece;
		}
	}
	printf("Returning nullptr\n");
	return nullptr;
}
