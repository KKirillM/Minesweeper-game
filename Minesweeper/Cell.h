#pragma once

class State;
class Field;

//реализация класса ячейки игрового поля основана на базе паттерна Состояние (State)
//класс ячейки включает указатель на класс состояния, который отвечает за поведение 
//ячейки в зависимости от её внутреннего состояния

//класс ячейки игрового поля
class Cell
{
public:
	Cell(void);
	~Cell(void);

	//отрисовка ячейки
	void Draw(CDC* dc);

	//функции обработки ячейкой полученного действия
	void MoveCursorAction(int xCoord, int yCoord);
	void PushButton1Action(int xCoord, int yCoord);
	bool PopButton1Action(int xCoord, int yCoord);
	void PushButton2Action(int xCoord, int yCoord);
	void PopButton2Action(int xCoord, int yCoord);	

	void addMineCounter() { ++mineCounter; }
	
	void setOpen() { is_open = true; }

	void setColumn(int i) { column = i; }

	void setRow(int i) { row = i; }

	void setCoord(CPoint c) { coord = c; }

	void setMined() { mined = true; }

	void setState(State* st) { delete currentState; currentState = st; }

	int getMineCounter() const { return mineCounter; }

	int getRow() const { return row; }

	int getColumn() const { return column; }

	CPoint getCoord() const { return coord; }

	State* getState() { return currentState; }

	bool isCurrentCellCoord(int x, int y);

	bool isOpen() const { return is_open; }

	bool isMined()	const { return mined; }	

private:
	CPoint coord;			//координаты ячейки на игровом поле
	int row;				//номер строки ячейки на игровом поле
	int column;				//номер столбца ячейки на игровом поле
	bool mined;				//наличие мины в ячейке
	bool is_open;			//состояние ячейки: false - закрыта, true - открыта
	int mineCounter;		//кол-во мин в соседних ячейках
	State* currentState;	//текущее состояние ячейки
};

//абстрактный класс для каждого из состояний в которых может пребывать ячейка игрового поля
class State
{
public:
	friend class Field;
	State(Cell* c) : cell(c), bitmap(NULL) {}
	virtual ~State(void) {}

	//инициализация статических переменных класса
	static void InitBitmaps();

	//размер картинки ячейки
	static CSize getCellSize();

	virtual void MoveCursorAction(int xCoord, int yCoord) = 0;	//поведение ячейки при перемещении курсора над ячейкой	
	virtual void PushButton1Action(int xCoord, int yCoord) = 0;	//поведение ячейки при нажатии ЛКМ
	virtual bool PopButton1Action(int xCoord, int yCoord) = 0;	//поведение ячейки при отпускании ЛКМ	
	virtual	void PushButton2Action(int xCoord, int yCoord) = 0;	//поведение ячейки при нажатии ПКМ
	virtual	void PopButton2Action(int xCoord, int yCoord) = 0;	//поведение ячейки при отпускании ПКМ

	void setBitmap(CBitmap* bm) { bitmap = bm; }

	CBitmap* getBitmap() { return bitmap; }	
	
	Cell* getCell() { return cell; }

private:
	Cell* cell;

protected:
	CBitmap* bitmap;

	//переменные для хранения всех возможных изображений ячеек
	static CBitmap bitmapClose;
	static CBitmap bitmapCloseWithMouseClick;
	static CBitmap bitmapCloseWithMouseMove;
	static CBitmap bitmapFlag;
	static CBitmap bitmapFlagWithMouseMove;
	static CBitmap bitmapOpen;
	static CBitmap bitmapOpen_1;
	static CBitmap bitmapOpen_2;
	static CBitmap bitmapOpen_3;
	static CBitmap bitmapOpen_4;
	static CBitmap bitmapOpen_5;
	static CBitmap bitmapOpen_6;
	static CBitmap bitmapOpen_7;
	static CBitmap bitmapOpen_8;
	static CBitmap bitmapOpenWithMine;
	static CBitmap bitmapOpenWithMineBang;
	static CBitmap bitmapQuestion;
	static CBitmap bitmapQuestionQithMouseClick;
	static CBitmap bitmapQuestionQithMouseMove;
};

//чистая ячейка в закрытом состоянии
class CloseCellState : public State
{
public:
	CloseCellState(Cell* c) : State(c) { bitmap = &bitmapClose; }
	~CloseCellState(void) {}

	void MoveCursorAction(int xCoord, int yCoord); 
	void PushButton1Action(int xCoord, int yCoord);
	bool PopButton1Action(int xCoord, int yCoord);
	void PushButton2Action(int xCoord, int yCoord);
	void PopButton2Action(int xCoord, int yCoord); 
};

//ячейка в закрытом состоянии c флагом
class CloseFlagCellState : public State
{
public:
	CloseFlagCellState(Cell* c) : State(c) { bitmap = &bitmapFlagWithMouseMove; }
	~CloseFlagCellState(void) {}

	void MoveCursorAction(int xCoord, int yCoord); 
	void PushButton1Action(int xCoord, int yCoord);
	bool PopButton1Action(int xCoord, int yCoord);
	void PushButton2Action(int xCoord, int yCoord);
	void PopButton2Action(int xCoord, int yCoord); 
};

//ячейка в закрытом состоянии c знаком вопроса
class CloseQuestionCellState : public State
{
public:
	CloseQuestionCellState(Cell* c) : State(c) { bitmap = &bitmapQuestionQithMouseMove; }
	~CloseQuestionCellState(void) {}

	void MoveCursorAction(int xCoord, int yCoord); 
	void PushButton1Action(int xCoord, int yCoord);
	bool PopButton1Action(int xCoord, int yCoord);
	void PushButton2Action(int xCoord, int yCoord);
	void PopButton2Action(int xCoord, int yCoord); 
};

//ячейка в открытом состоянии
class OpenCellState : public State
{
public:
	OpenCellState(Cell* c) : State(c) 
	{
		c->setOpen();

		if (c->isMined()) 
		{
			bitmap = &bitmapOpenWithMine;
		}
		else
		{
			switch (c->getMineCounter())
			{
			case 0: bitmap = &bitmapOpen;   break;
			case 1: bitmap = &bitmapOpen_1; break;
			case 2: bitmap = &bitmapOpen_2; break;
			case 3: bitmap = &bitmapOpen_3; break;
			case 4: bitmap = &bitmapOpen_4; break;
			case 5: bitmap = &bitmapOpen_5; break;
			case 6: bitmap = &bitmapOpen_6; break;
			case 7: bitmap = &bitmapOpen_7; break;
			case 8: bitmap = &bitmapOpen_8; break;
			}
		}
	}
	~OpenCellState(void) {}

	void MoveCursorAction(int xCoord, int yCoord) {} 
	void PushButton1Action(int xCoord, int yCoord) {} 
	bool PopButton1Action(int xCoord, int yCoord) { return false; } 
	void PushButton2Action(int xCoord, int yCoord) {} 
	void PopButton2Action(int xCoord, int yCoord) {}  
};
