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
	ChessPiece *ptrSelection;

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

	void DrawChessPiece(ChessPiece *p)
	{
		DrawPartialSprite(p->vPos, p->sprSprite.get(), p->vSpritePos * iGridSize, olc::vi2d(1, 1) * iGridSize);
	}

	void ArrangePieces()
	{
		char cLayout[8][8] =
			{
				{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
				{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
			};

		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				char *cPiece = &cLayout[y][x];

				int iPX = x * iGridSize;
				int iPY = y * iGridSize;

				if (y > 1)
				{
					iPY += iGridSize * 4;
				}

				switch (*cPiece)
				{
				case ' ':
					pieces[x + 8 * y] = Pawn({iPX, iPY}, y>1, 0);
					break;
				case 'R':
					pieces[x + 8 * y] = Rook({iPX, iPY}, y>1, 1);
					break;
				case 'N':
					pieces[x + 8 * y] = Knight({iPX, iPY}, y>1, 2);
					break;
				case 'B':
					pieces[x + 8 * y] = Bishop({iPX, iPY}, y>1, 3);
					break;
				case 'Q':
					pieces[x + 8 * y] = Queen({iPX, iPY}, y>1, 4);
					break;
				case 'K':
					pieces[x + 8 * y] = King({iPX, iPY}, y>1, 5);
					break;
				default:
					break;
				}
			}
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

		ptrSelection->vPos.x = GetMousePos().x - ptrSelection->vSize.x / 2;
		ptrSelection->vPos.y = GetMousePos().y - ptrSelection->vSize.y / 2;
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
		for (int i = 0; i < 32; i++)
		{
			// check if mouse if selecting this piece
			bool bIsSelected = pieces[i].IsSelected(GetMousePos(), GetMouse(0).bHeld);

			// make a selection (if exists)
			if (ptrSelection->vPos.x == -1 && ptrSelection->vPos.y == -1 && bIsSelected)
			{
				ptrSelection = &pieces[i];
			}

			// snap unselected pieces to grid
			if (ptrSelection != &pieces[i])
			{
				pieces[i].SnapToGrid();
			}

			UpdatePiecePosition();
			DrawChessPiece(&pieces[i]);
		}
		SetPixelMode(olc::Pixel::NORMAL);

		// clear selection upon mouse release
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
