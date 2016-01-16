#include "StdAfx.h"
#include "Field.h"
#include "Cell.h"
#include "Game.h"

Field::Field(Game* game) : gamePointer(game)
{
	cellField = NULL;
	minesCount = 0;	
	openCount = 0;

	//загружаем картинки для ячеек
	State::InitBitmaps();
}

Field::~Field(void)
{
	if (cellField)
	{
		delete[] cellField;
		cellField = NULL;
	}
}

void Field::InitField()
{	
	openCount = 0;

	if (cellField)
		delete[] cellField;

	cellField = new Cell[horizontalCellsCount * verticalCellsCount];

	//прописываем для кадой ячейки её собственные координаты строки и солбца
	//а также прописываем графические координаты ячеек
	CSize cellSize = State::getCellSize();
	int index = 0;
	for (int i = 0; i < horizontalCellsCount; ++i)
	{
		for (int j = 0; j < verticalCellsCount; ++j)
		{
			cellField[index].setColumn(i);
			cellField[index].setRow(j);
			cellField[index].setCoord(CPoint(i * cellSize.cx + 5, j * cellSize.cy + 5));
			++index;
		}
	}
}

void Field::UndermineField()
{
	srand(time(NULL));

	int numOfCells = horizontalCellsCount * verticalCellsCount;
	int installMinesCount = 0;
	int cellIndex = 0;

	while (installMinesCount < minesCount)
	{
		cellIndex = rand() % (numOfCells-1);
		cellField[cellIndex].setMined();
		++installMinesCount;		
	}

	CountingMines();
}

void Field::CountingMines()
{
	for (int i = 0; i < horizontalCellsCount; ++i)
	{
		for (int j = 0; j < verticalCellsCount; ++j)
		{
			if (getCell(i, j)->isMined()) 
				continue;

			if (i > 0 && getCell(i-1, j)->isMined()) 
				getCell(i, j)->addMineCounter();

			if (i+1 != horizontalCellsCount && getCell(i+1, j)->isMined()) 
				getCell(i, j)->addMineCounter();

			if (j > 0 && getCell(i, j-1)->isMined())
				getCell(i, j)->addMineCounter();

			if (j+1 != verticalCellsCount && getCell(i, j+1)->isMined())
				getCell(i, j)->addMineCounter();

			if (i > 0 && j > 0 && getCell(i-1, j-1)->isMined())
				getCell(i, j)->addMineCounter();

			if (i > 0 && j+1 != verticalCellsCount && getCell(i-1, j+1)->isMined())
				getCell(i, j)->addMineCounter();

			if (i+1 != horizontalCellsCount && j > 0 && getCell(i+1, j-1)->isMined())
				getCell(i, j)->addMineCounter();

			if (i+1 != horizontalCellsCount && j+1 != verticalCellsCount && getCell(i+1, j+1)->isMined())
				getCell(i, j)->addMineCounter();
		}
	}
}

void Field::OpenField()
{
	int numOfCells = horizontalCellsCount * verticalCellsCount;
	
	for (int i = 0; i < numOfCells; ++i)
	{
		cellField[i].setState(new OpenCellState(&cellField[i]));
	}
}

void Field::OpenEmptyCells(int column, int row)
{ 
	if (getCell(column, row)->getMineCounter())
		return;

	if (column > 0)
		AuxiliaryOpenCellsFunction(getCell(column-1, row));
	
	if (column+1 != horizontalCellsCount)
		AuxiliaryOpenCellsFunction(getCell(column+1, row));
	
	if (row > 0)
		AuxiliaryOpenCellsFunction(getCell(column, row-1));
	
	if (row+1 != verticalCellsCount)
		AuxiliaryOpenCellsFunction(getCell(column, row+1));
	
	if (column > 0 && row > 0)
		AuxiliaryOpenCellsFunction(getCell(column-1, row-1));
	
	if (column > 0 && row+1 != verticalCellsCount)
		AuxiliaryOpenCellsFunction(getCell(column-1, row+1));
	
	if (column+1 != horizontalCellsCount && row > 0)
		AuxiliaryOpenCellsFunction(getCell(column+1, row-1));
	
	if (column+1 != horizontalCellsCount && row+1 != verticalCellsCount)
		AuxiliaryOpenCellsFunction(getCell(column+1, row+1));
}

void Field::AuxiliaryOpenCellsFunction(Cell* cell)
{
	if (cell->isOpen())
		return;

	if (!cell->isMined())
	{
		cell->setState(new OpenCellState(cell));
		++openCount;
		OpenEmptyCells(cell->getColumn(), cell->getRow());
	}
}

void Field::DrawField(CDC* dc)
{
	int numOfCells = horizontalCellsCount * verticalCellsCount;
	
	for (int i = 0; i < numOfCells; ++i)
	{
		cellField[i].Draw(dc);
	}
}

void Field::MoveCursor(int xCoord, int yCoord)
{
	int numOfCells = horizontalCellsCount * verticalCellsCount;

	for (int i = 0; i < numOfCells; ++i)
	{
		cellField[i].MoveCursorAction(xCoord, yCoord);
	}
}

void Field::HitLeftMouseButton(int x, int y)
{
	int numOfCells = horizontalCellsCount * verticalCellsCount;

	for (int i = 0; i < numOfCells; ++i)
	{
		cellField[i].PushButton1Action(x, y);
	}
}

void Field::UpLeftMouseButton(int x, int y)
{
	int numOfCells = horizontalCellsCount * verticalCellsCount;
	bool ret = false;

	for (int i = 0; i < numOfCells; ++i)
	{
		ret = cellField[i].PopButton1Action(x, y);

		//проверяем результат нажатия ЛКМ
		if (ret)
		{
			++openCount;
			int numOfCloseCells = horizontalCellsCount * verticalCellsCount - openCount;

			if (cellField[i].isMined())	//взрыв мины - конец игры
			{
				OpenField();
				cellField[i].getState()->setBitmap(&State::bitmapOpenWithMineBang);
				gamePointer->ShowGameOverMessage();
			}
			else if (!cellField[i].getMineCounter()) //пустая ячейка, открываем все смежные пустые ячейки
			{
				OpenEmptyCells(cellField[i].getColumn(), cellField[i].getRow());
			}
			else if (numOfCloseCells == minesCount)	//победа
			{
				OpenField();
				gamePointer->ShowWinMessage();
			}
		}
	}
}

void Field::HitRightMouseButton(int x, int y)
{
	int numOfCells = horizontalCellsCount * verticalCellsCount;

	for (int i = 0; i < numOfCells; ++i)
	{
		cellField[i].PushButton2Action(x, y);
	}
}

void Field::UpRightMouseButton(int x, int y)
{
	int numOfCells = horizontalCellsCount * verticalCellsCount;

	for (int i = 0; i < numOfCells; ++i)
	{
		cellField[i].PopButton2Action(x, y);
	}
}

CSize Field::getFieldSize()
{
	CSize fieldSize;
	CSize cellSize;
	
	cellSize = State::getCellSize();

	fieldSize.cx = cellSize.cx * horizontalCellsCount;
	fieldSize.cy = cellSize.cy * verticalCellsCount;

	return fieldSize;
}

Cell* Field::getCell(int column, int row) 
{ 
	int numOfCells = horizontalCellsCount * verticalCellsCount;
	Cell* cell = NULL;

	for (int i = 0; i < numOfCells; ++i)
	{
		if (cellField[i].getColumn() == column && cellField[i].getRow() == row)
		{
			cell = &cellField[i];
			break;
		}
	}
	
	return cell; 
}
