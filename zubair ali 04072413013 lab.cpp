#include <iostream>
using namespace std;

template <typename key_type>
class tnode {
public:
    key_type key;
    tnode<key_type>* left;
    tnode<key_type>* right;
    tnode<key_type>* parent;
    bool is_nill;

    tnode() {
        key = key_type();
        left = right = parent = nullptr;
        is_nill = false;
    }
};

template <typename key_type>
class set {
private:
    tnode<key_type>* h; // sentinel node to handle to end of tree 
    int n;

public:
    set() {
        h = new tnode<key_type>;
        h->left = h->right = h->parent = h;
        h->is_nill = true;
        n = 0;
    }

    void insert(const key_type& key) {
        tnode<key_type>* temp;
        tnode<key_type>* nn = new tnode<key_type>;
        nn->left = nn->right = h;
        nn->key = key;
        nn->is_nill = false;

        if (h->parent == h) { //only if  empty tree
            nn->parent = h;
            h->parent = nn;
            h->left = nn;
            h->right = nn;
            n++;
            return;
        }

        temp = h->parent;
        while (temp != h) {
            if (key < temp->key) {
                if (temp->left == h) {
                    temp->left = nn;
                    nn->parent = temp;
                    n++;
                    break;
                }
                else {
                    temp = temp->left;
                }
            }
            else if (key > temp->key) {
                if (temp->right == h) {
                    temp->right = nn;
                    nn->parent = temp;
                    n++;
                    break;
                }
                else {
                    temp = temp->right;
                }
            }
            else {
                cout << "\nDuplicate value!";
                delete nn;
                return;
            }
        }

        if (key < h->left->key) h->left = nn;
        if (key > h->right->key) h->right = nn;
    }

    int size() const { return n; }

    bool empty() const { return n == 0; }

    tnode<key_type>* findNode(const key_type& key) const {
        tnode<key_type>* temp = h->parent;
        while (temp != h && temp != nullptr) {
            if (key < temp->key)
                temp = temp->left;
            else if (key > temp->key)
                temp = temp->right;
            else
                return temp;
        }
        return nullptr;
    }

    bool contains(const key_type& key) const {
        return findNode(key) != nullptr;
    }

 
    class iterator {
    private:
        tnode<key_type>* temp;
        tnode<key_type>* sentinel;

    public:
        friend class set;

        iterator(tnode<key_type>* node = nullptr, tnode<key_type>* h = nullptr)
            : temp(node), sentinel(h) {
        }

        key_type& operator*() const {
            return temp->key;
        }

        bool operator==(const iterator& other) const {
            return temp == other.temp;
        }

        bool operator!=(const iterator& other) const {
            return temp != other.temp;
        }

        iterator& operator++() {
            if (!temp) {
                return *this; // already end();
            }
            if (temp->right != sentinel && !temp->right->is_nill) {
                temp = temp->right;
                while (temp->left != sentinel && !temp->left->is_nill)
                {
                    temp = temp->left;
                }
            }
            else {
                tnode<key_type>* parent = temp->parent;
                while (parent != sentinel && temp == parent->right) {
                    temp = parent;
                    parent = parent->parent;
                }
                if (parent == sentinel) {
                    temp = nullptr; // reached end sentinel used to handle this part
                }

                else {
                    temp = parent;
                }
            }
            return *this;
        }
    };

    iterator begin() {
        if (h->parent == h) {
            return iterator(nullptr, h);
        }
        tnode<key_type>* curr = h->parent;
        while (curr->left != h) {
            curr = curr->left;
        }
        return iterator(curr, h);
    }

    iterator end() {
        return iterator(nullptr, h);
    }
};

int main() {
    set<int> s;
    s.insert(10);
    s.insert(5);
    s.insert(12);
    s.insert(3);
    s.insert(7);
    s.insert(8);
    s.insert(2);
    s.insert(5); // duplicate test in program

    cout << "\nThe size of program is = " << s.size();
    cout << "\nEmpty = " << s.empty();
    cout << "\nContains 10: " << s.contains(10) << endl;

    cout << "\nElements of tree: ";
    for (set<int>::iterator it = s.begin(); it != s.end(); ++it) 
    {
        cout << *it << "-> ";
    }

    cout << endl;
    return 0;
}
