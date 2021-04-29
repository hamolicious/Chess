#include "olcPixelGameEngine.h"

class ChessPiece
{
public:
	olc::vi2d vPos;
	olc::vi2d vSpritePos;
	std::unique_ptr<olc::Sprite> sprSprite;

	olc::vi2d vSize = {64, 64};

public:
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
public:
	Pawn(olc::vi2d vPos_, bool bBlack)
	{
		vPos = vPos_;
		vSpritePos = {0, (int)bBlack};

		LoadSprite();
	}
};

class Rook : public ChessPiece
{
public:
	Rook(olc::vi2d vPos_, bool bBlack)
	{
		vPos = vPos_;
		vSpritePos = {1, (int)bBlack};

		LoadSprite();
	}
};

class Knight : public ChessPiece
{
public:
	Knight(olc::vi2d vPos_, bool bBlack)
	{
		vPos = vPos_;
		vSpritePos = {2, (int)bBlack};

		LoadSprite();
	}
};

class Bishop : public ChessPiece
{
public:
	Bishop(olc::vi2d vPos_, bool bBlack)
	{
		vPos = vPos_;
		vSpritePos = {3, (int)bBlack};

		LoadSprite();
	}
};

class King : public ChessPiece
{
public:
	King(olc::vi2d vPos_, bool bBlack)
	{
		vPos = vPos_;
		vSpritePos = {4, (int)bBlack};

		LoadSprite();
	}
};

class Queen : public ChessPiece
{
public:
	Queen(olc::vi2d vPos_, bool bBlack)
	{
		vPos = vPos_;
		vSpritePos = {5, (int)bBlack};

		LoadSprite();
	}
};

