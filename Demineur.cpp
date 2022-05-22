#include "Demineur.h"
using namespace std;
#include <iomanip>

Type_history test;


Demineur::Demineur(){}

Demineur::Demineur(const int difficulte,const int mon_nb_bombe): difficulte_(difficulte),nb_bombes_(mon_nb_bombe), Mon_jeu_(){
    if (nb_bombes_ == 0 ){
        nb_bombes_ = difficulte_;
    }
    Mon_jeu_.resize(difficulte+2);
    for ( int i = 0; i < difficulte+2; ++i )
        Mon_jeu_[i].resize(difficulte+2);
}

Demineur::~Demineur()
{
    //dtor
}

void Demineur::poser_bombe(const int x, const int y){
    int bomb_x, bomb_y;
    int nb_bombes = nb_bombes_;
    for (int i=0 ; i < nb_bombes; ++i){                                         //Choix des coordonn�es des 10 bombes

        srand(time(NULL)+nb_bombes+i);

        bomb_x = ((rand() % difficulte_)+1);
        bomb_y = ((rand() % difficulte_)+1);


	//cout << "x :" << bomb_x<< " | y :" << bomb_y << endl;
        if ((Mon_jeu_[bomb_x][bomb_y].nb_bombe_ != je_suis_une_bombe) & !((bomb_x == (x+1)) & (bomb_y == (y+1)))){
	  //cout <<"OK"<<endl;
            Mon_jeu_[bomb_x][bomb_y].nb_bombe_ = je_suis_une_bombe;               // la case devient une bombe puis on remplit les case aux alentours
            ++Mon_jeu_[bomb_x-1][bomb_y-1].nb_bombe_ ;
            ++Mon_jeu_[bomb_x-1][bomb_y].nb_bombe_ ;
            ++Mon_jeu_[bomb_x-1][bomb_y+1].nb_bombe_ ;
            ++Mon_jeu_[bomb_x][bomb_y-1].nb_bombe_ ;
            ++Mon_jeu_[bomb_x][bomb_y+1].nb_bombe_ ;
            ++Mon_jeu_[bomb_x+1][bomb_y-1].nb_bombe_ ;
            ++Mon_jeu_[bomb_x+1][bomb_y].nb_bombe_ ;
            ++Mon_jeu_[bomb_x+1][bomb_y+1].nb_bombe_ ;
        }
        else                                                                       // si la case est deja une bombe, on annule l'iteration
            ++nb_bombes;
    }
};

void Demineur::affichage() {
  std::vector<std::string> valeur;
    for (int ligne=1 ; ligne <= difficulte_ ; ++ligne) {
        for (int colonne=1 ; colonne <= difficulte_ ; ++colonne) {
            if (Mon_jeu_[ligne][colonne].etat_ == NON_DECOUVERTE ) {
	      valeur.push_back("#");
            }
            else if (Mon_jeu_[ligne][colonne].etat_ == DRAPEAU ) {
	      valeur.push_back("F");
            }
            else if (Mon_jeu_[ligne][colonne].etat_== DECOUVERTE) {
                if (Mon_jeu_[ligne][colonne].nb_bombe_ >= je_suis_une_bombe) {
		  std::cout<<"bombe"<<std::endl;
		  valeur.push_back("B");
                    }
                else{
		  valeur.push_back(to_string(Mon_jeu_[ligne][colonne].nb_bombe_));
		}
            }
        }
    }
    notifierObservateurs(valeur);
}

void Demineur::affichage_final() {
  std::vector<std::string> valeur;

    for (int ligne=1 ; ligne <= difficulte_ ; ++ligne) {
        for (int colonne=1 ; colonne <= difficulte_ ; ++colonne) {
	  //valeur.push_back(" ");
            if (Mon_jeu_[ligne][colonne].nb_bombe_ >= je_suis_une_bombe) {
	      valeur.push_back("B");
                }
            else if ((Mon_jeu_[ligne][colonne].nb_bombe_ < je_suis_une_bombe) & (Mon_jeu_[ligne][colonne].nb_bombe_ >= 0)) {
	      valeur.push_back(to_string(Mon_jeu_[ligne][colonne].nb_bombe_));
            }
        }
    }
    notifierObservateurs(valeur);
}

int Demineur::jouer(const int x, const int y){
    if (Mon_jeu_[x+1][y+1].nb_bombe_ >= je_suis_une_bombe)
        return 0;
    else if (Mon_jeu_[x+1][y+1].etat_ == DECOUVERTE)
        return 2;

    else if(Mon_jeu_[x+1][y+1].etat_ == DRAPEAU)
        return 3;

    else if (Mon_jeu_[x+1][y+1].nb_bombe_ != 0) {
        Mon_jeu_[x+1][y+1].etat_ = DECOUVERTE;

        test.position = make_pair(x+1,y+1);
        test.etat_=DECOUVERTE;
        game_history_.add_modif(test);

        ++nb_case_decouvert_;


    }
    else{
        decouverte(x+1,y+1);
    }

    ++game_history_.tour_actuelle;
    ++game_history_.tour_total;
    
    if(nb_case_decouvert_ < difficulte_*difficulte_ - nb_bombes_ )
        return 1;
    else
        return -1;
}

int Demineur::drapeau(const int x, const int y){
    cout <<"test"<<endl;
    if (Mon_jeu_[x+1][y+1].etat_ == DRAPEAU){
        Mon_jeu_[x+1][y+1].etat_ = NON_DECOUVERTE;
        cout <<"test1"<<endl;
        return 1;
    }
    else if (Mon_jeu_[x+1][y+1].etat_ == DECOUVERTE){
        return 4;
    }
    cout <<"test2"<<endl;
    Mon_jeu_[x+1][y+1].etat_ = DRAPEAU;

    test.position = make_pair(x+1,y+1);
    test.etat_=DRAPEAU;
    game_history_.add_modif(test);

    ++game_history_.tour_actuelle;
    ++game_history_.tour_total;

    return 1;

};


void Demineur::decouverte (const int x, const int y){
    if ((x > 0) & (y > 0) & (x < difficulte_ +1) & (y < difficulte_ +1)) {

        //cout << "x : " << x-1 << "  y : " << y-1 << endl;
        /////////////////////////////////////////////////////////////////           x-1 / y-1
            if (Mon_jeu_[x-1][y-1].etat_ == NON_DECOUVERTE ) {
                if (Mon_jeu_[x-1][y-1].nb_bombe_ == 0)
                    decouverte(x-1,y-1);

                else if (Mon_jeu_[x-1][y-1].nb_bombe_ <9 ){
                    Mon_jeu_[x-1][y-1].etat_ = DECOUVERTE;

                    if ((x-1 > 0) & (y-1 > 0) ){
                        test.position = make_pair(x-1,y-1);
                        test.etat_=DECOUVERTE;
                        game_history_.add_modif(test);
                        ++nb_case_decouvert_;
                    }
                }
            }

        /////////////////////////////////////////////////////////////////           x-1 / y
            if (Mon_jeu_[x-1][y].etat_ == NON_DECOUVERTE ) {
                if (Mon_jeu_[x-1][y].nb_bombe_ == 0) {
                    decouverte(x-1,y);
                }
                else if (Mon_jeu_[x-1][y].nb_bombe_ <9 ){
                    Mon_jeu_[x-1][y].etat_ = DECOUVERTE;

                    if (x-1 > 0){
                        test.position = make_pair(x-1,y);
                        test.etat_=DECOUVERTE;
                        game_history_.add_modif(test);
                        ++nb_case_decouvert_;
                    }
                }
            }

         /////////////////////////////////////////////////////////////////           x-1 / y+1
            if (Mon_jeu_[x-1][y+1].etat_ == NON_DECOUVERTE ) {
               if ((Mon_jeu_[x-1][y+1].nb_bombe_ == 0) & (x > 0) & (y < difficulte_ +1)) {
                    decouverte(x-1,y+1);
                }
                else if (Mon_jeu_[x-1][y+1].nb_bombe_ <9 ){
                    Mon_jeu_[x-1][y+1].etat_ = DECOUVERTE;

                    if ((x-1 > 0) & (y+1 < difficulte_ +1)){
                        test.position = make_pair(x-1,y+1);
                        test.etat_=DECOUVERTE;
                        game_history_.add_modif(test);
                        ++nb_case_decouvert_;
                    }
                }
             }

        /////////////////////////////////////////////////////////////////           x / y-1
            if (Mon_jeu_[x][y-1].etat_ == NON_DECOUVERTE ) {
                if (Mon_jeu_[x][y-1].nb_bombe_ == 0) {
                    decouverte(x,y-1);
                }
                else if (Mon_jeu_[x][y-1].nb_bombe_ <9 ){
                    Mon_jeu_[x][y-1].etat_ = DECOUVERTE;

                    if (y-1 > 0){
                        test.position = make_pair(x,y-1);
                        test.etat_=DECOUVERTE;
                        game_history_.add_modif(test);
                        ++nb_case_decouvert_;
                    }
                }
            }
        /////////////////////////////////////////////////////////////////           x / y
            if (Mon_jeu_[x][y].etat_ == NON_DECOUVERTE ) {

                if (Mon_jeu_[x][y].nb_bombe_ < 9 )  {
                    Mon_jeu_[x][y].etat_ = DECOUVERTE;
                    test.position = make_pair(x,y);
                    test.etat_=DECOUVERTE;
                    game_history_.add_modif(test);
                    ++nb_case_decouvert_;
                }
/*

                if (Mon_jeu_[x][y].nb_bombe_ == 0 )  {
                    Mon_jeu_[x][y].etat_ = DECOUVERTE;
                    Mon_jeu_[x][y].Case_history_.push_back(make_pair(tour_actuelle,DECOUVERTE));
                    ++nb_case_decouvert_;
                }
                else if (Mon_jeu_[x][y].nb_bombe_ <9 ){
                    Mon_jeu_[x][y].etat_ = DECOUVERTE;
                    Mon_jeu_[x][y].Case_history_.push_back(make_pair(tour_actuelle,DECOUVERTE));
                    ++nb_case_decouvert_;
                }
*/
            }
        /////////////////////////////////////////////////////////////////           x / y+1
            if (Mon_jeu_[x][y+1].etat_ == NON_DECOUVERTE ) {
                if (Mon_jeu_[x][y+1].nb_bombe_ == 0) {
                    decouverte(x,y+1);
                }
                else if (Mon_jeu_[x][y+1].nb_bombe_ <9 ){
                    Mon_jeu_[x][y+1].etat_ = DECOUVERTE;

                    if (y+1 < difficulte_ +1){
                        test.position = make_pair(x,y+1);
                        test.etat_=DECOUVERTE;
                        game_history_.add_modif(test);
                        ++nb_case_decouvert_;
                    }
                }
            }
        /////////////////////////////////////////////////////////////////           x+1 / y-1
            if (Mon_jeu_[x+1][y-1].etat_ == NON_DECOUVERTE ) {
                if (Mon_jeu_[x+1][y-1].nb_bombe_ == 0) {
                    decouverte(x+1,y-1);
                }
                else if (Mon_jeu_[x+1][y-1].nb_bombe_ <9 ){
                    Mon_jeu_[x+1][y-1].etat_ = DECOUVERTE;

                    if ((y-1 > 0) & (x+1 < difficulte_ +1)){
                        test.position = make_pair(x+1,y-1);
                        test.etat_=DECOUVERTE;
                        game_history_.add_modif(test);
                        ++nb_case_decouvert_;
                    }
                }
            }
        /////////////////////////////////////////////////////////////////           x+1 / y
            if (Mon_jeu_[x+1][y].etat_ == NON_DECOUVERTE ) {
                if (Mon_jeu_[x+1][y].nb_bombe_ == 0) {
                    decouverte(x+1,y);
                }
                else if (Mon_jeu_[x+1][y].nb_bombe_ <9 ){
                    Mon_jeu_[x+1][y].etat_ = DECOUVERTE;

                    if (x+1 < difficulte_ +1){
                        test.position = make_pair(x+1,y);
                        test.etat_=DECOUVERTE;
                        game_history_.add_modif(test);
                        ++nb_case_decouvert_;
                    }
                }
            }
        /////////////////////////////////////////////////////////////////           x+1 / y+1
            if (Mon_jeu_[x+1][y+1].etat_ == NON_DECOUVERTE ) {
                if (Mon_jeu_[x+1][y+1].nb_bombe_ == 0) {
                    decouverte(x+1,y+1);
                }
                else if (Mon_jeu_[x+1][y+1].nb_bombe_ <9 ){
                    Mon_jeu_[x+1][y+1].etat_ = DECOUVERTE;

                    if ((x+1 < difficulte_ +1) & (y+1 < difficulte_ +1)){
                        test.position = make_pair(x+1,y+1);
                        test.etat_=DECOUVERTE;
                        game_history_.add_modif(test);
                        ++nb_case_decouvert_;
                    }
                }
            }
        }

}

void Demineur::update(const int x, const int y){
  // int difficulte_choisie;
  // int no_death_mode=1;
  //  int nb_bombes =0;
  // int classic_game_mode = 1;

//Dialogue, choix de difficulte
//Affichage du tableau des scores
//Appel du constructeur de d�mineur avec la difficulte+ nb bombes
    
//Question du no_deathMode 
// Chrono
//Gestion des erreurs et du no death (case deja decouverte etc)
    /*   if (premier_coup == 1){
      Mon_jeu.poser_bombe(x,y);
      premier_coup=0;
      }*/
    partie = this->jouer(x,y);
    if(partie!=-1 and partie!=0){ //-1 condition du joueur qui a gagn�
      //conditions sur partie
      this->affichage();
    }
    else{
      //status perdant
      this->affichage_final();
      if(partie==0){
	//renvoie status perdant
	std::cout<<"status perdant"<<std::endl;
      }
      else{
	//renvoie status gagnant
      }
    
    }
}
    //else {
    
        //auto duration = ((int) chrono::duration<double, std::milli> (chrono::steady_clock::now() - start).count()/10) / 100.0;
/*
        if (no_death_mode ==0){
            cout <<"Voulez vous enregistrer votre scores ? Y or N --> ";
            cin >> choix;
            if (choix == "Y"){
                score.add_score(Mon_jeu.difficulte_,duration,nb_bombes);
                score.print_scores(difficulte_choisie);
            }
        }
*/
  



void Demineur::undo(){
    if (game_history_.tour_actuelle > 0){
        game_history_.Undo_Mode=1;
        --game_history_.tour_actuelle;
        for(auto e : game_history_.history_[game_history_.tour_actuelle]){
            --nb_case_decouvert_;
            if (e.etat_ == NON_DECOUVERTE)
                Mon_jeu_[e.position.first][e.position.second].etat_ = DECOUVERTE;
            else
                Mon_jeu_[e.position.first][e.position.second].etat_ = NON_DECOUVERTE;
        }
    }
};

void Demineur::redo(){
    if (game_history_.tour_actuelle < game_history_.tour_total){
        for(auto e : game_history_.history_[game_history_.tour_actuelle]){
            ++nb_case_decouvert_;
            Mon_jeu_[e.position.first][e.position.second].etat_ = e.etat_;
        }
        ++game_history_.tour_actuelle;
    }
};