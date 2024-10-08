// My favorite custom iterator tutorial so far:
// https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp

#include <iostream>
#include <string>

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
			this->next = nullptr;
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
	public:
	
		int size;

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

		T getElement() const {
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

		void reset() {
			this->current = this->head;
		};
		
		Node<T>* getHead() const {
		    return this->head;
		}

		T pop() {
			T element = this->head->getElement();
			Node<T>* temp = this->head;
			this->head = this->head->next;
			delete temp;
			--this->size;
			return element;
		};
    
		friend std::ostream& operator<<(std::ostream& os, LinkedList const & LL) {
		    if(LL.size == 0) {
		        return os << "[]";
		    }
		    std::string str_rep = "[";
		    Node<T>* TN = LL.getHead(); //traversal node
		    str_rep = str_rep + std::to_string(TN->getElement()) + ", ";
		    
		    while(TN->next != NULL) {
		        TN = TN->next;
		        str_rep = str_rep + std::to_string(TN->getElement()) + ", ";
		    }
		    str_rep.erase(str_rep.end() - 2, str_rep.end());
		    return os << str_rep + "]";
		}

        struct Iterator {
            
            // Constructor
            Iterator(Node<T>* node_ptr) : current(node_ptr) {}
            
            // De-reference operator overrides
            T operator*() { return this->current->getElement();};
            Node<T>* operator->() { return this->current;};
            
            // Pre-fix operator overload
            Iterator& operator++() {
                this->current = this->current->next;
                return *this;
            };
            
            // Post-fix operator overload
			Iterator operator++(int) {
				Iterator temp = *this;
				++(*this);
				return temp;
			};
			
			bool operator==(Iterator& a) {
			    return this->current == a.current;
			}
			
			bool operator!=(Iterator& a) {
			    return this->current != a.current;
			}
            
            private:
                Node<T>* current;
        };

        Iterator begin() {
            return Iterator(this->head);
        }
        
        Iterator end() {
            return Iterator(this->tail->next);
        }

};

int main() {
	int a = 5;
	int* b = &a;
	print(b);
	print(*b);

	print("--------");

	LinkedList<int> test_list = LinkedList<int>();
	test_list.addElement(1);
	test_list.addElement(2);
	test_list.addElement(3);
	test_list.addElement(4);

	test_list.addElement(42);
	test_list.addElement(111);
	test_list.addElement(666);
	
	for (auto i : test_list) {
	    std::cout << i << std::endl;
	}
}
