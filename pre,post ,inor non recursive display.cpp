#include <iostream>
#include <stack>
using namespace std;

// Node structure
struct nodeType {
    int info;
    nodeType* left;
    nodeType* right;
};

// Insert into BST
nodeType* insertBST(nodeType* root, int x) {
    if (root == nullptr) {
        nodeType* temp = new nodeType;
        temp->info = x;
        temp->left = temp->right = nullptr;
        return temp;
    }

    if (x < root->info)
        root->left = insertBST(root->left, x);
    else
        root->right = insertBST(root->right, x);

    return root;
}

// ---------------- NON-RECURSIVE INORDER ----------------
void inorderNonRecursive(nodeType* root) {
    stack<nodeType*> s;
    nodeType* current = root;

    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }

        current = s.top();
        s.pop();
        cout << current->info << " ";

        current = current->right;
    }
}

// ---------------- NON-RECURSIVE PREORDER ----------------
void preorderNonRecursive(nodeType* root) {
    if (root == nullptr)
        return;

    stack<nodeType*> s;
    s.push(root);

    while (!s.empty()) {
        nodeType* current = s.top();
        s.pop();

        cout << current->info << " ";

        if (current->right != nullptr)
            s.push(current->right);

        if (current->left != nullptr)
            s.push(current->left);
    }
}

// ---------------- NON-RECURSIVE POSTORDER ----------------
void postorderNonRecursive(nodeType* root) {
    if (root == nullptr)
        return;

    stack<nodeType*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        nodeType* temp = s1.top();
        s1.pop();
        s2.push(temp);

        if (temp->left != nullptr)
            s1.push(temp->left);

        if (temp->right != nullptr)
            s1.push(temp->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->info << " ";
        s2.pop();
    }
}

// ---------------- MAIN (TEST PROGRAM) ----------------
int main() {
    nodeType* root = nullptr;

    // Create BST
    int values[] = {10, 5, 15, 3, 7, 12, 18};
    for (int x : values)
        root = insertBST(root, x);

    cout << "Non-Recursive Inorder Traversal: ";
    inorderNonRecursive(root);

    cout << "\nNon-Recursive Preorder Traversal: ";
    preorderNonRecursive(root);

    cout << "\nNon-Recursive Postorder Traversal: ";
    postorderNonRecursive(root);

    return 0;
}
