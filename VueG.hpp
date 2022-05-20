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
#include <gtkmm/messagedialog.h>
#include <gtkmm/stock.h>
#include <gtkmm/textview.h>
#include <gtkmm/table.h>
#include <vector>

#include "Observateur.hpp"
#include "firstWindow.hpp"
#include "choiceWindow.hpp"
#include "Dialogue.hpp"
#include "Mine.hpp"

class Controleur;

class VueG : public Gtk::Window, public Observateur<double> {

private:
  Gtk::MenuBar barreMenu;
  Gtk::MenuItem itemMenu,itemAide,itemParametres;
  Gtk::Menu Menu,Aide,Parametres;
  Gtk::ImageMenuItem subItemFichierScores,subItemQuitter,subItemRegles,subItemDifficulte;
  Gtk::SeparatorMenuItem separateur;
  Gtk::HBox boiteMenu,boiteJeu;
  Gtk::VBox boiteJoueur,Jeu,Grille;
  Gtk::Label pseudoJoueur;
  Gtk::Image avatarJoueur;
  Gtk::Grid GrilleJeu;
  Gtk::Table boite;
  std::vector<Mine*> v;
  
public:
  VueG();
  virtual ~VueG();
  void close();
  void update(double &info);
  void afficherDialogue();
  void afficherPremierePage();
  void afficherInstructions();
  void afficherDifficulte();
  void initialiserGrille(const int M, const int N);
};


