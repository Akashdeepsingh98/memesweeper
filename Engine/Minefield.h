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
	public:
		void Reveal();
		bool HasMine();
		void SpawnMine();
		Vei2 GridToScreen(Vei2& gridPos)const;
		void Draw(Graphics& gfx,Vei2& gridPos)const;
	};
private:
	static constexpr int width = 20;
	static constexpr int height = 16;
	Tile field[ width * height ];
	Vei2 ScreenToGrid(const Vei2& screenPos)const;
public:
	Minefield(int nMines);
	Tile& TileAt(const Vei2& gridPos);
	const Tile& TileAt(const Vei2& gridPos)const;
	void Draw(Graphics& gfx)const;
	void ClickReveal(const Vei2& screenPos);
	RectI GetRect();
};