#include <iomanip>

#include "VueG.hpp"
#include "Controleur.hpp"

VueG::VueG():
  b("Afficher le dialogue")
{
  afficherPremierePage();
  //show_all_children();
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
  if(reponse == Gtk::RESPONSE_OK){
    introWindow.close();
    afficherDialogue();
  }
}

void VueG::afficherDialogue() {
    //Création de la boîte de dialogue personnalisée.
    Dialogue dialogue("Nom du joueur", this, "Veuillez entrer votre pseudo :");
    //Modifier le texte de la zone de texte par celui de l'étiquette.
    dialogue.set_texte(etiquette.get_text());
    
    int reponse = dialogue.run(); //Lancer la boîte de dialogue.
    
    if(reponse == Gtk::RESPONSE_OK) { //Si l'utilisateur clique sur Valider.
        //etiquette.set_text(dialogue.get_texte());
    }
}
