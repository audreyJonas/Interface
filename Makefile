GTKMM_CF = `pkg-config gtkmm-3.0 --cflags`
GTKMM_LD = `pkg-config gtkmm-3.0 --libs`
CFLAGS = $(GTKMM_CF) -Wall    # les options du compilateur
LDFLAGS = $(GTKMM_LD)        # les options pour l'éditeur de liens

CC = g++          # le compilateur à utiliser

SRC = main.cpp VueG.cpp firstWindow.cpp Dialogue.cpp # les fichiers sources
PROG = main          # nom de l'exécutable
OBJS =  $(SRC:.cpp=.o) # les .o qui en découlent
.SUFFIXES: .cpp .o     # lien entre les suffixes

#règles
all: $(PROG)

# étapes de compilation et d'édition de liens
# $@ la cible  $^ toutes les dépendances	
$(PROG): $(OBJS)
	$(CC)  -o $@ $^ $(LDFLAGS)

firstWindow.o: firstWindow.hpp VueG.hpp
Dialogue.o: Dialogue.hpp
VueG.o: VueG.hpp Observateur.hpp firstWindow.hpp Dialogue.hpp
main.o: VueG.hpp Modele.hpp Observable.hpp Controleur.hpp  #les options du compilateur
# le lien entre .o et .c
# $< dernière dépendance	
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

# pour faire propre
.PHONY: clean
clean:
	rm -f *.o *~ core $(PROG)
