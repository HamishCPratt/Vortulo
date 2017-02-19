all: project

SOURCE=$(wildcard *.cpp)
OBJECT=$(SOURCE:.cpp=.o)

project: $(OBJECT)
	g++ -std=c++11 $(OBJECT) -o project 
	
%.o: %.cpp
		g++ -std=c++11 -c $^

clean:
	rm -f $(OBJECT) project
	
