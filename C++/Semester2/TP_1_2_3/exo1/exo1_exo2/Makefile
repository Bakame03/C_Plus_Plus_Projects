# Compilateur et options de compilation
CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS = -L/usr/X11R6/lib -lX11 -lXext

# Cible par defaut (quand on tape juste "make")
all: calculatrice.exe tracer.exe

# Regle pour creer calculatrice.exe
calculatrice.exe: calculatrice.o Polynome.o
	$(CXX) $(CXXFLAGS) calculatrice.o Polynome.o -o calculatrice.exe

# Regle pour creer tracer.exe
tracer.exe: tracer.o Polynome.o ez-draw++.o
	$(CXX) $(CXXFLAGS) tracer.o Polynome.o ez-draw++.o -o tracer.exe $(LDFLAGS)

# Regles de compilation pour chaque fichier .cpp -> .o
calculatrice.o: calculatrice.cpp Polynome.hpp
	$(CXX) $(CXXFLAGS) -c calculatrice.cpp

tracer.o: tracer.cpp Polynome.hpp ez-draw++.hpp
	$(CXX) $(CXXFLAGS) -c tracer.cpp

Polynome.o: Polynome.cpp Polynome.hpp
	$(CXX) $(CXXFLAGS) -c Polynome.cpp

ez-draw++.o: ez-draw++.cpp ez-draw++.hpp
	$(CXX) $(CXXFLAGS) -c ez-draw++.cpp

# Regle pour tout nettoyer
clean:
	rm -f *.o *.exe

# Verifier les fuites memoire avec Valgrind (calculatrice)
test_calculatrice: calculatrice.exe
	valgrind --leak-check=full ./calculatrice.exe

# Verifier les fuites memoire avec Valgrind (tracer)
test_tracer: tracer.exe
	valgrind --leak-check=full ./tracer.exe
