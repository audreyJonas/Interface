#pragma once

#include "Modele.hpp"
#include "VueG.hpp"

class Controleur {
private:
  Modele *m;
  VueG *v;
public:
//établit la connexion entre le modèle et la vue 
//gestionnaire de signaux pour les boutons 

  Controleur(Modele *mm, VueG *vv) : m(mm), v(vv) {
  }


};
