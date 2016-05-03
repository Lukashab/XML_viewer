CXX=g++
CXXFLAGS=-Wall -g -pedantic -Wno-long-long -O0 -ggdb -std=c++11 -lncurses
LFLAGS=-lncurses
SRCS=src/main.cpp src/CXml.cpp src/CParent.cpp src/CSub.cpp src/CSubSC.cpp src/Exception.cpp src/CScreen.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
EXEC=haberluk

all: doc compile
compile: $(OBJS)
	$(CXX)  $(CXXFLAGS) -o $(EXEC) $(OBJS) $(LFLAGS)
main.o: src/main.cpp src/CXml.h 
CParent.o: src/CParent.cpp src/CParent.h src/CScreen.h 
CSub.o: src/CSub.cpp src/CSub.h src/CParent.h 
CSubSC.o: src/CSubSC.cpp src/CSubSC.h \
 src/CParent.h 
CXml.o: src/CXml.cpp src/CXml.h \
 src/CParent.h src/CSub.h \
 src/CSubSC.h src/EXception.h src/CScreen.h
EXception.o: src/Exception.cpp src/Exception.h
CScreen.o: src/CScreen.cpp src/CScreen.h src/Exception.h

clean:
	rm -rf doc haberluk *.o
run:
	./haberluk
doc: $(OBJS)
	cd ./src; \
	doxygen ../doxyConfig
