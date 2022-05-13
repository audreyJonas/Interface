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
#include <gtkmm/menu.h>
#include <gtkmm/menubar.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/separatormenuitem.h>
#include <gtkmm/imagemenuitem.h>
#include <gtkmm/stock.h>
#include <gtkmm/textview.h>



#include "Observateur.hpp"
#include "firstWindow.hpp"
#include "Dialogue.hpp"

class Controleur;

class VueG : public Gtk::Window, public Observateur<double> {

private:
  Gtk::MenuBar barreMenu;
  Gtk::MenuItem itemMenu,itemAide,itemParametres;
  Gtk::Menu Menu,Aide,Parametres;
  Gtk::ImageMenuItem subItemFichierScores,subItemQuitter,subItemRegles,subItemDifficulte;
  Gtk::SeparatorMenuItem separateur;
  Gtk::HBox boiteMenu,boite2;
  Gtk::VBox boiteJoueur,Jeu,Grille;
  Gtk::Label pseudoJoueur;
  Gtk::Image avatarJoueur;
  
public:
  VueG();
  virtual ~VueG();
  void close();
  void update(double &info);
  void afficherDialogue();
  void afficherPremierePage();
  void afficherInstructions();
};


