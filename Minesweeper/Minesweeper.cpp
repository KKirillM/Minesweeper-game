
// Minesweeper.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Minesweeper.h"
#include "MinesweeperDlg.h"
#include "Game.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMinesweeperApp

BEGIN_MESSAGE_MAP(CMinesweeperApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMinesweeperApp construction

CMinesweeperApp::CMinesweeperApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMinesweeperApp object

CMinesweeperApp theApp;


// CMinesweeperApp initialization

BOOL CMinesweeperApp::InitInstance()
{
	CWinApp::InitInstance();

	CMinesweeperDlg dlg(new Game());
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}