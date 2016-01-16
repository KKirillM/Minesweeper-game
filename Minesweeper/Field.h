#pragma once

class Cell;
class Game;

//класс игрового поля
//конструктор принимает 3 значения: кол-во горизонтальных ячеек, кол-во вертикальных ячеек и кол-во мин на поле
class Field
{
public:
	Field(Game* game);
	~Field(void);

	//создание массива ячеек и заполнение его данными
	void InitField();

	//заполнение поля минами в случайном порядке
	void UndermineField();

	//подсчёт количества мин в соседних ячейках
	void CountingMines();

	//открыть всё поле
	void OpenField();

	//открытие соседних пустых ячеек
	void OpenEmptyCells(int column, int row);

	//перерисовка всего поля
	void DrawField(CDC* dc);

	//сигнал перемещения курсора над полем
	void MoveCursor(int xCoord, int yCoord);

	//сигналы нажатия/отпускания левой кнопки мыши над полем
	void HitLeftMouseButton(int x, int y);
	void UpLeftMouseButton(int x, int y);

	//сигналы нажатия/отпускания правой кнопки мыши над полем
	void HitRightMouseButton(int x, int y);
	void UpRightMouseButton(int x, int y);

	void setCells(int horizontalCount, int verticalCount) 
	{ 
		horizontalCellsCount = horizontalCount;
		verticalCellsCount = verticalCount;
	}

	void setMinesCount(int mines) { minesCount = mines; }

	int getMinesCount() const { return minesCount; }

	Cell* getCell(int column, int row);

	//размер игрового поля в пикселях
	CSize getFieldSize();

private:
	void AuxiliaryOpenCellsFunction(Cell* cell);

private:
	Game* gamePointer;			//указатель на главный класс игры
	Cell* cellField;			//массив ячеек поля
	int minesCount;				//кол-во мин на поле
	int horizontalCellsCount;	//кол-во горизонтальных ячеек на поле
	int verticalCellsCount;		//кол-во вертикальных ячеек на поле
	int openCount;				//кол-во открытых ячеек на поле
};

