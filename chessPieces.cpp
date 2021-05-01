#include "olcPixelGameEngine.h"

class ChessPiece
{
public:
	olc::vi2d vPos;
	olc::vi2d vSpritePos;
	olc::vi2d vSize = {64, 64};

	std::string sOldPos = "";

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

		SavePos();
		LoadSprite();
	}

public:
	bool IsHovered(olc::vi2d vMousePos)
	{
		return (vMousePos.x > vPos.x && vMousePos.x < (vPos.x + vSize.x) && vMousePos.y > vPos.y && vMousePos.y < (vPos.y + vSize.y));
	}

	bool IsSelected(olc::vi2d vMousePos, bool bRightMousePress)
	{
		return (IsHovered(vMousePos) && bRightMousePress == true);
	}

	std::string PosToNotation()
	{
		int iFile = (vPos.x / vSize.x);
		int iRank = (vPos.y / vSize.y);

		std::string sFile = "";
		std::string sRank = "";

		switch (iFile)
		{
		case 0:
			sFile = "A";
			break;
		case 1:
			sFile = "B";
			break;
		case 2:
			sFile = "C";
			break;
		case 3:
			sFile = "D";
			break;
		case 4:
			sFile = "E";
			break;
		case 5:
			sFile = "F";
			break;
		case 6:
			sFile = "G";
			break;
		case 7:
			sFile = "H";
			break;
		}
		switch (iRank)
		{
		case 0:
			sRank = "1";
			break;
		case 1:
			sRank = "2";
			break;
		case 2:
			sRank = "3";
			break;
		case 3:
			sRank = "4";
			break;
		case 4:
			sRank = "5";
			break;
		case 5:
			sRank = "6";
			break;
		case 6:
			sRank = "7";
			break;
		case 7:
			sRank = "8";
			break;
		}

		std::string notation = sFile + sRank;
		return notation;
	}

	void SavePos()
	{
		sOldPos = PosToNotation();
	}

	void SnapToGrid()
	{
		int iXPos = ((vPos.x + (vSize.x / 2)) % vSize.x);
		int iYPos = ((vPos.y + (vSize.y / 2)) % vSize.y);

		if (iXPos != 0)
			vPos.x -= iXPos - (vSize.x / 2);
		if (iYPos != 0)
			vPos.y -= iYPos - (vSize.y / 2);


		if (PosToNotation() != sOldPos)
		{
			bHasMoved = true;
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

	virtual void DisplayMoves(olc::PixelGameEngine *pge, olc::vi2d vMousePos) {}
};

class Pawn : public ChessPiece
{
public:
	Pawn(olc::vi2d vPos_, bool bIsBlack, int iPieceIndex) : ChessPiece(vPos_, bIsBlack, iPieceIndex) {}

	void DisplayMoves(olc::PixelGameEngine *pge, olc::vi2d vMousePos) override
	{
		if (!IsHovered(vMousePos))
			return;

		olc::vi2d vDir = {0, 0};

		vDir.y = (vSpritePos.y - 0.5) * 2;

		pge->FillCircle(vPos + (vSize / 2) + (vDir * vSize), 8, olc::WHITE);

		if (!bHasMoved)
		{
			pge->FillCircle(vPos + (vSize / 2) + (vDir * (vSize * 2)), 8, olc::WHITE);
		}
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
