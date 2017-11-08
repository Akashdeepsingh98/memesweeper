#include "Minefield.h"
#include <random>
#include <assert.h>
#include "SpriteCodex.h"
Minefield::Minefield(int nMines)
{
	assert(nMines > 0 && nMines < width * height);
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);
	for (int minesSpawned = 0; minesSpawned < nMines; minesSpawned++)
	{
		Vei2 gridPos;
		do
		{
			gridPos = { xDist(rng) , yDist(rng) };
		} while (TileAt(gridPos).HasMine());
		TileAt(gridPos).SpawnMine();
	}
}

Minefield::Tile & Minefield::TileAt(const Vei2 & gridPos)
{
	return field[gridPos.y * width + gridPos.x];
}

const Minefield::Tile & Minefield::TileAt(const Vei2 & gridPos) const
{
	// TODO: insert return statement here
	return field[gridPos.y * width + gridPos.x];
}

void Minefield::Draw(Graphics & gfx)const
{
	for (Vei2 gridPos = { 0,0 }; gridPos.y < height; gridPos.y++)
	{
		for (gridPos.x = 0; gridPos.x < width; gridPos.x++)
		{
			TileAt(gridPos).Draw(gfx,gridPos);
		}
	}
}

void Minefield::ClickReveal(const Vei2 & screenPos)
{
	TileAt(ScreenToGrid(screenPos)).Reveal();
}

RectI Minefield::GetRect()
{
	return RectI(0,width*SpriteCodex::tileSize,0,height*SpriteCodex::tileSize);
}

Vei2 Minefield::Tile::GridToScreen(Vei2 & gridPos)const 
{
	return gridPos * SpriteCodex::tileSize;
}

Vei2 Minefield::ScreenToGrid(const Vei2 & screenPos) const
{
	return screenPos/SpriteCodex::tileSize;
}

void Minefield::Tile::Reveal()
{
	state = State::Revealed;
}

bool Minefield::Tile::HasMine()
{
	return hasMine;
}

void Minefield::Tile::SpawnMine()
{
	hasMine = true;
}

void Minefield::Tile::Draw(Graphics & gfx,Vei2& gridPos)const
{
	Vei2 screenPos = GridToScreen(gridPos);
	switch (state)
	{
	case State::Hidden:
		SpriteCodex::DrawTileButton(screenPos, gfx);
		break;
	case State::Flagged:
		SpriteCodex::DrawTile0(screenPos, gfx);
		SpriteCodex::DrawTileFlag(screenPos, gfx);
		break;
	case State::Revealed:
		if (hasMine)
		{
			SpriteCodex::DrawTileBomb(screenPos, gfx);
		}
		else
		{
			SpriteCodex::DrawTile0(screenPos, gfx);
		}
		break;
	default:
		break;
	}
}
