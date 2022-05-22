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
  }

  void on_gridBox_button(int l, int c){
    //fonction qui lie le clique sur les boutons à la découverte d'une case
    if (premier_coup == 1){
      m->poser_bombe(l,c);
      premier_coup=0;
    }
    m->update(l,c);
    /* m->jouer(l,c);
       m->affichage();*/
    
	     
  }


};
