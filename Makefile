remake: usefulfunc.o state.o Action.o ActionList.o  qvalweb.o qvaltree.o edt.o userdefined.o Agent.o
	rm -f rpsort rpsort.o 
	g++ -g -c rpsort.cpp
	g++ -g -o rpsort rpsort.o usefulfunc.o state.o Action.o ActionList.o qvalweb.o qvaltree.o edt.o userdefined.o Agent.o

rpsort.o: rpsort.cpp rpsort.h
	g++ -c rpsort.cpp

usefulfunc.o: usefulfunc.h usefulfunc.cpp
	g++ -g -c usefulfunc.cpp
	
state.o: state.h state.cpp
	g++ -g -c state.cpp
	
Action.o: Action.h Action.cpp
	g++ -g -c Action.cpp
	
ActionList.o: ActionList.h ActionList.cpp
	g++ -g -c ActionList.cpp
	
qvalweb.o: qvalweb.h qvalweb.cpp
	g++ -g -c qvalweb.cpp
	
qvaltree.o: qvaltree.h qvaltree.cpp
	g++ -g -c qvaltree.cpp
	
edt.o: edt.h edt.cpp
	g++ -g -c edt.cpp

userdefined.o: userdefined.cpp
	g++ -g -c userdefined.cpp
	
sorts.o: sorts.h sorts.cpp
	g++ -g -c sorts.cpp
	
Agent.o: Agent.h Agent.cpp
	g++ -g -c Agent.cpp

clean:
	rm -f *.o *~ rpsort

backup:
	zip backuprpgensort.zip *.cpp *.h Makefile
	cp backuprpgensort.zip ../

restore:
	unzip -o backuprpgensort.zip
