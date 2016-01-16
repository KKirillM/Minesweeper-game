
// MinesweeperDlg.h : header file
//

#pragma once

class Game;

//класс главного окна игры
class CMinesweeperDlg : public CDialogEx
{
public:
	CMinesweeperDlg(Game* pGameObject, CWnd* pParent = NULL);
	~CMinesweeperDlg();

// Dialog Data
	enum { IDD = IDD_MINESWEEPER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	void AddMenu(void);
	void AddStatusBar(void);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	
	DECLARE_MESSAGE_MAP()

private:
	Game* gameObject;
	CMenu menu;
	CStatusBarCtrl statBar;
	
public:
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnGameNew();
	afx_msg void OnGameStop();
	afx_msg void OnGameQuit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
