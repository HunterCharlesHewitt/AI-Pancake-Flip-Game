#define CATCH_CONFIG_MAIN // Tells Catch to provide a main() when function code is compiled by itself
#include "catch.hpp"
#include "set_init_state.cpp"

using namespace std;

TEST_CASE("Initial state is obtained", "[set_init_state]"){
	int n = 9;

    SECTION("Choosing a random starting state"){
		
        int fd[2];
        pipe(fd);
        vector<int> stack;
        if (fork() != 0) { //parent
            dup2(fd[0], 0);
            close(fd[0]);
            close(fd[1]);
            stack = get_init_state(n);
        } else {
            sleep(1);
            dup2(fd[1], 1);
            close(fd[0]);
            cout << "r" << endl;
            close(fd[1]);
            exit(0);
        }

        dup2(0,0);
        dup2(1,1);

		REQUIRE(stack.size() == 9);
	}

	SECTION("Choosing a starting state of [1, 2, 3, 4, 5, 6, 7, 8, 9]"){
        int fd[2];
        pipe(fd);
        vector<int> stack;
        if (fork() != 0) { //parent
            dup2(fd[0], 0);
            close(fd[0]);
            close(fd[1]);
            stack = get_init_state(n);
        } else {
            sleep(1);
            dup2(fd[1], 1);
            close(fd[0]);
            cout << "1,2,3,4,5,6,7,8,9" << endl;
            close(fd[1]);
            exit(0);
        }

        dup2(0,0);
        dup2(1,1);

		REQUIRE(stack.size() == 9);
        for (int i = 0; i < 9; i++)
            REQUIRE(stack.at(i) == i+1);
        
	}

    // SECTION("Making sure AI and Player stacks are thr same") {

    // }

}