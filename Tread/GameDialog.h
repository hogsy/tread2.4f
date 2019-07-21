
#pragma once

// GameDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGameDialog dialog

#include <gtk/gtk.h>

namespace gtk {
  class Window {
  public:
    explicit Window(GtkWindow* parent = nullptr) {}
    ~Window() {}

  protected:
    GtkWidget* window_;
  };

  class Dialog : public Window {
  public:
    using Window::Window;

    int DoModal() {
      return gtk_dialog_run(GTK_DIALOG(window_));
    }
  };
}

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
