#include <iostream>
#include <cstring>
using namespace std;

template<typename T>
struct Comparator {
	virtual bool operator() (T const&, T const&) const = 0;
};

struct IntComparator final : Comparator<int> {
	bool operator() (int const& lha, int const& rha) const override {
		return lha < rha;
	}
};

template<typename T>
struct Node {
	T field;
	Node* parent;
	Node* right;
	Node* left;
};

template<typename T>
void print_tree(Node<T>* curr) {
	if (curr == nullptr) return;
	std::cout << curr->field;
	if (curr->left != nullptr) {
		std::cout << ": left(";
		print_tree(curr->left);
		std::cout << ")";
	}
	if (curr->right != nullptr) {
		std::cout << ", right(";
		print_tree(curr->right);
		std::cout << ")";
	}
}

template<typename T>
class PriorityQueue {
private:
	Node<T>* top;
	int size;
	Comparator<T>& comp;

	int get_depth() {
		// returns the height (depth) of the tree
		int power = 1;
		int depth = 0;
		while (power <= size) {
			power *= 2;
			depth++;
		}
		return depth;
	}

	bool* get_directions() {
		int depth = get_depth();

		// figuring out the path to the bottom leftmost empty space
		bool* directions = new bool[depth - 1]; // false means go left, true means go right
		int curr = size;
		int ind = depth - 2;
		while (curr > 1) {
			if (curr % 2 == 0) {
				directions[ind] = false;
			}
			else {
				directions[ind] = true;
			}
			curr /= 2;
			ind--;
		}
		return directions;
	}

	Node<T>* follow(bool* directions, int size_directions) {
		// follows the directions from the top and returns the last node
		Node<T>* current = top;
		for (int i = 0; i < size_directions; i++) {
			if (directions[i]) current = current->right;
			else current = current->left;
		}
		return current;
	}

	void swap(Node<T>* lha, Node<T>* rha) {
		// swaps values of lha and rha
		T temp = lha->field;
		lha->field = rha->field;
		rha->field = temp;
	}

public:
	PriorityQueue(Comparator<T>& comp): top(nullptr), comp(comp), size(0) {}
	PriorityQueue() = delete; // since i have to get a comparator

	void push(T value) {
		// checking if the queue is empty
		if (is_empty()) {
			// creating the new node (constructors are for the weak)
			Node<T>* new_node = new Node<T>;
			new_node->field = value;
			new_node->right = nullptr;
			new_node->left = nullptr;
			new_node->parent = nullptr;

			top = new_node;
			size = 1;
			return;
		}

		// main case
		// increasing the size
		size++;
	
		bool* directions = get_directions();
		int depth = get_depth();

		// following the directions
		Node<T>* current = follow(directions, depth - 2);

		// creating the new node (constructors are for the weak)
		Node<T>* new_node = new Node<T>;
		new_node->field = value;
		new_node->right = nullptr;
		new_node->left = nullptr;
		new_node->parent = current;
		
		// finally adding the new node
		if (directions[depth - 2]) current->right = new_node;
		else current->left = new_node;

		// fixing the heap
		current = new_node;
		while (current->parent != nullptr) {
			if (comp(current->parent->field, current->field)) swap(current, current->parent);
			current = current->parent;
		}

		// forgetting everything
		delete[] directions;
	}

	T peek() {
		return top->field;
	}

	void poll() {
		if (size == 0) return;

		if (size == 1) {
			delete top;
			top = nullptr;
			size = 0;
			return;
		}

		// main case
		// getting last and pre last nodes
		int depth = get_depth();
		bool* directions = get_directions();
		Node<T>* pre_last = follow(directions, depth - 2);
		Node<T>* last = follow(directions, depth - 1);

		// the most important part
		size--;
		
		// replacing the top value with the last one
		top->field = last->field;

		// deleting the last node
		delete last;
		if (directions[depth - 2]) pre_last->right = nullptr;
		else pre_last->left = nullptr;

		// forgetting directions
		delete[] directions;

		// fixing the heap
		bool fixed = false;
		Node<T>* current = top;
		while (!fixed) {
			// if there are no children, stop
			if (current->left == nullptr) break;
			
			// if there's only one children, compare with it
			if (current->right == nullptr) {
				if (comp(current->field, current->left->field)) swap(current->left, current);
				fixed = true;
				return;
			}
			
			// checking if the heap is ordered
			if (comp(current->left->field, current->field) && comp(current->right->field, current->field)) fixed = true;
			// swapping with the bigger child if it isn't
			else {
				if (comp(current->left->field, current->right->field)) {
					swap(current->right, current);
					current = current->right;
				}
				else {
					swap(current->left, current);
					current = current->left;
				}
			}			
		}
	}

	bool is_empty() {
		return top == nullptr;
	}

	void free() {
		// deletes the queue as n log n
		while (size > 0) poll();
	}

	void print() {
		print_tree<T>(top);
	}
};

int main() {
	IntComparator comp;
	PriorityQueue<int> pq(comp);
	pq.push(4);
	pq.push(2);
	pq.push(10);
	pq.push(5);
	pq.push(0);
	pq.print();
	std::cout << std::endl;
	
	std::cout << "peek: " << pq.peek() << std::endl;

	pq.poll();
	pq.print();

	std::cout << std::endl << "is empty: " << pq.is_empty() << std::endl;

	pq.free();
	std::cout << "is empty: " << pq.is_empty() << std::endl;
}



