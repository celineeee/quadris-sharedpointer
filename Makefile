CXX = g++
CXXFLAGS = -std=c++11 -L/usr/X11R6/lib -I/usr/X11R6/include -lX11 -I/opt/X11/include
EXEC = quadris
OBJECTS = main.o block.o blockstate.o blocktype.o board.o cell.o cellstate.o gamestate.o generator.o graphicsdisplay.o heavy.o level.o levelzero.o levelone.o leveltwo.o levelthree.o levelfour.o state.o subject.o textdisplay.o window.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
