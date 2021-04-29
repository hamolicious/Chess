#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "chessPieces.cpp"
#include <iostream>

class ChessGame : public olc::PixelGameEngine
{
public:
	ChessGame()
	{
		sAppName = "Chess";
	}

private:
	int iGridSize = 64;
	ChessPiece pieces[32];

	olc::Pixel pWhiteColor = {199, 240, 216};
	olc::Pixel pBlackColor = {107, 122, 101};

	ChessPiece nullSelection;
	ChessPiece* ptrSelection;

public:
	void DrawChessBoard()
	{
		int iCounter = 0;

		for (int y = 0; y < ScreenHeight(); y += iGridSize)
		{
			for (int x = 0; x < ScreenWidth(); x += iGridSize)
			{
				if (iCounter % 2 == 0)
				{
					FillRect(x, y, iGridSize, iGridSize, pWhiteColor);
				}
				iCounter++;
			}
			iCounter++;
		}
	}

	void DrawChessPiece(ChessPiece* p)
	{
		DrawPartialSprite(p->vPos, p->sprSprite.get(), p->vSpritePos * iGridSize, olc::vi2d(1, 1) * iGridSize);
	}

	void ArrangePieces()
	{
		int iFileCounter = 0;
		olc::vi2d vFileOffset[] = {
			olc::vi2d(1, 0),
			olc::vi2d(2, 0),
			olc::vi2d(3, 0),
			olc::vi2d(5, 0),
			olc::vi2d(4, 0),
			olc::vi2d(3, 0),
			olc::vi2d(2, 0),
			olc::vi2d(1, 0)
		};

		for (int i = 0; i < 8; i++)
		{
			// white pawn
			pieces[i].vPos.x = iGridSize * i;
			pieces[i].vPos.y = iGridSize;

			pieces[i].vSpritePos.x = 0;
			pieces[i].vSpritePos.y = 0;

			// white others
			pieces[i + 16].vPos.x = iGridSize * i;
			pieces[i + 16].vPos.y = 0;

			pieces[i + 16].vSpritePos.x = vFileOffset[iFileCounter].x;
			pieces[i + 16].vSpritePos.y = vFileOffset[iFileCounter].y;

			// black others
			pieces[i + 24].vPos.x = iGridSize * i;
			pieces[i + 24].vPos.y = iGridSize * 7;

			pieces[i + 24].vSpritePos.x = vFileOffset[iFileCounter].x;
			pieces[i + 24].vSpritePos.y = vFileOffset[iFileCounter].y + 1;

			// black pawn
			pieces[i + 8].vPos.x = iGridSize * i;
			pieces[i + 8].vPos.y = iGridSize * 6;

			pieces[i + 8].vSpritePos.x = 0;
			pieces[i + 8].vSpritePos.y = 1;

			iFileCounter++;
		}
	}

	olc::vi2d NotationToPos(std::string notation)
	{
		olc::vi2d vPos;

		char *cstr = new char[notation.length() + 1];
		strcpy(cstr, notation.c_str());

		char cFile = cstr[0];
		char cRank = cstr[1];

		int iMultX = 0;
		int iMultY = 0;

		switch (cFile)
		{
		case 'A':
			iMultX = 0;
			break;
		case 'B':
			iMultX = 1;
			break;
		case 'C':
			iMultX = 2;
			break;
		case 'D':
			iMultX = 3;
			break;
		case 'E':
			iMultX = 4;
			break;
		case 'F':
			iMultX = 5;
			break;
		case 'G':
			iMultX = 6;
			break;
		case 'H':
			iMultX = 7;
			break;
		}

		vPos.x = iGridSize * iMultX;
		vPos.y = iGridSize * ((cRank - '0') - 1);

		delete[] cstr;
		return vPos;
	}

	void UpdatePiecePosition()
	{
		if (ptrSelection->vPos.x == -1 && ptrSelection->vPos.y == -1)
		{
			return;
		}

		ptrSelection->vPos.x = GetMousePos().x - ptrSelection->vSize.x/2;
		ptrSelection->vPos.y = GetMousePos().y - ptrSelection->vSize.y/2;
	}

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		ArrangePieces();

		nullSelection.vPos = {-1, -1};
		ptrSelection = &nullSelection;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(pBlackColor);
		DrawChessBoard();

		// draw and update all pieces
		SetPixelMode(olc::Pixel::MASK);
		for (int i = 0 ; i < 32 ; i++)
		{
			bool bIsSelected = pieces[i].IsSelected(GetMousePos(), GetMouse(0).bHeld);

			if (ptrSelection->vPos.x == -1 && ptrSelection->vPos.y == -1 && bIsSelected)
			{
				ptrSelection = &pieces[i];
			}

			if (ptrSelection != &pieces[i])
			{
				pieces[i].SnapToGrid();
			}

			UpdatePiecePosition();
			DrawChessPiece(&pieces[i]);
		}
		SetPixelMode(olc::Pixel::NORMAL);

		if (!GetMouse(0).bHeld)
		{
			ptrSelection = &nullSelection;
		}

		return true;
	}
};


int main()
{
	int iWidth = 512;
	int iHeight = 512;
	int iPixelSize = 1;

	ChessGame demo;
	if (demo.Construct(iWidth, iHeight, iPixelSize, iPixelSize))
		demo.Start();

	return 0;
}
