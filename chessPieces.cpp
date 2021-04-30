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

	ChessPiece(olc::vi2d vPos_, bool bIsBlack, int iPieceIndex)
	{
		vPos = vPos_;
		vSpritePos = {iPieceIndex, (int)bIsBlack};

		LoadSprite();
	}

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

	void Display(olc::PixelGameEngine *pge)
	{
		pge->DrawPartialSprite(vPos, sprSprite.get(), vSpritePos * vSize, olc::vi2d(1, 1) * vSize);
	}

	void DisplayMoves(olc::PixelGameEngine *pge, olc::vi2d vMousePos)
	{
		pge->FillCircle(vPos + (vSize / 2), 8, olc::WHITE);
	}
};

class Pawn : public ChessPiece
{
public:
	Pawn(olc::vi2d vPos_, bool bIsBlack, int iPieceIndex) : ChessPiece(vPos_, bIsBlack, iPieceIndex) {}

	void DisplayMoves(olc::PixelGameEngine *pge, olc::vi2d vMousePos)
	{
		pge->FillCircle(vPos + (vSize / 2), 8, olc::RED);
	}
};

class Rook : public ChessPiece
{
public:
	Rook(olc::vi2d vPos_, bool bIsBlack, int iPieceIndex) : ChessPiece(vPos_, bIsBlack, iPieceIndex) {}
};

class Knight : public ChessPiece
{
public:
	Knight(olc::vi2d vPos_, bool bIsBlack, int iPieceIndex) : ChessPiece(vPos_, bIsBlack, iPieceIndex) {}
};

class Bishop : public ChessPiece
{
public:
	Bishop(olc::vi2d vPos_, bool bIsBlack, int iPieceIndex) : ChessPiece(vPos_, bIsBlack, iPieceIndex) {}
};

class King : public ChessPiece
{
public:
	King(olc::vi2d vPos_, bool bIsBlack, int iPieceIndex) : ChessPiece(vPos_, bIsBlack, iPieceIndex) {}
};

class Queen : public ChessPiece
{
public:
	Queen(olc::vi2d vPos_, bool bIsBlack, int iPieceIndex) : ChessPiece(vPos_, bIsBlack, iPieceIndex) {}
};
