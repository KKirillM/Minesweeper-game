#pragma once

#define NUM_HORIZ_CELLS		15		//кол-во ячеек по горизонтали
#define NUM_VERTIC_CELLS	10		//кол-во ячеек по вертикали
#define NUM_MINES			20		//кол-во мин на игровом поле

class Field;

//класс таймера
class Timer
{
public:
	Timer(void)
	{
		timerID = 0;
		secondCounter = 0;
	}
	~Timer(void) {}

	void StartWindowTimer(HWND window) { timerID = SetTimer(window, 1556, 1000, NULL); }

	void KillWindowTimer(HWND window) { KillTimer(window, timerID); secondCounter = 0; timerID = 0; }

	void Reset() { timerID = 0; secondCounter = 0; }

	void addSecond() { ++secondCounter; }

	UINT_PTR getTimerID() const { return timerID; }

	int getSecond() const { return secondCounter; }

private:
	UINT_PTR timerID;
	int secondCounter;
};

//класс Game содержит в себе базовые возможности игры такие как старт новой игры, завершение игры и др.
//также он включает указатель на класс игрового поля и класс таймера
class Game
{
public:
	Game(void);
	~Game(void);

	void InitData(int horizontalCount, int verticalCount, int mines);

	void StartNewGame();

	void ShowWinMessage();

	void ShowGameOverMessage();

	void StartNewTimer();

	void setMainWindow(HWND wnd) { window = wnd; }

	Timer* getTimer() const { return timer; }

	Field* getGameField() const { return gameField; }

private:
	Field* gameField;	
	HWND window;		//хэндл главного окна игры
	Timer* timer;		
};

