#include <iomanip>
#include <cstdio>

#include "VueG.hpp"
#include "Controleur.hpp"

VueG::VueG():
  itemMenu("Menu"),
  itemAide("Aide"),
  itemParametres("Parametres"),
  subItemFichierScores(Gtk::Stock::FILE),
  subItemQuitter(Gtk::Stock::CLOSE),
  subItemRegles(Gtk::Stock::HELP),
  subItemDifficulte(Gtk::Stock::PROPERTIES),
  boiteMenu(false),
  boite2(false),
  boiteJoueur(false),
  Jeu(false),
  Grille(false),
  avatarJoueur("Avatars/yoshi3.png")
  
{
  /*Creation des differents menus*/
  /*Barre de menu*/
  barreMenu.append(itemMenu);
  barreMenu.append(itemAide);
  barreMenu.append(itemParametres);
  itemMenu.set_submenu(Menu);
  itemAide.set_submenu(Aide);
  itemParametres.set_submenu(Parametres);
  /*Sous items du menu deroulant Menu*/
  Menu.append(subItemFichierScores);
  Menu.append(separateur);
  Menu.append(subItemQuitter);
  /*Sous items du menu deroulant Aide*/
  Aide.append(subItemRegles);
  /*Sous items du menu deroulant Parametres*/
  Parametres.append(subItemDifficulte);

  /*Gestion des emplacements graphiques*/
  boiteMenu.pack_start(barreMenu,Gtk::PACK_SHRINK);
  boiteJoueur.pack_start(avatarJoueur);
  boiteJoueur.pack_end(pseudoJoueur,Gtk::PACK_SHRINK);
  Jeu.pack_start(boiteMenu,Gtk::PACK_SHRINK);
  boite2.pack_start(Grille);
  boite2.pack_end(boiteJoueur);
  Jeu.pack_start(boite2,Gtk::PACK_SHRINK);
  add(Jeu);

  /*Gestion des connexions*/
  subItemQuitter.signal_activate().connect(sigc::mem_fun(*this,&VueG::close));
  subItemRegles.signal_activate().connect(sigc::mem_fun(*this,&VueG::afficherInstructions));
  //subItemDifficulte.signal_activate().connect(sigc::mem_fun(*this,&VueG::afficherDifficulte));
  afficherPremierePage();
  afficherDialogue();
  afficherDifficulte();
  
  show_all_children();
}
  
void VueG::update(double &info){
    info +=1;
}

void VueG::close(){
  Gtk::Window::close();
}

VueG::~VueG(){}

void VueG::afficherPremierePage() {
  //Création de la boîte de dialogue personnalisée.
  firstWindow introWindow(this);
  introWindow.resize(400,50);
  int reponse = introWindow.run(); //Lancer la boîte de dialogue.
  if(reponse==Gtk::RESPONSE_HELP){
    afficherInstructions();
  }
}

void VueG::afficherDialogue() {
  //Création de la boîte de dialogue personnalisée.
  Dialogue dialogue("Nom du joueur", this, "Veuillez entrer votre pseudo :");
  int reponse = dialogue.run(); //Lancer la boîte de dialogue.
    
    if(reponse == Gtk::RESPONSE_OK) { //Si l'utilisateur clique sur Valider.
      pseudoJoueur.set_text(dialogue.get_texte());
    }
}


void VueG::afficherInstructions(){
  Gtk::MessageDialog winInstruction(*this, "<big><b>Regles du Demineur</b></big>", true);
  winInstruction.set_title("Regles du jeu");
  winInstruction.set_secondary_text("Le champ de mines du Démineur est représenté par une grille, dont la taille varie avec la difficulte. Chaque case de la grille peut soit cacher une mine, soit etre vide. Le but du jeu est de decouvrir toutes les cases libres sans faire exploser les mines, c est-à-dire sans cliquer sur les cases qui les dissimulent.\n\nLorsque vous cliquez sur une case libre comportant au moins une mine dans l une de ses cases avoisinantes, un chiffre apparaît, indiquant ce nombre de mines.Si en revanche toutes les cases adjacentes sont vides, une case vide est affichee et la meme opération est repetee sur ces cases, et ce jusqu a ce que la zone vide soit entierement delimitee par des chiffres.\n\nVous pouvez signaler les cases contenant des mines presumees par un drapeau en cliquant sur le bouton — mais ce n est aucunement obligatoire. Il faut faire attention a ne pas signaler une case saine par un drapeau, car cela peut vous induire en erreur");
  winInstruction.run();
  }

void VueG::afficherDifficulte(){
  choiceWindow choix(this, "Difficulte","Choisissez la difficulte","Facile","Moyen","Difficile");
  int reponse = choix.run();
  if(reponse == Gtk::RESPONSE_OK) {
      
    }
  
}
