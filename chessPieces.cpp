#include "olcPixelGameEngine.h"


class ChessPiece
{
	public:
		olc::vi2d vPos;
		olc::vi2d vSpritePos;
		std::unique_ptr<olc::Sprite> sprSprite;

		olc::vi2d vSize;

	public:
		ChessPiece()
		{
			vPos = {0, 0};
			vSpritePos = {0, 0};
			vSize = {64, 64};

			LoadSprite();
		}

		void UpdatePosition(olc::vi2d vMousePos, bool bRightMousePress)
		{
			if (vMousePos.x > vPos.x && vMousePos.x < (vPos.x + vSize.x) && vMousePos.y > vPos.y && vMousePos.y < (vPos.y + vSize.y) && bRightMousePress == true)
			{
				vPos.x = vMousePos.x - (vSize.x / 2);
				vPos.y = vMousePos.y - (vSize.y / 2);
			}

			if (!bRightMousePress)
			{
				int iXPos = ((vPos.x + (vSize.x / 2)) % vSize.x);
				int iYPos = ((vPos.y + (vSize.y / 2)) % vSize.y);

				if (iXPos != 0)
				{
					vPos.x -= iXPos - (vSize.x / 2);
					vPos.y -= iYPos - (vSize.y / 2);
				}
			}
		}

	private:
		void LoadSprite()
		{
			sprSprite = std::make_unique<olc::Sprite>("./assets/chess-pieces.png");
		}
};




