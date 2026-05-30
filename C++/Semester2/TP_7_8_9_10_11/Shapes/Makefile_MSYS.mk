# Makefile pour EZ-Draw++ : version pour Windows/MSYS
#
# 01/02/2017 - Eric.Remy@univ-amu.fr

# Variables pour Unix/X11

ifeq ($(CXX),)
CXX=g++
endif
CFLAGS   = -g -Wall -pedantic -O2 -D_WIN32
CXXFLAGS = $(CFLAGS) -std=c++20 -Wfatal-errors
LIBS     = -lgdi32 -lmsimg32
RM       = rm -f
EXE      = .exe

OBJECTS= Point.o Shape.o Rectangle.o SetOfShapes.o
OBJECTS+= Ellipse.o Square.o Circle.o Label.o
OBJECTS+= MyWindow.o main.o ez-draw++.o

# Liste les fichiers de dépendances en remplaçant l'extension *.o par *.d)
DEPENDS=$(OBJECTS:.o=.d)

.PHONY:: all clean distclean depends cleandepends

# Rajoutez vos executables C++ a la fin de EXECSPP =
#
EXECSPP = ShapesEditor$(EXE)

all :: depends $(EXECSPP)

# Règle générale qui indique comment compiler n'importe quel fichier XXX.cpp en un fichier XXX.o.
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $*.cpp

ShapesEditor$(EXE) : $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS)

depends : $(DEPENDS) # Produire les dépendances (en général) consiste à produire chaque fichier de dépendance listé

cleandepends :
	rm -f $(DEPENDS)

# Règle qui génère un fichier de dépendance XXX.d pour chaque fichier XXX.cpp
%.d : %.cpp
	$(CXX) -MM $(CXXFLAGS) $< -o $@

clean ::
	-$(RM) *.o core

distclean :: clean cleandepends
	-$(RM) $(EXECSPP)

# Inclue les fichiers de dépendance du projet
include $(DEPENDS)
