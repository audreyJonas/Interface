#pragma once

#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/grid.h>
#include <gtkmm/stock.h>
#include <gtkmm/textview.h>
#include <gtkmm/dialog.h>
#include <gtkmm/messagedialog.h>

class firstWindow : public Gtk::Dialog{

private:
  Gtk::Box* box1;
  Gtk::HBox box2;
  Gtk::HButtonBox box3;
  Gtk::Button bInstructions;
  //Glib::RefPtr<Gtk::TextBuffer> buf1_textPres;
  //Gtk::TextView zoneTexte;
  Gtk::Label zoneTexte;
  
public:
  firstWindow(Gtk::Window* parent);
  virtual ~firstWindow();
  void close();
  void suivant();
  void afficherInstructions();

};
