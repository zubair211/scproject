#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cctype>
#include <sstream>
#include <vector>
#include <algorithm> 
void show_help() {
    std::cout << "------------------- HELP function to run my program  -------------------\n";
    std::cout << "Usage of program : program_name would like this  [file_name | URL | help]\n\n";
    std::cout << "Arguments:\n";
    std::cout << "  file_name   : Path to a local text or HTML file to analyze and download the file \n";
    std::cout << "  URL         : URL of a web page and it should be starting with http to analyze  \n";
    std::cout << "  help        : Show this help message to user \n\n";
    std::cout << "This  program generate a word cloud HTML and shows top frequent words.\n";
    std::cout<<"\nThank you\n";
    std::cout << "--------------------------------------------\n";
}

template<typename Key_type, typename V>
struct tnode {
    Key_type key;
    V value;
    tnode* left;
    tnode* right;
    tnode* parent;
    int height;

    tnode(Key_type k, V v) {
        key = k;
        value = v;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        height = 1;
    }
};
template<typename Key_type, typename V>
class Map {
private:
    tnode<Key_type, V>* root;
    int n;

 tnode<Key_type,V>* insertNode( tnode<Key_type,V>* node, Key_type key, V value, tnode<Key_type,V>* parent) {
    if (!node) {
        n++;
        tnode<Key_type,V>* nn = new tnode<Key_type,V>(key, value);
        nn->parent = parent;
        return nn;
    }

    if (key < node->key)
       {
       	 node->left = insertNode(node->left, key, value, node);
		}
    else if (key > node->key)
       {
       	node->right = insertNode(node->right, key, value, node);
		} 
    else {
        node->value = value;
        return node;
    }

    node->height = 1 + std::max(h(node->left), h(node->right));

    int balance_factor = balance(node);
    if (balance_factor > 1 && key < node->left->key)
       {
       	return right_rotation(node);
		} 
    if (balance_factor < -1 && key > node->right->key)
       {
       	return  left_rotation(node);
		} 

    if ( balance_factor> 1 && key > node->left->key) {
        node->left =  left_rotation(node->left);
        return right_rotation(node);
    }


    if (balance_factor < -1 && key < node->right->key) {
        node->right = right_rotation(node->right);
        return  left_rotation(node);
    }

    return node;
}

     int h(tnode<Key_type,V>* node) {
        return node ? node->height : 0;
    }

    int balance(tnode<Key_type,V>* node) {
        return node ? h(node->left) - h(node->right) : 0;
    }

    tnode<Key_type,V>* right_rotation(tnode<Key_type,V>* y) {
        tnode<Key_type,V>* x = y->left;
        tnode<Key_type,V>* z = x->right;

        x->right = y;
        y->left = z;

        if (z){
        z->parent = y;	
		} 
        x->parent = y->parent;
        y->parent = x;

        y->height = std::max(h(y->left), h(y->right)) + 1;
        x->height = std::max(h(x->left), h(x->right)) + 1;

        return x;
    }

    tnode<Key_type,V>* left_rotation(tnode<Key_type,V>* x) {
        tnode<Key_type,V>* y = x->right;
        tnode<Key_type,V>* z = y->left;

        y->left = x;
        x->right = z;

        if (z) {
        	z->parent = x;
		}
        y->parent = x->parent;
        x->parent = y;

        x->height = std::max(h(x->left), h(x->right)) + 1;
        y->height = std::max(h(y->left), h(y->right)) + 1;

        return y;
    }

tnode<Key_type,V>* erase(tnode<Key_type,V>* node, Key_type key) {
    if (!node) {
        return nullptr;
    }

    if (key < node->key) {
        node->left = erase(node->left, key);
    }
    else if (key > node->key) {
        node->right = erase(node->right, key);
    }
    else { 
        if (!node->left) {
            tnode<Key_type,V>* temp = node->right;
            delete node;
            --n;
            return temp;
        }
        else if (!node->right) {
            tnode<Key_type,V>* temp = node->left;
            delete node;
            --n;
            return temp;
        }
        else { 
            tnode<Key_type,V>* succ = node->right;
            while (succ->left != nullptr) {
                succ = succ->left;
            }
            node->key = succ->key;
            node->value = succ->value;
            node->right = erase(node->right, succ->key);
            return node; 
        }
    }
    return node; 
}

    void clearTree(tnode<Key_type, V>* node) {
        if (node == nullptr) {
            return;
        }

        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
      void inorder( tnode<Key_type,V>* node) {
        if (!node) 
		{
		return;	//base
		}
        inorder(node->left);
      std::cout << node->key << " -> " << node->value << std::endl;
        inorder(node->right);
    }
tnode<Key_type, V>* findNode(tnode<Key_type, V>* node, Key_type key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            return findNode(node->left, key);
        }
        else if (key > node->key) {
            return findNode(node->right, key);
        }
        else {
            return node;
        }
    }
public:
    Map() {
        root = nullptr;
        n = 0;
    }

    ~Map() {
        clear();
    }

    V& operator[](const Key_type& key) {
        tnode<Key_type, V>* node = findNode(root, key);

        if (node == nullptr) {
            V temp = V();
            root = insertNode(root, key, temp, nullptr);
            node = findNode(root, key);
        }

        return node->value;
    }

    void clear() {
        clearTree(root);
        root = nullptr;
        n = 0;
    }


    class iterator {
        tnode<Key_type, V>* ptr;
    public:
        iterator(tnode<Key_type, V>* p) {
            ptr = p;
        }

        std::pair<Key_type, V> operator*() const {
            return std::pair<Key_type, V>(ptr->key, ptr->value);
        }

        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }

        iterator& operator++() {
            if (ptr->right != nullptr) {
                ptr = ptr->right;
                while (ptr->left != nullptr) {
                    ptr = ptr->left;
                }
            }
            else {
                tnode<Key_type, V>* p = ptr->parent;
                while (p != nullptr && ptr == p->right) {
                    ptr = p;
                    p = p->parent;
                }
                ptr = p;
            }
            return *this;
        }
    };

    iterator begin() {
        tnode<Key_type, V>* cur = root;

        if (cur == nullptr) {
            return iterator(nullptr);
        }

        while (cur->left != nullptr) {
            cur = cur->left;
        }

        return iterator(cur);
    }

    iterator end() {
        return iterator(nullptr);
    }
    void insert(Key_type key, V value) {
    root = insertNode(root, key, value, nullptr);
}
  
     bool find(Key_type key, V& value) {
        tnode<Key_type,V>* current = root;

        while (current != nullptr) {
            if (key < current->key){
             current = current->left;	
			}
               
            else if (key > current->key)
               {
               	current = current->right;
				} 
            else {
                value = current->value;   
                return true;
            }
        }

        return false; 
    }
      void erase(Key_type key) {
        root = erase(root, key);
    }
int size()const{
    	return n;
	}
	bool empty()const{
		return n==0;
	}
	 void display() {
        inorder(root);//calling existing function;
    }
};

// ---------------- Stop Words ----------------
std::set<std::string> stop_words = {
    "the","is","and","to","of","in","on","for",
    "with","a","if","about","this","that","those","too","at"
};
std::string word_cleaning(const std::string& word) {
    std::string result = "";

    for (int i = 0; i < word.length(); i++) {
        char ch = word[i];
        if (isalpha(ch)) {
            if (ch >= 'A' && ch <= 'Z') {
                ch = ch + 32;
            }
            result = result + ch;
        }
    }

    return result;
}    
std::string remove_html_tags(const std::string& html) {
    std::string text = "";
    int inside = 0;

    for (int i = 0; i < html.length(); i++) {
        if (html[i] == '<') {
            inside = 1;
        }
        else if (html[i] == '>') {
            inside = 0;
        }
        else {
            if (inside == 0) {
                text = text + html[i];
            }
        }
    }

    return text;
}
void download_page(const std::string& url) {
#ifdef _WIN32
    std::string cmd = "curl -L \"" + url + "\" -o temp.html";
#else
    std::string cmd = "wget -q \"" + url + "\" -O temp.html";
#endif
    system(cmd.c_str());
}


int main(int argc, char* argv[]) {

    std::string ural;
    if (argc > 1 && (std::string(argv[2]) == "help" || std::string(argv[2]) == "--help")) {
        show_help();
        return 0; 
    }

    if (argc > 1) {
        ural = argv[1];
    }
    else {
        std::cout << "Enter file name or URAL plz : ";
        std::cin >> ural;
    }
if (ural.empty() || ural == "help") {
        show_help();
        return 0;
    }
    Map<std::string, int> frequency;
    Map<std::string, Map<std::string, int>> variations;

    std::string contents = "";

    if (ural.find("http") == 0) {
        download_page(ural);

        std::ifstream file("temp.html");
        std::string line;

        while (getline(file, line)) {
            contents = contents + line + " ";
        }

        file.close();
        contents = remove_html_tags(contents);
    }
    else {
        std::ifstream file(ural.c_str());

        if (!file) {
            std::cout << "File not found.\n";
            return 0;
        }

        std::string line;
        while (getline(file, line)) {
            contents = contents + line + " ";
        }

        file.close();
    }

    std::stringstream ss(contents);
    std::string word;

    while (ss >> word) {
        std::string washed = word_cleaning(word);
        if (washed == "") {
            continue;
        }
        if (stop_words.count(washed) == 1) {
            continue;
        }
        frequency[washed]++;
        variations[washed][word]++;
    }
    std::vector<std::pair<std::string, int>> freq_vec;

for (Map<std::string, int>::iterator it = frequency.begin(); it != frequency.end(); ++it) {
    std::pair<std::string, int> p = *it;
    freq_vec.push_back(p);
}
std::cout << "\n--- Top 10 frequent words used ---\n";
for (int i = 0; i < 10 && i < freq_vec.size(); ++i) {
    std::cout << freq_vec[i].first << " : " << freq_vec[i].second << std::endl;
}
    std::ofstream html("word_cloud.html");
    html << "<html><body><h1>Word Cloud</h1><div>\n";

    for (Map<std::string, int>::iterator it = frequency.begin();it != frequency.end(); ++it) {
        std::pair<std::string, int> p = *it;
        html << "<span style=\"font-size:";
        html << p.second;
        html << "px\">";
        html << p.first;
        html << "</span> ";
        html << "<small>[";
        Map<std::string, int>& v_map = variations[p.first];

        for (Map<std::string, int>::iterator it2 = v_map.begin();it2 != v_map.end();  ++it2) {

            std::pair<std::string, int> vp = *it2;
            html << vp.first << ":" << vp.second << " ";
        }

        html << "]</small><br>\n";
    }
    html << "</div></body></html>";
    html.close();
    std::cout << "Word cloud generated successfully.\n";
std::cout << "\n--- Testing Map class functions  separately ------\n";
Map<int, std::string> m;
m.insert(10, "Red");
m.insert(5, "Black");
m.insert(20, "Blue");
m[15] = "Green";
m[25] = "Yellow";
std::cout << "Size of map: " << m.size() << std::endl;
std::cout << "Is Map empty? " << (m.empty() ? "Yes" : "No") << std::endl;
std::string val;
if (m.find(20, val)){
	   std::cout << "Value for key 20 : " << val << std::endl;
}
else{
	  std::cout << "Key 20 not found\n";
}
m.erase(10);
std::cout << "After erasing key 10,  checking size: " << m.size() << std::endl;
std::cout << " Runninng Iterating through map:\n";
for (Map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it) {
      std::pair<int, std::string> p = *it;
    std::cout << p.first << " -> " << p.second << std::endl;
}
    return 0;
}

