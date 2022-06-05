#pragma once

enum class TileType
{
	Empty = 0,
	Platform = 1,
	Ladder = 2,
	PlatformWithLadderUp = 3,
	PlatformWithLadderDown = 4,
	PlatformWithLadderBoth = 5,
	BurgerIngredient = 6,
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
	const TileType m_pTileType;
};

