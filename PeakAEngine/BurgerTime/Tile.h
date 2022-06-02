#pragma once

enum class TileType
{
	Platform = 0,
	Ladder = 1,
	Empty = 2
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

