
#pragma once

// GameDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGameDialog dialog

#include "GtkWrapper.h"

class CGameDialog : public gtk::Dialog {
 private:
  std::string game_;
  // Construction
 public:
  CGameDialog(GtkWindow* pParent = nullptr);  // standard constructor
  ~CGameDialog();
  
  std::string GetGameSelection();

  static void Changed(GtkComboBox* widget, CGameDialog* cself) {
    gchar* str = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget));
    if (str == nullptr) {
      return;
    }

    cself->game_ = str;
    g_free(str);
  }
};
