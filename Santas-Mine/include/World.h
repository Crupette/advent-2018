/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-5
 *	Engine Version:		0.4.3
 *	Compiler:		g++ -std=c++17
 * */

#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>
#include <vector>
#include <random>
#include <functional>

#include <Engine/SpriteBatch.h>
#include <Engine/AABB.h>

struct CoordsSort {
	size_t operator()(const glm::ivec2& k) const {
		return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
	}

	bool operator()(const glm::ivec2& a, const glm::ivec2& b) const {
		return a.x == b.x && a.y == b.y;
	}
};

typedef std::unordered_map<glm::ivec2, std::pair<bool, bool>, CoordsSort> TileMap;

class World {
	static TileMap m_tiles;
	static std::vector<DecentEngine::AABB> m_colliders;

	static DecentEngine::SpriteBatch m_batch;
	static bool m_update;

	static std::mt19937 m_engine;
public:
	static void init();
	static void destroy();

	static void update();
	static void render();

	static bool tileExists(int x, int y);
	static bool mineTile(int x, int y);
	static void createTile(int x, int y);

	static std::vector<DecentEngine::AABB> getColliders() { return m_colliders; }
};

#endif
