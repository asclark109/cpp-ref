#include "ex_5_stack_austin.h";
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

size_t const reps{ 100};
size_t const threadCount{ 10 };

void addRandomInts(Stack<int>& stack, size_t qty) {
	for (size_t s = 0; s < qty; s++)
		stack.push(std::rand());
}

void popInts(Stack<int>& stack, size_t qty) {
	for (size_t s = 0; s < qty; s++)
		stack.pop();
}

void demonstrateMultiThreadUsage() {
	CourseStack<int> coarseGrainedStack{};
	Stack<int>& stack = coarseGrainedStack; // program to interfaces...can switch implementation above

	std::vector<std::thread> addingthreads;
	std::vector<std::thread> removingthreads;
	
	// spawn threads that'll add numbers
	for (size_t s = 0; s < threadCount; s++)
		addingthreads.push_back(std::thread(addRandomInts,std::ref(stack),reps));

	// wait for all to finish
	for (auto& thr : addingthreads)
		thr.join();

	std::cout << "stack (after adding elems); " << stack.size() << " elements in stack" << std::endl;

	// spawn threads that'll remove numbers
	for (size_t s = 0; s < threadCount; s++)
		removingthreads.push_back(std::thread(popInts, std::ref(stack), reps));

	// wait for all to finish
	for (auto& thr : removingthreads)
		thr.join();

	std::cout << "stack (after removing elems); " << stack.size() << " elements in stack" << std::endl;

}

void demonstrateSingleThreadUsage() {
	CourseStack<int> stack;
	std::cout << "pushing" << std::endl;
	std::cout << stack << std::endl;
	stack.push(4);
	std::cout << stack << std::endl;
	stack.push(4);
	std::cout << stack << std::endl;
	stack.push(40);
	std::cout << stack << std::endl;
	stack.push(40);
	std::cout << stack << std::endl;
	std::cout << "popping" << std::endl;
	stack.pop();
	std::cout << stack << std::endl;
	stack.pop();
	std::cout << stack << std::endl;
	stack.pop();
	std::cout << stack << std::endl;
	stack.pop();
	std::cout << stack << std::endl;
	stack.pop();
	std::cout << stack << std::endl;
}

int main() {

	// demonstrateSingleThreadUsage();
	demonstrateMultiThreadUsage();
	
	return 0;
}