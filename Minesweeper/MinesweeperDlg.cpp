
// MinesweeperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Minesweeper.h"
#include "MinesweeperDlg.h"
#include "afxdialogex.h"
#include "Game.h"
#include "Field.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMinesweeperDlg dialog

CMinesweeperDlg::CMinesweeperDlg(Game* pGameObject, CWnd* pParent /*=NULL*/)
	: CDialogEx(CMinesweeperDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	gameObject = pGameObject;
}

CMinesweeperDlg::~CMinesweeperDlg()
{
	if (gameObject)
	{
		delete gameObject;
		gameObject = NULL;
	}
}

void CMinesweeperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMinesweeperDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_GAME_NEW, &CMinesweeperDlg::OnGameNew)
	ON_COMMAND(ID_GAME_STOP, &CMinesweeperDlg::OnGameStop)
	ON_COMMAND(ID_GAME_QUIT, &CMinesweeperDlg::OnGameQuit)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMinesweeperDlg message handlers

BOOL CMinesweeperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//инициализируем начальными данными игру
	gameObject->InitData(NUM_HORIZ_CELLS, NUM_VERTIC_CELLS, NUM_MINES);
	
	//получаем размер игрового поля
	Field* gameField = gameObject->getGameField();
	CSize fieldSize = gameField->getFieldSize();

	//изменяем размер окна в соответствии с размером игрового поля
	CRect rect;
	GetWindowRect(rect);
	MoveWindow(rect.left, rect.top, fieldSize.cx + 17, fieldSize.cy + 82);

	//добавляем меню
	AddMenu();

	//доабвляем строку состояния для отображения таймера
	AddStatusBar();

	//инициализируем хэндл окна для класса игры
	gameObject->setMainWindow(GetSafeHwnd());
	
	//при первом запуске приложения сразу начинается новая игра
	gameObject->StartNewGame();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMinesweeperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		Field* gameField = gameObject->getGameField();
		gameField->DrawField(&dc);

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMinesweeperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMinesweeperDlg::AddMenu(void)
{
	menu.LoadMenuW(IDR_MENU);
	SetMenu(&menu);
}

void CMinesweeperDlg::AddStatusBar(void)
{
	CRect rect;
   	GetWindowRect(&rect);
	rect.top = rect.bottom - 25;
    	
	statBar.Create(WS_CHILD | WS_BORDER | WS_VISIBLE , rect, this, 1555);                             

	statBar.SetMinHeight(25); 
	statBar.SetText(L"Timer: 0", 0,0);
}

void CMinesweeperDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//комментируем обработку кнопки Enter, чтобы при нажатии на неё приложение не закрывалось
	//CDialogEx::OnOK();
}

void CMinesweeperDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	Field* gameField = gameObject->getGameField();
	gameField->MoveCursor(point.x, point.y);

	Invalidate(0);

	CDialogEx::OnMouseMove(nFlags, point);
}

void CMinesweeperDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	Field* gameField = gameObject->getGameField();
	gameField->HitLeftMouseButton(point.x, point.y);

	Invalidate(0);

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMinesweeperDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	Field* gameField = gameObject->getGameField();
	gameField->UpLeftMouseButton(point.x, point.y);

	Invalidate(0);

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CMinesweeperDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	Field* gameField = gameObject->getGameField();
	gameField->HitRightMouseButton(point.x, point.y);

	Invalidate(0);

	CDialogEx::OnRButtonDown(nFlags, point);
}

void CMinesweeperDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	Field* gameField = gameObject->getGameField();
	gameField->UpRightMouseButton(point.x, point.y);

	Invalidate(0);

	CDialogEx::OnRButtonUp(nFlags, point);
}

void CMinesweeperDlg::OnGameNew()
{
	// TODO: Add your command handler code here
	gameObject->StartNewGame();
}

void CMinesweeperDlg::OnGameStop()
{
	// TODO: Add your command handler code here

	//открываем игровое поле
	Field* gameField = gameObject->getGameField();
	gameField->OpenField();

	//останавливаем таймер
	Timer* timer = gameObject->getTimer();
	timer->KillWindowTimer(GetSafeHwnd());
}

void CMinesweeperDlg::OnGameQuit()
{
	// TODO: Add your command handler code here
	OnCancel();
}

void CMinesweeperDlg::OnTimer(UINT_PTR nIDEvent)
{
	//обрабатываем сигналы от таймера каждую секунду
	Timer* timer = gameObject->getTimer();

	if (nIDEvent == timer->getTimerID())
	{
		timer->addSecond();
		CString str;
		str.Format(L"Timer: %d", timer->getSecond());
		statBar.SetText(str, 0,0);
	}

	CDialogEx::OnTimer(nIDEvent);
}
