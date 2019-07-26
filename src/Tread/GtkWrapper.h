/*
The MIT License (MIT)

Copyright (c) 2019 Mark Sowden <markelswo@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <gtk/gtk.h>
#include <string>

namespace gtk {
  class Widget {
  public:
    void ShowAll() {
      gtk_widget_show_all(self_);
    }

    static void Destroy(GtkWidget* self, Widget* cself) {
      gtk_widget_destroy(self);
      delete cself;
    }

    GtkWidget* GetSelf() { return self_; }

  protected:
    GtkWidget* self_{ nullptr };
  };

  class Container : public Widget {
  public:

    void Add(Widget* widget) {
      gtk_container_add(GTK_CONTAINER(self_), widget->GetSelf());
    }

    void Remove(Widget* widget) {
      gtk_container_remove(GTK_CONTAINER(self_), widget->GetSelf());
    }

    void SetBorderWidth(unsigned int border_width) {
      gtk_container_set_border_width(GTK_CONTAINER(self_), border_width);
    }

  protected:
  private:
  };

  class ComboBox : public Container {
  public:
    ComboBox() {
      self_ = gtk_combo_box_new();
    }

    void SetActive(int index) {
      gtk_combo_box_set_active(GTK_COMBO_BOX(self_), index);
    }
  };

  class Window : public Container {
  public:
    explicit Window(GtkWindowType type) {
      self_ = gtk_window_new(type);
    }

    ~Window() {
      gtk_widget_destroy(self_);
    }

    void Maximize() {
      gtk_window_maximize(GTK_WINDOW(self_));
    }

    void UnMaximize() {
      gtk_window_unmaximize(GTK_WINDOW(self_));
    }

    bool ActivateFocus() {
      return gtk_window_activate_focus(GTK_WINDOW(self_));
    }

    bool ActivateDefault() {
      return gtk_window_activate_default(GTK_WINDOW(self_));
    }

    bool IsMaximized() {
      return gtk_window_is_maximized(GTK_WINDOW(self_));
    }

    bool IsActive() {
      return gtk_window_is_active(GTK_WINDOW(self_));
    }

    void SetTitle(const std::string& title) {
      gtk_window_set_title(GTK_WINDOW(self_), title.c_str());
    }

    void SetResizable(bool resizable) {
      gtk_window_set_resizable(GTK_WINDOW(self_), resizable);
    }

    void SetPosition(GtkWindowPosition position) {
      gtk_window_set_position(GTK_WINDOW(self_), position);
    }

    void SetDefaultSize(int width, int height) {
      gtk_window_set_default_size(GTK_WINDOW(self_), width, height);
    }

    void SetModal(bool modal) {
      gtk_window_set_modal(GTK_WINDOW(self_), modal);
    }
  };

  class Dialog : public Window {
  public:
    Dialog() : Window(GTK_WINDOW_POPUP) {}

    int Run() {
      return gtk_dialog_run(GTK_DIALOG(self_));
    }
  };
}
