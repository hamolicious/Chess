#include "olcPixelGameEngine.h"


class ChessPiece : public olc::PixelGameEngine
{
	public:
		olc::vi2d vPos;
		olc::vi2d vSpritePos;
		std::unique_ptr<olc::Sprite> sprSprite;

	public:
		ChessPiece(int x, int y)
		{
			vPos = {x, y};

			LoadSprite();
		}
		ChessPiece()
		{
			vPos = {0, 0};
			vSpritePos = {0, 0};

			LoadSprite();
		}

		void UpdatePosition(olc::vi2d vMousePos, bool bRighMousePress)
		{
			if (vMousePos.x > vPos.x && vMousePos.x < (vPos.x + 64) && vMousePos.y > vPos.y && vMousePos.y < (vPos.y + 64)) // && bRighMousePress == true
			{
				vPos.x = vMousePos.x;
				vPos.y = vMousePos.y;
			}
		}

	private:
		void LoadSprite()
		{
			sprSprite = std::make_unique<olc::Sprite>("./assets/chess-pieces.png");
		}
};




