#include "StdAfx.h"
#include "Game.h"
#include "Field.h"
#include "Cell.h"


Game::Game(void)
{
	gameField = NULL;
	timer = NULL;
	window = NULL;
}

Game::~Game(void)
{
	if (gameField)
	{
		delete gameField;
		gameField = NULL;
	}

	if (timer)
	{
		delete timer;
		timer = NULL;
	}
}

void Game::InitData(int horizontalCount, int verticalCount, int mines)
{
	if (gameField) 
		delete gameField;

	//создаем игровое поле
	gameField = new Field(this);
	gameField->setCells(horizontalCount, verticalCount);
	gameField->setMinesCount(mines);
}

void Game::StartNewGame()
{
	//заполняем игровое поле ячейками и минами и запускаем таймер
	gameField->InitField();
	gameField->UndermineField();
	StartNewTimer();
}

void Game::ShowWinMessage()
{
	CString winMessage;

	winMessage.Format(L"Congratulations! You win!\n Your time: %d seconds.", timer->getSecond());
	timer->KillWindowTimer(window);
	MessageBox(NULL, winMessage, L"Game field cleared", MB_ICONINFORMATION);
	
}

void Game::ShowGameOverMessage()
{
	timer->KillWindowTimer(window);
	MessageBox(NULL, L"Mine explosion", L"Game over", MB_ICONINFORMATION);
}

void Game::StartNewTimer()
{
	if (timer == NULL)
	{
		timer = new Timer();
	}

	timer->Reset();
	timer->StartWindowTimer(window);
}