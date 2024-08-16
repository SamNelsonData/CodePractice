#include <iostream>

template <typename T>
void print(T a) {
	std::cout << a << std::endl;
}

template <typename T> class Node {
	private:
		T element;

    public: 
		Node* next;
		
		// constructor
        Node(T element) {
            this->element = element;
			this->next = NULL;
        };
        
		// getter for the node element
        T getElement() {
            return(this->element);
        };

		void setChild(Node* next) {
			this->next = next;
		};
};

template <typename T>
class LinkedList {
	private:
		Node<T>* head;
		Node<T>* current;
		Node<T>* tail;
		int size;
	public:

		// Constructor
		LinkedList() {
			this->head = NULL;
			this->current = NULL;
			this->tail = NULL;
			this->size = 0;
		}

		void increment() {
			if (this->current->next == NULL) {
				throw std::length_error("Reached end of List");
			}
			this->current = this->current->next;
		};

		T getElement() {
			return this->current->getElement();
		};

		void addElement(T element) {
			Node<T>* new_node = new Node<T>(element);
			if (this->size == 0) {
				this->head = new_node;
				this->current = new_node;
				this->tail = new_node;
				++this->size;
			}
			else {
				this->tail->setChild(new_node);
				this->tail = new_node;
				++this->size;
			}
		};

		T getHead() {
			this->current = this->head;
			return this->head->getElement();
		};

		T pop() {
			Node<T>* temp = this->head;
			this->head = temp->next;
			delete this->head;
			delete temp;
			--this->size;
		};
};

int main() {
	int a = 5;
	int* b = &a;
	print(b);
	print(*b);
	
	print("--------");

	Node<int> temp1 = Node<int>(5);
	Node<int> temp2 = Node<int>(30);
	Node<int> temp3 = Node<int>(42);

	temp1.next = &temp2;
	temp2.setChild(&temp3);

	print(temp1.getElement());
	print(temp1.next->getElement());
	print(temp2.next->getElement());
	print(temp1.next->next->getElement());

	print("--------");

	print("--------");

	LinkedList<int> test_list = LinkedList<int>();
	test_list.addElement(1);
	test_list.addElement(2);
	
	print(test_list.getElement());

	test_list.increment();

	print(test_list.getElement());

}



