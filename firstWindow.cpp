#include <iomanip>

#include "firstWindow.hpp"
#include "VueG.hpp"

firstWindow::firstWindow(Gtk::Window* parent):
  Gtk::Dialog("Bienvenue", *parent),
  box1(get_content_area()),
  box2(false,1),
  box3(Gtk::BUTTONBOX_END),
  bInstructions("Instructions"),
  zoneTexte("Bienvenue dans cette version numerique du Demineur!\nSi vous souhaitez lire les regles du jeu avant de commencer,\ncliquer sur le bouton 'Instructions', sinon cliquer sur 'Suivant'\n\nVous pourrez avoir acces aux regles en cours de partie\nen cliquant sur le menu 'Aide'")
  // box2(true, 10),
  //box3(Gtk::BUTTONBOX_END,20),
{
  bInstructions.set_can_focus(false);
  zoneTexte.set_justify(Gtk::JUSTIFY_FILL);
  zoneTexte.set_alignment(Gtk::ALIGN_CENTER);
  //zoneTexte.set_line_wrap(true);
  box3.pack_end(bInstructions);
  //box2.pack_start(zoneTexte);
   box1->pack_start(box3,Gtk::PACK_SHRINK);
   box1->pack_start(zoneTexte,Gtk::PACK_SHRINK);
   add_button("Quitter", Gtk::RESPONSE_CANCEL);
   add_button("Suivant", Gtk::RESPONSE_OK);
   bInstructions.signal_clicked().connect(sigc::mem_fun(*this,&firstWindow::afficherInstructions));
  //box4(true,100),

  /*
  bExit("Quitter"),
  bSuivant("Suivant"),
  bInstructions("Instructions"),
  zoneTexte("\tBienvenu dans cette version numerique du Demineur!\nSi vous souhaitez lire les regles du jeu avant de commencer, cliquer sur le bouton 'Instructions', sinon cliquer sur 'Suivant'\n\nVous pourrez avoir acces aux regles en cours de partie en cliquant sur le menu 'Aide'")
{
  // buf1_textPres= Gtk::TextBuffer::create();
  //buf1_textPres->set_text("Texte de presentation du jeu");
  zoneTexte.set_justify(Gtk::JUSTIFY_CENTER);
  zoneTexte.set_alignment(Gtk::ALIGN_CENTER);
  zoneTexte.set_line_wrap();
  //zoneTexte.set_markup("<big><span face='Arial'>coucou</span></big>");
  box3.pack_end(bSuivant);
    box2.pack_start(bExit);
    box2.pack_end(bInstructions);
    box1->pack_start(box3);
    box4.pack_start(zoneTexte);
		    //,Gtk::PACK_SHRINK);
    box1->pack_start(box4);
    box1->pack_end(box2);
    //add(box1);
    bExit.signal_clicked().connect(sigc::mem_fun(*this,&firstWindow::close));
    bSuivant.signal_clicked().connect(sigc::mem_fun(*this,&firstWindow::suivant));
    bInstructions.signal_clicked().connect(sigc::mem_fun(*this,&firstWindow::afficherInstructions));*/
  
    show_all_children ();

}

firstWindow::~firstWindow(){}

void firstWindow::close(){
    Gtk::Window::close();
    }

void firstWindow::suivant(){
  Gtk::Window::close();
}

void firstWindow::afficherInstructions(){
  Gtk::MessageDialog winInstruction(*this, "<big><b>Regle du Demineur</b></big>", true);
  winInstruction.set_title("Regles du jeu");
  winInstruction.set_secondary_text("Le champ de mines du D??mineur est repr??sent?? par une grille, dont la taille varie avec la difficulte. Chaque case de la grille peut soit cacher une mine, soit etre vide. Le but du jeu est de decouvrir toutes les cases libres sans faire exploser les mines, c est-??-dire sans cliquer sur les cases qui les dissimulent.\n\nLorsque vous cliquez sur une case libre comportant au moins une mine dans l une de ses cases avoisinantes, un chiffre appara??t, indiquant ce nombre de mines.Si en revanche toutes les cases adjacentes sont vides, une case vide est affichee et la meme op??ration est repetee sur ces cases, et ce jusqu a ce que la zone vide soit entierement delimitee par des chiffres.\n\nVous pouvez signaler les cases contenant des mines presumees par un drapeau en cliquant sur le bouton ??? mais ce n est aucunement obligatoire. Il faut faire attention a ne pas signaler une case saine par un drapeau, car cela peut vous induire en erreur");
  winInstruction.run();
  }
