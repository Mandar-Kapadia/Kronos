CC = g++
CFLAGS = -Wall -Werror -pedantic --std=c++17
LIBS = -lboost_unit_test_framework -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lboost_regex -lboost_date_time
DEPS = main.cpp
all:ps7 style  
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -I/opt/homebrew/Cellar/boost/1.78.0_1/include -I/opt/homebrew/Cellar/sfml/2.5.1_1/include -c $<
ps7: main.o
	$(CC) $(CFLAGS) -L/opt/homebrew/Cellar/boost/1.78.0_1/lib -L/opt/homebrew/Cellar/sfml/2.5.1_1/lib -o $@ $^ $(LIBS)
clean:
	rm -f *.o 
	rm -f ps7
style:
	cpplint --filter=-runtime/references,-build/header_guard --extensions=cpp,hpp,h main.cpp