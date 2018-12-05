#include "get_game_state.cpp"

#include <iostream>
#include <vector>
#include <curses.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

static void test_stack_size_mutation(int* size){
	
}

static void test_ai_difficulty_mutation(int* difficulty){
	*difficulty = get_numeric_value(
}

int main(){
	int* stack_size = 0;
	int* ai_difficulty = 0;
	pthread_t func[2];

	pthread_create(&func[0], NULL, test_stack_size_mutation, stack_size);
	putchar(51);
	putchar(13);
	pthread_join(&func[0], 0);

	assert(*stack_size==3 && "test_stack_size_mutation()");

	pthread_create(&func[1], NULL, test_ai_difficulty_mutation, ai_difficulty);
	putchar(50);
	putchar(13);
	pthread_join(&func[1], 0);

	assert(*ai_difficulty==2 && "test_ai_difficulty_mutation()");
	

	cout << "Test was successful" << endl;

	return 0;
	
}
