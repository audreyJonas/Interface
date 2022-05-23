#include <iomanip>
#include <cstdio>
#include <vector>
#include <iostream>
#include <cstdlib>

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
  boiteJeu(true),
  boiteJoueur(false),
  Jeu(false),
  Grille(false),
  avatarJoueur("Avatars/yoshi3.png"),
  bDrapeaux("Drapeaux")
 
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
  bDrapeaux.set_active(false);
  boiteMenu.pack_start(barreMenu,Gtk::PACK_SHRINK);
  boiteJoueur.pack_start(avatarJoueur);
  boiteJoueur.pack_end(pseudoJoueur,Gtk::PACK_SHRINK);
  Jeu.pack_start(boiteMenu,Gtk::PACK_SHRINK);
  //Jeu.pack_start(bJouer);
  Grille.pack_start(bDrapeaux);
  Grille.pack_start(GrilleJeu);
  boiteJeu.pack_end(boiteJoueur,Gtk::PACK_SHRINK);
  Jeu.pack_start(boiteJeu,Gtk::PACK_SHRINK);
  Jeu.pack_start(Grille, Gtk::PACK_SHRINK);
  add(Jeu);

  /*Gestion des connexions*/
  subItemQuitter.signal_activate().connect(sigc::mem_fun(*this,&VueG::close));
  subItemRegles.signal_activate().connect(sigc::mem_fun(*this,&VueG::afficherInstructions));
  afficherPremierePage();
  afficherDialogue();
  afficherDifficulte();  
  show_all_children();
}
  
void VueG::update(std::vector<std::string> &info, int& res){
  auto grille=this->get_casesGrille();
  for(auto i=0; i<info.size(); i++){
    if(info[i]!="#"){
      grille[i]->set_label(info[i]);
      if(!this->bDrapeaux.get_active()){
	grille[i]->set_sensitive(false);
      }
    }
  }
  if(res == 0){
    Gtk::MessageDialog winInstruction(*this, "Vous avez perdu", false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);
    winInstruction.set_title("Fin du jeu");
    winInstruction.set_secondary_text("Aie attention aux bombes! Vous gagnerez surement la prochaine fois.");
    winInstruction.run();
  }
  else if(res==-1){
    Gtk::MessageDialog winInstruction(*this, "Vous avez Gagne", false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK_CANCEL);
    winInstruction.set_title("Fin du jeu");
    winInstruction.set_secondary_text("FELICITATIONS !!! N hesitez pas a rejouer en augmentant la difficulte");
    winInstruction.run();
  }
  
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
  choix.run();
  switch(choix.getOption()){
  case 1:this->Difficulte=10;break;
  case 2: this->Difficulte=20;break;
  case 3: this->Difficulte=30;break;
  }
  initialiserGrille(this->Difficulte,this->Difficulte);
}

void VueG::initialiserGrille(const int M, const int N){
  GrilleJeu.set_row_homogeneous(true);
  GrilleJeu.set_column_homogeneous(true);
  for(int i=0; i<M; i++){
    for(int j=0; j<N; j++){
      auto btn = new Mine();
      btn->set_ligne(i);
      btn->set_colonne(j);
      casesGrille.push_back(btn);
      btn->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &VueG::testActive),btn->get_ligne(),btn->get_colonne(),M));
      GrilleJeu.attach(*btn,btn->get_colonne(),btn->get_ligne());
      btn->show();
    }
  } 
}

void VueG::addGridListener(Controleur* c){
  for(auto wid: casesGrille){
    (*wid).signal_clicked().connect(sigc::bind(sigc::mem_fun(*c, &Controleur::on_gridBox_button),(*wid).get_ligne(),(*wid).get_colonne()));
  }  
}

void VueG::addBDrapeauxListener(Controleur* c){
  bDrapeaux.signal_toggled().connect(sigc::mem_fun(*c, &Controleur::on_drapeaux_button));
}


void VueG::testActive(int l, int c,int M){
  auto caseCliquee =casesGrille[l*M+c];
  if(!this->bDrapeaux.get_active()){
    caseCliquee->set_sensitive(false);
  }  
}

std::vector<Mine*> VueG::get_casesGrille(){
  return this->casesGrille;
}

