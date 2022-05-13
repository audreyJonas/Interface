#pragma once

#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/alignment.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/grid.h>
#include <gtkmm/stock.h>
#include <gtkmm/textview.h>



#include "Observateur.hpp"
#include "firstWindow.hpp"
#include "Dialogue.hpp"

class Controleur;

class VueG : public Gtk::Window, public Observateur<double> {

private:
  /* Gtk::Box box1;
  Gtk::HBox box2,box4;
  Gtk::HButtonBox box3;
  Gtk::Button bExit, bSuivant, bInstructions;
  Gtk::Alignment alignement;
  //Glib::RefPtr<Gtk::TextBuffer> buf1_textPres;
  //Gtk::TextView zoneTexte;
  Gtk::Label zoneTexte; 
  Gtk::Grid mainGrid;*/
  Gtk::Button b;
  Gtk::VBox boiteV;
  Gtk::Label etiquette;
    
public:
  VueG();
  virtual ~VueG();
  void close();
  void update(double &info);
  void afficherDialogue();
  void afficherPremierePage();
  // void afficherInstructions();
 
};


