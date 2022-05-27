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
  subItemFichierScores("Scores"),
  subItemQuitter(Gtk::Stock::CLOSE),
  subItemRegles(Gtk::Stock::HELP),
  subItemMode("Mode"),
  // subItemDimensions("Dimensions"),
  boiteMenu(false),
  boiteJeu(false),
  Grille(false),
  boiteJoueur(false),
  Jeu(false),
  avatarJoueur("./Avatars/yoshi.png"),
  bDrapeaux("Drapeaux"),
  bRestart("Nouvelle Partie"),
  bUndo(Gtk::Stock::GO_BACK),
  bRedo(Gtk::Stock::GO_FORWARD)
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
  Parametres.append(subItemMode);
  //Parametres.append(subItemDimensions);

  /*Gestion des emplacements graphiques*/
  bDrapeaux.set_active(false);
  boiteMenu.pack_start(barreMenu,Gtk::PACK_SHRINK);
  boiteMenu.pack_start(bUndo,Gtk::PACK_SHRINK);
  boiteMenu.pack_start(bRedo,Gtk::PACK_SHRINK);
  boiteJoueur.pack_start(avatarJoueur,Gtk::PACK_SHRINK);
  boiteJoueur.pack_end(pseudoJoueur,Gtk::PACK_SHRINK);
  Jeu.pack_start(boiteMenu,Gtk::PACK_SHRINK);
  Grille.pack_start(bDrapeaux);
  Grille.pack_start(GrilleJeu);
  boiteJeu.pack_end(boiteJoueur,Gtk::PACK_SHRINK);
  Jeu.pack_end(bRestart,Gtk::PACK_SHRINK);
  Jeu.pack_start(boiteJeu,Gtk::PACK_SHRINK);
  Jeu.pack_start(Grille, Gtk::PACK_SHRINK);
  add(Jeu);

  
  /*Gestion des connexions*/
  subItemQuitter.signal_activate().connect(sigc::mem_fun(*this,&VueG::close));
  subItemRegles.signal_activate().connect(sigc::mem_fun(*this,&VueG::afficherInstructions));
  subItemFichierScores.signal_activate().connect(sigc::mem_fun(*this,&VueG::afficherFichierScores));
  afficherPremierePage();
  afficherDialogue();
  afficherDifficulte();

  this->start = chrono::steady_clock::now();
  show_all_children();
}

void VueG::update(std::vector<std::string> &info, int& res){
  auto grille=this->get_casesGrille();
  for(auto i=0; i<info.size(); i++){
    auto img = new Gtk::Image("./Icons/"+info[i]+".png");
    grille[i]->set_image(*img);
    if(info[i]!="n" and info[i]!="flag"){
      //si une case est découvete et n'est pas un drapeau
      grille[i]->set_sensitive(false);//elle n'est plus cliquable
	}
    else if(info[i]=="n" and !grille[i]->get_sensitive()){
      //si une case est non découverte mais incliquable -> undo réalisé
      grille[i]->set_sensitive(true); //elle redevient cliquable
    }
    
  }
  if(res == 0){ //perdu
    Gtk::MessageDialog winInstruction(*this, "Vous avez perdu", false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK);
    winInstruction.set_title("Fin du jeu");
    winInstruction.set_secondary_text("Aie attention aux bombes! Vous gagnerez surement la prochaine fois. Pour rejouer cliquez sue Nouvelle partie");
    winInstruction.run();
  }
  else if(res==-1){ //gagné
    auto duration = ((int) chrono::duration<double, std::milli> (chrono::steady_clock::now() - start).count()/10) / 100.0;
    std::ostringstream temps;
    temps << duration;
    Gtk::MessageDialog winInstruction(*this, "Vous avez Gagne", false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_YES_NO);
    winInstruction.set_title("Fin du jeu");
    winInstruction.set_secondary_text("FELICITATIONS !!! Vous avez mis: " + temps.str() + " secondes. N hesitez pas a rejouer en augmentant la difficulte.\n\n Souhaitez-vous enregistrer votre score?");
    int reponse = winInstruction.run();
    if(reponse == Gtk::RESPONSE_YES) {
      this->score.add_score(this->Difficulte,duration,this->Bombes);
      afficherFichierScores();
    }
  }
  else if(res==2){ //perdu en no_death_mode
    Gtk::MessageDialog winInstruction(*this, "Bombe", false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK);
    winInstruction.set_title("No death mode");
    winInstruction.set_secondary_text("Vous avez selectionne une bombe, votre derniere action a ete annulee");
    winInstruction.run();
  }
  else if(res==3){ //gagné en no_death_mode
    std::cout<<"test"<<std::endl;
    Gtk::MessageDialog winInstruction(*this, "Vous avez Gagne", false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_OK);
    winInstruction.set_title("Fin du jeu");
    winInstruction.set_secondary_text("FELICITATIONS !!! N hesitez pas a rejouer en augmentant la difficulte.\n\n Souhaitez-vous enregistrer votre score?");
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
      this->pseudo=dialogue.get_texte();
      pseudoJoueur.set_text(this->pseudo);
    }
}


void VueG::afficherInstructions(){
  Gtk::MessageDialog winInstruction(*this, "<big><b>Regles du Demineur</b></big>", true);
  winInstruction.set_title("Regles du jeu");
  winInstruction.set_secondary_text("Le champ de mines du Démineur est représenté par une grille, dont la taille varie avec la difficulte. Chaque case de la grille peut soit cacher une mine, soit etre vide. Le but du jeu est de decouvrir toutes les cases libres sans faire exploser les mines, c est-à-dire sans cliquer sur les cases qui les dissimulent.\n\nLorsque vous cliquez sur une case libre comportant au moins une mine dans l une de ses cases avoisinantes, un chiffre apparaît, indiquant ce nombre de mines.Si en revanche toutes les cases adjacentes sont vides, une case vide est affichee et la meme opération est repetee sur ces cases, et ce jusqu a ce que la zone vide soit entierement delimitee par des chiffres.\n\nVous pouvez signaler les cases contenant des mines presumees par un drapeau en cliquant sur le bouton — mais ce n est aucunement obligatoire. Il faut faire attention a ne pas signaler une case saine par un drapeau, car cela peut vous induire en erreur");
  winInstruction.run();
  }

void VueG::afficherDifficulte(){
  choiceWindow choix(this, "Difficulte","Choisissez la difficulte","Facile","Moyen","Difficile","Choisir");
  choix.run();
  int difficulte, bombes;
  switch(choix.getOption()){
  case 1:difficulte=8;bombes=8;break;
  case 2: difficulte=14;bombes=8;break;
  case 3: difficulte=20;bombes=20;break;
  case 4: auto diff=afficherChoixDimensions(); difficulte=diff.first;bombes=diff.second;this->classic_game_mode=0;break;
  }
  this->Difficulte=difficulte;
  this->Bombes=bombes;
  initialiserGrille(this->Difficulte);
  this->score = score_file("score.txt", this->pseudo,this->classic_game_mode);
}

int VueG::afficherChoixMode(){
  Gtk::MessageDialog fenetreMode(*this, "Voulez vous jouer en \"no death mode\"?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
   fenetreMode.set_title("Mode ?");
   fenetreMode.set_secondary_text("Cela signifie que vous ne pourrez pas mourir et vous ne pourrez pas sauvegarder votre score");
   int resultat = fenetreMode.run();
   if(resultat == Gtk::RESPONSE_YES) { //S'il a cliqué sur Oui.
     return 1;
    }
   return 0;  
}


void VueG::afficherFichierScores(){
  std::string  fScore = (this->score.print_scores(this->Difficulte)).str();
  Gtk::MessageDialog fenetreScores(*this, "Fichier de Score", false);
  fenetreScores.set_title("Scores");
  fenetreScores.set_secondary_text(fScore);
  fenetreScores.run();    
}

std::pair<int,int> VueG::afficherChoixDimensions(){
  dimWindow fenetre_dimensions(this,"Dimensions","Nombre de bombes",5,2,20,1);
  fenetre_dimensions.run();
  return make_pair(fenetre_dimensions.get_dim(),fenetre_dimensions.get_bombes());  
}

void VueG::initialiserGrille(const int M){
  GrilleJeu.set_row_homogeneous(true);
  GrilleJeu.set_column_homogeneous(true);
  for(int i=0; i<M; i++){
    for(int j=0; j<M; j++){
      auto btn = new Mine();
      btn->set_ligne(i);
      btn->set_colonne(j);
      casesGrille.push_back(btn);
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

void VueG::addBRestartListener(Controleur* c){
  bRestart.signal_clicked().connect(sigc::mem_fun(*c, &Controleur::on_restart_button));
}

void VueG::addBUndoListener(Controleur* c){
  bUndo.signal_clicked().connect(sigc::mem_fun(*c, &Controleur::on_undo_button));
}

void VueG::addBRedoListener(Controleur* c){
  bRedo.signal_clicked().connect(sigc::mem_fun(*c, &Controleur::on_redo_button));
}

void VueG::addItemModeListener(Controleur* c){
  subItemMode.signal_activate().connect(sigc::mem_fun(*c,&Controleur::on_item_mode));
}

void VueG::testActive(int l, int c,int M){
  auto caseCliquee =casesGrille[l*M+c];
   if(!this->bDrapeaux.get_active()){
    caseCliquee->set_sensitive(false);
    }  
}

void VueG::resetGrille(){
  for(auto cell: casesGrille){
    GrilleJeu.remove(*cell);
  }
  casesGrille.erase(casesGrille.begin(),casesGrille.end());
  afficherDifficulte();
  this->start = chrono::steady_clock::now();
}

std::vector<Mine*> VueG::get_casesGrille(){
  return this->casesGrille;
}

