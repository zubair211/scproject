#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* next;
	Node(int val) : data(val), next(nullptr) {}
};

class ForwardList {
private:
	Node* head;

public:
	ForwardList() : head(nullptr) {}
	void push_front(int value) {
		Node* newNode = new Node(value);
		newNode->next = head;
		head = newNode;
	}
	void push_back(int value) {
		Node* newNode = new Node(value);
		if (!head) {
			head = newNode;
			return;
		}
		Node* temp = head;
		while (temp->next)
			temp = temp->next;
		temp->next = newNode;
	}
	void pop_front() {
		if (!head) return;
		Node* temp = head;
		head = head->next;
		delete temp;
	}

	ForwardList& merge(ForwardList& other) {
		Node* t1 = head;
		Node* t2 = other.head;
		Node* temp;
		while (t1 != nullptr && t2 != nullptr) {
			if ( t1->next->data > t2->data) {
				temp = t2->next;
				t2->next = t1->next;
				t1->next = t2;
				t2 = temp;
				t1 = t1->next;
			}
			else {
				t1 = t1->next;
			}
		}
		 if (t2 != nullptr) {
			t1->next = t2;
		}

		other.head = nullptr; 
		return *this}
        
	void display() const {
		Node* temp = head;
		while (temp) {
			cout << temp->data << " -> ";
			temp = temp->next;
		}
	}

	
	
};

int main() {
	ForwardList list, list2;
	list.push_front(3);
	list.push_front(2);
	list.push_front(1);
	list.push_front(1);
	list.display();

	list2.push_front(4);
	list2.push_front(3);
	list2.push_front(2);

	list.merge(list2);
	list.display();
	
}