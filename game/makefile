# makefile

# Add your executable to the tests command so that in compiles along with the rest of the unit testing code
# Please name your executable in the form of test_(function number according to document)

main: Main.cpp
	g++-8.2.0 -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer -o main Board.h Main.cpp -lncurses++ -lmenu -lpanel -lform -lutil -lncurses
tests: tests.cpp
	g++ -std=c++11 -o tests -lcurses tests.cpp

clean_tests:
	rm tests

clean:
	rm main tests
