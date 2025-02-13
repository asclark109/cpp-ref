////////////
// AUSTIN
////////////
#ifndef STACK_H
#  define STACK_H

// LIFO (last-in-first-out) Stack

#include<mutex>
#include<shared_mutex>
#include <memory>
#include <sstream>

// INTERFACE; pure virtual functions only
template <class T>
class Stack 
{
public:
	virtual void push(T toInsert) = 0;
	virtual std::unique_ptr<T> pop() = 0;
	virtual std::unique_ptr<T> top() = 0;
	virtual bool isEmpty() = 0;
	virtual int size() = 0;
};

// HELPER CLASS
template <class T>
class Node {

	inline friend std::ostream& operator<<(std::ostream& os, const Node& node) {
		os << "Node[";
		os << node.payload;
		os << ",->";
		if (node.next == nullptr) {
			os << "nil";
		}
		else {
			os << node.next;
		}
		os << "]";
		return os;
	}

public:
	Node(T payload) { // accept T object by value
		this->payload = payload;
		this->next = std::unique_ptr<Node>(nullptr);
	};

	Node(T payload, std::unique_ptr<Node> next) { // also accept next node
		this->payload = payload;
		this->next = std::move(next);
	};

	T payload;
	std::unique_ptr<Node> next;
};

// COARSE-GRAINED STACK IMPLEMENTATION
template <class T>
class CourseStack : public Stack<T> {

	inline friend std::ostream& operator<<(std::ostream& os, const CourseStack& stack) {
		os << "Stack[";
		// walk through Node LL; need to use pointers		

		// continuously:
		// (1) print node
		// (2) advance to next node if exists
		if (stack.head != nullptr) {
			Node<T>* currNodePtr = stack.head.get(); // start at head
			while (true) {
				os << *currNodePtr; 
				if (currNodePtr->next != nullptr){  
					os << ", ";
					currNodePtr = currNodePtr->next.get();
				}
				else {
					break;
				}
			}
		}
		os << "]";
		return os;
	}

private:
	std::unique_ptr<Node<T>> head;
	std::shared_mutex mutable mtx;
	int count{0};

public:
	CourseStack() {
		head = nullptr;
	}
	CourseStack(std::unique_ptr<Node<T>> node) {
		head = std::move(node);
	}

	virtual void push(T toInsert) {
		std::unique_lock guard(mtx); // Unique writer access for pushing
		if (head == nullptr) { // case, stack is empty. 
			head = std::make_unique<Node<T>>(toInsert);
		}
		else { 
			std::unique_ptr<Node<T>> newHead = std::make_unique<Node<T>>(toInsert,std::move(head));
			head = std::move(newHead);
		}	
	};

	virtual std::unique_ptr<T> pop() {
		std::unique_lock guard(mtx); // Unique writer access for popping
		// (1) case: nothing in stack.
		// (2) case: 1 element in stack. head is now nullptr.
		// (3) case: >1 element in stack. head is updated.
		if (head == nullptr) {
			return std::make_unique<T>();
		}
		auto result = std::make_unique<T>(head->payload);
		if (head->next == nullptr) {
			head = nullptr; // this should auto delete the original heap object?
		} else {
			head = std::move(head->next);
		}
		return result;
	};
	
	virtual std::unique_ptr<T> top() {
		std::shared_lock guard(mtx);
		if (isEmpty())
			return std::make_unique<T>();
		return std::make_unique<T>(head->payload); // return pointer to copied value
	};

	virtual bool isEmpty() {
		return (head == nullptr);
	};

	virtual int size() {
		// walk through Node LL; use pointers		
		// continuously:
		// (1) increment counter
		// (2) advance to next node if exists
		int count{};
		if (head != nullptr) {
			Node<T>* currNodePtr = head.get(); // start at head
			while (true) {
				count++;
				if (currNodePtr->next != nullptr) {
					currNodePtr = currNodePtr->next.get();
				}
				else {
					break;
				}
			}
		}
		return count;
	}
};


#endif