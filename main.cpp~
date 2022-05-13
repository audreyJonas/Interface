#include <gtkmm.h>
#include <gtkmm/application.h>
#include "VueG.hpp"

int main(int argc,char * argv []) {
    /*auto app = Gtk::Application::create(argc,argv);
    Gtk::Window window ;
    window.set_default_size(300,100);
    return app->run(window);
*/
    /*La fonction main du programme principal consiste simplement à passer à la méthode run de
l’application une instance de Vue.*/
    auto app =Gtk::Application::create(argc,argv);
    VueG *vg = new VueG();
    vg->set_default_size(700,600);
    vg->set_title("Jeu du Démineur");
    return app->run(*vg);
}
