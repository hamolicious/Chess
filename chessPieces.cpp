#include "olcPixelGameEngine.h"

class ChessPiece
{
public:
	olc::vi2d vPos;
	olc::vi2d vSpritePos;
	olc::vi2d vSize = {64, 64};

	std::unique_ptr<olc::Sprite> sprSprite;

	bool bHasMoved = false;

public:
	ChessPiece()
	{
		vPos = {0, 0};
		vSpritePos = {0, 0};

		LoadSprite();
	}

	ChessPiece(olc::vi2d vPos_)
	{
		vPos = vPos_;

		LoadSprite();
	}

	ChessPiece(olc::vi2d vPos_, bool bIsBlack, int iPieceIndex)
	{
		vPos = vPos_;
		vSpritePos = {iPieceIndex, (int)bIsBlack};

		LoadSprite();
	}


	bool IsSelected(olc::vi2d vMousePos, bool bRightMousePress)
	{
		return (vMousePos.x > vPos.x && vMousePos.x < (vPos.x + vSize.x) && vMousePos.y > vPos.y && vMousePos.y < (vPos.y + vSize.y) && bRightMousePress == true);
	}

	void SnapToGrid()
	{
		int iXPos = ((vPos.x + (vSize.x / 2)) % vSize.x);
		int iYPos = ((vPos.y + (vSize.y / 2)) % vSize.y);

		if (iXPos != 0)
		{
			vPos.x -= iXPos - (vSize.x / 2);
			vPos.y -= iYPos - (vSize.y / 2);
		}
	}

	void LoadSprite()
	{
		sprSprite = std::make_unique<olc::Sprite>("./assets/chess-pieces.png");
	}
};

class Pawn : public ChessPiece
{
	using ChessPiece::ChessPiece;
};

class Rook : public ChessPiece
{
	using ChessPiece::ChessPiece;
};

class Knight : public ChessPiece
{
	using ChessPiece::ChessPiece;
};

class Bishop : public ChessPiece
{
	using ChessPiece::ChessPiece;
};

class King : public ChessPiece
{
	using ChessPiece::ChessPiece;
};

class Queen : public ChessPiece
{
	using ChessPiece::ChessPiece;
};
