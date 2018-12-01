#include "Grid.h"

Grid::Grid() : m_needsUpdate(true), m_engine(time(0)){

}

Grid::~Grid(){

}

void Grid::init(int numBombs){
	m_batch.init();
	std::uniform_int_distribution<int> chance(numBombs, 100);

	for(size_t y = 0; y < GRID_SIZE; y++)
	for(size_t x = 0; x < GRID_SIZE; x++){
		if(chance(m_engine) == 100){
			m_blocks[x+y*GRID_SIZE].bomb = true;
		}
	}
}

void Grid::destroy(){
	m_batch.destroy();
}

void Grid::update(){

	static GLuint tex_block = DecentEngine::TextureCache::getTexture("assets/textures/block.png");
	static GLuint tex_block_flag = DecentEngine::TextureCache::getTexture("assets/textures/block-flag.png");
	static GLuint tex_clicked[9] = 
	{
		DecentEngine::TextureCache::getTexture("assets/textures/block-clicked.png"),
		DecentEngine::TextureCache::getTexture("assets/textures/block-clicked-1.png"),
		DecentEngine::TextureCache::getTexture("assets/textures/block-clicked-2.png"),
		DecentEngine::TextureCache::getTexture("assets/textures/block-clicked-3.png"),
		DecentEngine::TextureCache::getTexture("assets/textures/block-clicked-4.png"),
		DecentEngine::TextureCache::getTexture("assets/textures/block-clicked-5.png"),
		DecentEngine::TextureCache::getTexture("assets/textures/block-clicked-6.png"),
		DecentEngine::TextureCache::getTexture("assets/textures/block-clicked-7.png"),	
		DecentEngine::TextureCache::getTexture("assets/textures/block-clicked-8.png"),

	};
	static GLuint tex_clicked_bomb = DecentEngine::TextureCache::getTexture("assets/textures/block-clicked-bomb.png");

	if(m_needsUpdate){
		m_batch.begin();

		for(size_t y = 0; y < GRID_SIZE; y++)
		for(size_t x = 0; x < GRID_SIZE; x++){
			size_t index = x + y * GRID_SIZE;
			if(m_blocks[index].clicked){
				if(m_blocks[index].bomb){
					m_batch.addSprite(glm::vec4(x * (800 / GRID_SIZE), y * (800 / GRID_SIZE), 800 / GRID_SIZE, 800 / GRID_SIZE), glm::vec4(0, 0, 1, 1), glm::uvec4(255), 0.f, 0, tex_clicked_bomb);
				}else{
					m_batch.addSprite(glm::vec4(x * (800 / GRID_SIZE), y * (800 / GRID_SIZE), 800 / GRID_SIZE, 800 / GRID_SIZE), glm::vec4(0, 0, 1, 1), glm::uvec4(255), 0.f, 0, tex_clicked[bombAdjacent(x, y)]);
				}
			}else{
				if(m_blocks[index].flagged){
					m_batch.addSprite(glm::vec4(x * (800 / GRID_SIZE), y * (800 / GRID_SIZE), 800 / GRID_SIZE, 800 / GRID_SIZE), glm::vec4(0, 0, 1, 1), glm::uvec4(255), 0.f, 0, tex_block_flag);

				}else{
					m_batch.addSprite(glm::vec4(x * (800 / GRID_SIZE), y * (800 / GRID_SIZE), 800 / GRID_SIZE, 800 / GRID_SIZE), glm::vec4(0, 0, 1, 1), glm::uvec4(255), 0.f, 0, tex_block);
				}
			}
		}
		m_needsUpdate = false;
		m_batch.end();
	}
}

void Grid::render(){
	m_batch.renderBatches();
}

bool Grid::clickBlock(uint8_t x, uint8_t y){
	size_t index = x + y * GRID_SIZE;
	if(x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE) return false;
	if(m_blocks[index].clicked) return false;
	m_needsUpdate = true;
	m_blocks[index].clicked = true;
	if(m_blocks[index].bomb){
		return true;	
	}

	if(bombAdjacent(x, y) > 0) return false;

	bool result = false;

	if(testBlock(x+1, y)) result = result ? true : clickBlock(x+1, y);
	if(testBlock(x-1, y)) result = result ? true : clickBlock(x-1, y);
	if(testBlock(x, y+1)) result = result ? true : clickBlock(x, y+1);
	if(testBlock(x, y-1)) result = result ? true : clickBlock(x, y-1);

	return result;
}

void Grid::flagBlock(uint8_t x, uint8_t y){
	size_t index = x + y * GRID_SIZE;
	if(x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE) return;
	if(m_blocks[index].clicked || m_blocks[index].flagged) return;
	m_needsUpdate = true;
	m_blocks[index].flagged = !m_blocks[index].flagged;
	if(m_blocks[index].bomb){
		m_remainingBombs += m_blocks[index].flagged ? -1 : 1;
	}
}

int Grid::bombAdjacent(uint8_t x, uint8_t y){
	int adjacent = 0;
	
	for(int ny = y - 1; ny < y + 2; ny++)
	for(int nx = x - 1; nx < x + 2; nx++){
		if(nx == x && ny == y) continue;
		if(nx < 0 || nx >= GRID_SIZE || ny < 0 || ny >= GRID_SIZE) continue;
		if(m_blocks[nx + ny * GRID_SIZE].bomb) adjacent++;
	}
	return adjacent;
}

bool Grid::testBlock(uint8_t x, uint8_t y){
	size_t index = x+y*GRID_SIZE;
	if(m_blocks[index].bomb) return false;
	return true;
}
