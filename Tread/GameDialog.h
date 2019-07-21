
#pragma once

// GameDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGameDialog dialog

#include "GtkWrapper.h"

class CGameDialog : public gtk::Dialog {
 private:
  CString m_sGame;
  // Construction
 public:
  CGameDialog(GtkWindow* pParent = nullptr);  // standard constructor
  ~CGameDialog();
  
  void AddGameString(CString sGame);
  CString GetGameSelection();
};
