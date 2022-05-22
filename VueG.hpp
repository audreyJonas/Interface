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
#include <cstring>

#include "Observateur.hpp"
#include "firstWindow.hpp"
#include "choiceWindow.hpp"
#include "Dialogue.hpp"
#include "Mine.hpp"

class Controleur;

class VueG : public Gtk::Window, public Observateur<std::vector<std::string>> {

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
  std::vector<Mine*> casesGrille;
  
public:
  VueG();
  virtual ~VueG();
  void close();
  void update(std::vector<std::string> &info);
  void afficherDialogue();
  void afficherPremierePage();
  void afficherInstructions();
  void afficherDifficulte();
  void initialiserGrille(const int M, const int N);
  void addGridListener(Controleur* c);
  void testActive(int l, int c, int M);
  std::vector<Mine*> get_casesGrille();
  
};


