// GameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "tread3d.h"
#include "GameDialog.h"
#include "GameApi.h"
#include "TreadSys.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGameDialog dialog

CGameDialog::CGameDialog(GtkWindow* pParent /*=NULL*/) {
  window_ = gtk_dialog_new_with_buttons(
    "Select Game",
    pParent,
    GTK_DIALOG_MODAL,
    "Select", "Cancel", NULL
  );
  gtk_window_set_modal(GTK_WINDOW(window_), true);

  GtkWidget* content_area = gtk_dialog_get_content_area(
    GTK_DIALOG(window_));
  GtkWidget* label = gtk_label_new("Hello World!");

  GtkWidget* list_box = gtk_list_box_new();
  gtk_list_box_insert(GTK_LIST_BOX(list_box), label, -1);

  g_signal_connect_swapped(window_, "response",
    G_CALLBACK(gtk_widget_destroy),
    window_);

  gtk_container_add(GTK_CONTAINER(content_area), list_box);

  gtk_widget_show_all(window_);
  gtk_window_set_position(GTK_WINDOW(window_), GTK_WIN_POS_CENTER);
}

CGameDialog::~CGameDialog() {
}

CString CGameDialog::GetGameSelection() { return m_sGame; }

#if 0
BEGIN_MESSAGE_MAP(CGameDialog, CDialog)
//{{AFX_MSG_MAP(CGameDialog)
ON_WM_CTLCOLOR()
ON_LBN_SELCHANGE(IDC_LIST_GAMES, OnSelchangeListGames)
ON_BN_CLICKED(IDC_BUTTON_SELECT, OnButtonSelect)
ON_LBN_DBLCLK(IDC_LIST_GAMES, OnDblclkListGames)
ON_LBN_SELCANCEL(IDC_LIST_GAMES, OnSelcancelListGames)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameDialog message handlers

HBRUSH CGameDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
  HBRUSH hbr;

  switch (nCtlColor) {
    case CTLCOLOR_LISTBOX:
      pDC->SetTextColor(RGB(50, 50, 200));
      pDC->SetBkColor(RGB(196, 196, 196));
      hbr = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
      return hbr;
  }

  hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
  return hbr;
}

BOOL CGameDialog::OnInitDialog() {
  CDialog::OnInitDialog();

  GetDlgItem(IDC_BUTTON_SELECT)->EnableWindow(false);

  CGameDefinition* pGame = NULL;
  CLinkedList<CGameDefinition>* pList = NULL;

  pList = GetGameAPI()->GetGameDefinitionList();
  if (pList == NULL) {
    Error("Invalid pointer to Game Definition List");
    return false;
  }

  pList->First();
  for (pGame = pList->GetCurItem(); pGame != NULL; pGame = pList->GetNextItem())
    AddGameString(pGame->GetGameName());

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}

void CGameDialog::OnSelchangeListGames() {
  GetDlgItem(IDC_BUTTON_SELECT)->EnableWindow(true);

  int nTemp;
  nTemp = m_lbGames.GetCurSel();
  if (nTemp == -1)
    return;
  else
    m_lbGames.GetText(nTemp, m_sGame);
}

void CGameDialog::AddGameString(CString sGame) { m_lbGames.AddString(sGame); }

void CGameDialog::OnButtonSelect() { OnOK(); }

void CGameDialog::OnDblclkListGames() {
  int nTemp;
  nTemp = m_lbGames.GetCurSel();
  if (nTemp == -1) return;

  m_lbGames.GetText(nTemp, m_sGame);
  OnOK();
}

void CGameDialog::OnSelcancelListGames() {
  GetDlgItem(IDC_BUTTON_SELECT)->EnableWindow(false);
}
#endif
