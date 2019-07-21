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

CGameDialog::CGameDialog(GtkWindow* pParent) : Dialog() {
  self_ = gtk_dialog_new_with_buttons(
    "Select Game",
    pParent,
    (GtkDialogFlags)(GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT),
    "Select", GTK_RESPONSE_OK,
    "Cancel", GTK_RESPONSE_CANCEL,
    nullptr
  );

  SetModal(true);

  GtkWidget* content_area = gtk_dialog_get_content_area(GTK_DIALOG(self_));
  GtkWidget* combo_box = gtk_combo_box_text_new();

  // todo: replace CLinkedList with std equivalent
  CLinkedList<CGameDefinition>* pList = nullptr;
  pList = GetGameAPI()->GetGameDefinitionList();
  if (pList != nullptr) {
    pList->First();
    for (CGameDefinition* pGame = pList->GetCurItem(); pGame != nullptr; pGame = pList->GetNextItem()) {
      gtk_combo_box_text_insert(
        GTK_COMBO_BOX_TEXT(combo_box),
        -1,
        pGame->GetGameName().GetBuffer(),
        pGame->GetGameName().GetBuffer()
      );
    }
  } else {
    Error("Invalid pointer to Game Definition List");
  }
  
  gtk_container_add(GTK_CONTAINER(content_area), combo_box);

  g_signal_connect(combo_box, "changed", G_CALLBACK(Changed), this);

  // Ensure something is selected
  gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box), 0);

  gtk_container_set_border_width(GTK_CONTAINER(self_), 5);
  gtk_container_set_border_width(GTK_CONTAINER(content_area), 5);
  gtk_container_set_border_width(GTK_CONTAINER(combo_box), 5);
  
  SetDefaultSize(512, -1);
  SetPosition(GTK_WIN_POS_CENTER);

  ShowAll();
}

CGameDialog::~CGameDialog() {
}

std::string CGameDialog::GetGameSelection() { 
  return game_;
}

#if 0
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
