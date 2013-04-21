GTmodify: GTMmain.o utility.o algorithms.o defs.h
	  g++  -std=c++11 GTMmain.o utility.o algorithms.o defs.h -o GTModify

GTMmain.o: GTMmain.cc defs.h
	  g++ -std=c++11 -c GTMmain.cc

utility.o: utility.cc defs.h
	   g++ -std=c++11 -c utility.cc

algorithms.o: algorithms.cc defs.h
	      g++ -std=c++11 -c algorithms.cc

clean:
	rm *.o 
	rm GTModify

