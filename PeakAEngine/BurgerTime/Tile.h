#pragma once

enum class TileType
{
	Empty = 0,
	Platform = 1,
	Ladder = 2,
	BurgerIngredient = 3,
	BurgerCatcher = 4
};

class Tile
{
public:
	Tile() = default;
	~Tile() = default;
	Tile(const Tile& other) = delete;
	Tile(Tile&& other) noexcept = delete;
	Tile& operator=(const Tile& other) = delete;
	Tile& operator=(Tile&& other) noexcept = delete;

private:
	TileType m_pTileType;
};

