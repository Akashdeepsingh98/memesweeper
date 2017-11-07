#pragma once
#include "Vei2.h"
#include "Graphics.h"
class Minefield
{
private:
	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed
		};
	private:
		State state = State::Hidden;
		bool hasMine = false;
		Vei2 GridToScreen(Vei2& gridPos);
	public:
		bool HasMine();
		void SpawnMine();
		void Draw(Graphics& gfx,Vei2& gridPos);
	};
private:
	static constexpr int width = 20;
	static constexpr int height = 16;
	Tile field[ width * height ];
public:
	Minefield(int nMines);
	Tile& TileAt(const Vei2& gridPos);
	void Draw(Graphics& gfx);
};