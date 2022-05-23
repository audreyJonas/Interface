#pragma once

#include "Modele.hpp"
#include "Demineur.h"
#include "VueG.hpp"

class Controleur {
private:
  Demineur *m;
  VueG *v;
  int premier_coup = 1;
  
public:
//etablit la connexion entre le modele et la vue 
//gestionnaire de signaux pour les boutons 

  Controleur(Demineur *mm, VueG *vv) : m(mm), v(vv) {
    v->addGridListener(this);
    v->addBDrapeauxListener(this);
  }

  void on_gridBox_button(int l, int c){
    //fonction qui lie le clique sur les boutons à la découverte d'une case
    if (premier_coup == 1){
      m->configDemineur(v->Difficulte);
      m->poser_bombe(l,c);
      premier_coup=0;
    }
    m->update(l,c);	     
  }

  void on_drapeaux_button(){
    std::cout<<m->drapeaux<<std::endl;
    //fonction qui lie le clique sur le bouton Drapeaux au mode drapeau
    m->drapeaux=!(m->drapeaux);
  }
};
