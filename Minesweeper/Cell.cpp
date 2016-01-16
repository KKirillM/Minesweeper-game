#include "StdAfx.h"
#include "resource.h"
#include "Cell.h"

CBitmap State::bitmapClose;
CBitmap State::bitmapCloseWithMouseClick;
CBitmap State::bitmapCloseWithMouseMove;
CBitmap State::bitmapFlag;
CBitmap State::bitmapFlagWithMouseMove;
CBitmap State::bitmapOpen;
CBitmap State::bitmapOpen_1;
CBitmap State::bitmapOpen_2;
CBitmap State::bitmapOpen_3;
CBitmap State::bitmapOpen_4;
CBitmap State::bitmapOpen_5;
CBitmap State::bitmapOpen_6;
CBitmap State::bitmapOpen_7;
CBitmap State::bitmapOpen_8;
CBitmap State::bitmapOpenWithMine;
CBitmap State::bitmapOpenWithMineBang;
CBitmap State::bitmapQuestion;
CBitmap State::bitmapQuestionQithMouseClick;
CBitmap State::bitmapQuestionQithMouseMove;

Cell::Cell(void)
{
	row = 0;			
	column = 0;			
	mined = false;	
	is_open = false;
	mineCounter = 0;		
	currentState = new CloseCellState(this);
}

Cell::~Cell(void)
{
	if (currentState)
	{
		delete currentState;
		currentState = NULL;
	}
}

void State::InitBitmaps()
{
	bitmapClose.LoadBitmapW(IDB_BITMAP_CLOSE);	
	bitmapCloseWithMouseClick.LoadBitmapW(IDB_BITMAP_CLICK);
	bitmapCloseWithMouseMove.LoadBitmapW(IDB_BITMAP_MOVE);
	bitmapFlag.LoadBitmapW(IDB_BITMAP_FLAG);
	bitmapFlagWithMouseMove.LoadBitmapW(IDB_BITMAP_FLAG_MOVE);
	bitmapOpen.LoadBitmapW(IDB_BITMAP_OPEN0);					
	bitmapOpen_1.LoadBitmapW(IDB_BITMAP_OPEN1);				
	bitmapOpen_2.LoadBitmapW(IDB_BITMAP_OPEN2);				
	bitmapOpen_3.LoadBitmapW(IDB_BITMAP_OPEN3);				
	bitmapOpen_4.LoadBitmapW(IDB_BITMAP_OPEN4);				
	bitmapOpen_5.LoadBitmapW(IDB_BITMAP_OPEN5);				
	bitmapOpen_6.LoadBitmapW(IDB_BITMAP_OPEN6);				
	bitmapOpen_7.LoadBitmapW(IDB_BITMAP_OPEN7);				
	bitmapOpen_8.LoadBitmapW(IDB_BITMAP_OPEN8);				
	bitmapOpenWithMine.LoadBitmapW(IDB_BITMAP_OPEN_MINE);		
	bitmapOpenWithMineBang.LoadBitmapW(IDB_BITMAP_OPEN_MINE_BANG);		
	bitmapQuestion.LoadBitmapW(IDB_BITMAP_QUESTION);				
	bitmapQuestionQithMouseClick.LoadBitmapW(IDB_BITMAP_QUESTION_CLICK);
	bitmapQuestionQithMouseMove.LoadBitmapW(IDB_BITMAP_QUESTION_MOVE);	
}

CSize State::getCellSize()
{
	CSize bitmapSize;
	BITMAP bMap;
	
	bitmapClose.GetBitmap(&bMap);
	
	bitmapSize.cx = bMap.bmWidth;
	bitmapSize.cy = bMap.bmHeight;
	
	return bitmapSize;
}

void Cell::Draw(CDC* dc)
{
	//получаем размер игрового поля
	CSize fieldSize = State::getCellSize();

	//рисуем ячейку в соответствии с её координатами на игровом поле
	CDC dcMemory;
    dcMemory.CreateCompatibleDC(dc);
	dcMemory.SelectObject(currentState->getBitmap());
	dc->BitBlt(5+column*fieldSize.cx, 5+row*fieldSize.cy, fieldSize.cx, fieldSize.cy, &dcMemory, 0, 0, SRCCOPY);
}

bool Cell::isCurrentCellCoord(int x, int y)
{
	CPoint coord = getCoord(); 
	CSize cellSize = State::getCellSize();
	
	if ( coord.x < x && coord.x + cellSize.cx > x &&
		 coord.y < y && coord.y + cellSize.cy > y )
	{
		return true;
	}
	else
		return false;
}

void Cell::MoveCursorAction(int xCoord, int yCoord)
{
	currentState->MoveCursorAction(xCoord, yCoord);
}

void Cell::PushButton1Action(int xCoord, int yCoord)
{
	currentState->PushButton1Action(xCoord, yCoord);
}

bool Cell::PopButton1Action(int xCoord, int yCoord)
{
	return currentState->PopButton1Action(xCoord, yCoord);
}

void Cell::PushButton2Action(int xCoord, int yCoord)
{
	currentState->PushButton2Action(xCoord, yCoord);
}

void Cell::PopButton2Action(int xCoord, int yCoord)
{
	currentState->PopButton2Action(xCoord, yCoord);
}

//***CloseCellState***

void CloseCellState::MoveCursorAction(int xCoord, int yCoord)	//курсор на закрытой ячейке
{
	Cell* cell = getCell();

	if (cell->isCurrentCellCoord(xCoord, yCoord))
	{
		if (bitmap == &bitmapClose)
			bitmap = &bitmapCloseWithMouseMove;
	}	
	else
	{
		bitmap = &bitmapClose;
	}
}

void CloseCellState::PushButton1Action(int xCoord, int yCoord)	//нажатие ЛКМ на закрытой ячейке
{
	Cell* cell = getCell();

	if (cell->isCurrentCellCoord(xCoord, yCoord))
	{
		bitmap = &bitmapCloseWithMouseClick;
	}	
	else
	{
		bitmap = &bitmapClose;
	}
}

bool CloseCellState::PopButton1Action(int xCoord, int yCoord)	//отпускание ЛКМ на закрытой наведенной ячейке
{
	Cell* cell = getCell();

	if (cell->isCurrentCellCoord(xCoord, yCoord))
	{
		if (bitmap == &bitmapCloseWithMouseClick)
		{
			cell->setState(new OpenCellState(cell));
			return true;
		}
	}	

	return false;
}

void CloseCellState::PushButton2Action(int xCoord, int yCoord)	//нажатие ПКМ на закрытой ячейке
{
	Cell* cell = getCell();

	if (cell->isCurrentCellCoord(xCoord, yCoord))
	{
		bitmap = &bitmapCloseWithMouseClick;
	}	
	else
	{
		bitmap = &bitmapClose;
	}
}

void CloseCellState::PopButton2Action(int xCoord, int yCoord)	//отпускание ПКМ на закрытой наведенной ячейке
{
	Cell* cell = getCell();

	if (cell->isCurrentCellCoord(xCoord, yCoord))
	{
		if (bitmap == &bitmapCloseWithMouseClick)
			cell->setState(new CloseFlagCellState(cell));
	}
}

//***CloseFlagCellState***

void CloseFlagCellState::MoveCursorAction(int xCoord, int yCoord)
{
	Cell* cell = getCell();

	if (cell->isCurrentCellCoord(xCoord, yCoord))
	{
		bitmap = &bitmapFlagWithMouseMove;
	}
	else
	{
		bitmap = &bitmapFlag;
	}
}

void CloseFlagCellState::PushButton1Action(int xCoord, int yCoord)
{
}

bool CloseFlagCellState::PopButton1Action(int xCoord, int yCoord)
{
	return false;
}

void CloseFlagCellState::PushButton2Action(int xCoord, int yCoord)
{
}

void CloseFlagCellState::PopButton2Action(int xCoord, int yCoord)
{
	Cell* cell = getCell();

	if (cell->isCurrentCellCoord(xCoord, yCoord))
	{
		if (bitmap == &bitmapFlagWithMouseMove)
			cell->setState(new CloseQuestionCellState(cell));
	}
}

//***CloseQuestionCellState***

void CloseQuestionCellState::MoveCursorAction(int xCoord, int yCoord)
{
	Cell* cell = getCell();

	if (cell->isCurrentCellCoord(xCoord, yCoord))
	{
		if (bitmap != &bitmapQuestionQithMouseClick)
			bitmap = &bitmapQuestionQithMouseMove;
	}
	else
	{
		bitmap = &bitmapQuestion;
	}
}

void CloseQuestionCellState::PushButton1Action(int xCoord, int yCoord)
{
	Cell* cell = getCell();

	if (cell->isCurrentCellCoord(xCoord, yCoord))
	{
		bitmap = &bitmapQuestionQithMouseClick;
	}	
	else
	{
		bitmap = &bitmapQuestion;
	}
}

bool CloseQuestionCellState::PopButton1Action(int xCoord, int yCoord)
{
	Cell* cell = getCell();

	if (cell->isCurrentCellCoord(xCoord, yCoord))
	{
		if (bitmap == &bitmapQuestionQithMouseClick)
		{
			cell->setState(new OpenCellState(cell));
			return true;
		}
	}	

	return false;
}

void CloseQuestionCellState::PushButton2Action(int xCoord, int yCoord)
{
	Cell* cell = getCell();

	if (cell->isCurrentCellCoord(xCoord, yCoord))
	{
		bitmap = &bitmapQuestionQithMouseClick;
	}	
	else
	{
		bitmap = &bitmapQuestion;
	}
}

void CloseQuestionCellState::PopButton2Action(int xCoord, int yCoord)
{
	Cell* cell = getCell();

	if (cell->isCurrentCellCoord(xCoord, yCoord))
	{
		if (bitmap == &bitmapQuestionQithMouseClick)
		{
			cell->setState(new CloseCellState(cell));
		}
	}
}