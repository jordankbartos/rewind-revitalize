# File: makefile
# Author: 
# Date: 
# Description: 

CXX = g++ -std=c++11
CXXTAGS = -Wall
CXXTAGS += -g
CXXTAGS += -pedantic-errors

OBJS = main.o
OBJS += Journal.o
OBJS += Entry.o
OBJS += helperFunctions.o

HPPs = Entry.hpp
HPPS += Journal.hpp
HPPS += helperFunctions.hpp

CPPS = main.cpp
CPPS += Entry.cpp
CPPS += Journal.cpp
CPPS += helperFunctions.cpp

rewind-revitalize : $(OBJS)
	$(CXX) $(OBJS) -o rewind-revitalize 

%.o : %.cpp %.hpp
	$(CXX) $(CXXTAGS) -c $< -o $@

clean :
	rm $(OBJS) rewind-revitalize

debug :
	valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes ./rewind-revitalize

zip :
	zip -D rewind-revitalize.zip $(CPPS) $(HPPS) $(TXTS) makefile *.txt *.pdf
