#include <iostream>
#include<cstring>
#include<fstream>
#include<set>
template<typename Key_type, typename V>
struct tnode {
    Key_type key;
    V value;
     tnode* left;
     tnode* right;

     tnode(Key_type k, V v) {
        key = k;
        value = v;
        left = nullptr;
		right = nullptr;
    }
};
template<typename Key_type, typename V>
class Map {
private:
	int n=0;
     tnode<Key_type,V>* root_node;
     tnode<Key_type,V>* insert( tnode<Key_type,V>*node, Key_type key, V value) {
        if (node == nullptr)
          {
          	++n;
          	 return new tnode<Key_type,V>(key, value);
			}  

        if (key < node->key){
        	 node->left = insert(node->left, key, value);//using recursion to insert values;
        	 
		}
           

        else if (key > node->key){
        	 node->right = insert(node->right, key, value);
        	 
		}
           

        else
            {
            		node->value = value;  //if only when Key exists then  update value;
         	}
        return node;
    }
     tnode<Key_type,V>* find_node( tnode<Key_type,V>* node, Key_type key) {
        if (!node){//not exist in program ;
        	 return nullptr;
		}
        if (key < node->key) 
		{
		return find_node(node->left, key);	
		}
        else if (key > node->key)
		{
		return find_node(node->right, key);	
		 } 
        else return node;
}
  tnode<Key_type,V>* minnode(tnode<Key_type,V>* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }
     tnode<Key_type,V>* erases( tnode<Key_type,V>* node, Key_type key) {
        if (!node){
        	--n;
        return node;//base condition	
		} 

        if (key < node->key){
        	node->left = erases(node->left, key);
        	
		}
            

        else if (key > node->key){
        
            node->right = erases(node->right, key);	
            
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
tnode<Key_type,V>* temp = minnode(node->right);
            node->key = temp->key;
            node->value = temp->value;

            node->right = erases(node->right, temp->key);
        }
        return node;
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
void clear_Tree(tnode<Key_type, V>* node) {
    if (!node) return;
    clear_Tree(node->left);
    clear_Tree(node->right);
    delete node;
}
public:
    Map() {//constructor
	 root_node = nullptr;
	  }
	  ~Map(){
	  	clear();
	  }
    void insert(Key_type key, V value) {
        root_node= insert(root_node, key, value);
    }

  bool find(Key_type key, V& value) {
        tnode<Key_type,V>* current = root_node;

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
  class iterator{
  	private:
  		tnode<Key_type,V>*ptr;
  		tnode<Key_type, V>* root; 
      	
  		public:
  			iterator(tnode<Key_type, V>* p, tnode<Key_type, V>* r) {
    ptr = p;
    root = r;
}

			  std::pair<int,std::string>operator*()const{
			   return std::make_pair(ptr->key, ptr->value);
			  }
			  bool operator ==(const iterator& other)const{
			  	return ptr==other.ptr;
			  }
			  bool operator !=(const iterator& other)const{
			  	return ptr!=other.ptr; 
			  }
			  
iterator& operator++() {
    if (ptr == nullptr) {
    return *this;	
	}

   
    if (ptr->right != nullptr) {
        ptr = ptr->right;
        while (ptr->left != nullptr){
           ptr = ptr->left;	
		}
         
        return *this;
    }
    tnode<Key_type,V>* succ = nullptr;
    tnode<Key_type,V>* curr = root;

    while (curr != nullptr) {
        if (ptr->key < curr->key) {
            succ = curr;
            curr = curr->left;
        }
        else if (ptr->key > curr->key) {
            curr = curr->right;
        }
        else break;
    }

    ptr = succ;
    return *this;
}


iterator& operator--() {
    if (ptr->left != nullptr) {
        ptr = ptr->left;
        while (ptr->right != nullptr)
            ptr = ptr->right;
    } else {
         tnode<Key_type, V>* parent = ptr->parent;
        while (parent != nullptr && ptr == parent->left) {
            ptr = parent;
            parent = parent->parent;
        }
        ptr = parent;      
    }
    return *this;
}
			  
  };
iterator begin() {
    tnode<Key_type, V>* current = root_node;

    
    if (current == nullptr)
        return iterator(nullptr, root_node);
    while (current->left != nullptr) {
        current = current->left;
    }

    return iterator(current, root_node);
}


iterator end() {
    return iterator(nullptr, root_node);
}

    void erase(Key_type key) {
        root_node = erases(root_node, key);
    }
    int count(Key_type key) {
    V temp;         // dummy variable to satisfy or to call exist find function bcz it work same as count;
    return find(key, temp) ? 1 : 0;
}
void clear() {
    clear_Tree(root_node);
    root_node = nullptr;
    n = 0;       // reset size to 0
}
    void display() {
        inorder(root_node);//calling existing function;
    }
    int size()const{
    	return n;
	}
	bool empty()const{
		return n==0;
	}
	V& operator[](const Key_type& key) {
    tnode<Key_type,V>* node = find_node(root_node, key);
    if (node) {
        return node->value;  // key exists
    } else {
        V defaultValue{};    // default-constructed value
        root_node = insert(root_node, key, defaultValue);
        node = find_node(root_node, key);  // find newly inserted node
        return node->value;
    }
}

};
std::set<std::string> stopWords = {"the","is","and","to","of","in","on","for","with","a"};
std::string clean(std::string word)
{
   std:: string result = "";

    for(int i = 0; i < word.length(); i++)
    {
        char c = word[i];
        if(c >= 'A' && c <= 'Z'){
        	  c = c + 32;
		}
          
        if(c >= 'a' && c <= 'z'){
        	result += c;
		}
            
    }

    return result;
}
 	int main(int argc, char* argv[])
{
   std:: string file_name;
    if(argc > 1){
    	 file_name = argv[1];
	}     
    else {
       std:: cout << "\nEnter file name plz : ";
       std:: cin >> file_name;
    }
    std::ifstream file(file_name);
    if(!file)
    {
        std::cout << "\nFile not found check your access \n";
        return 0;
    }
    else{
    	std::cout<<"\n File created proceed \n";
	}
	Map< std::string,int> freq;   // word → count
   std:: string word;

    // ✅ READ FILE
    while(file >> word)
    {
        word = clean(word);   // manual clean

        if(word == "") 
		{
			  continue;
			  }      
          

        // ✅ IGNORE STOP WORDS
        if(stopWords.count(word) == 1)
          {
          	 continue;
			} 

        // ✅ COUNT
        freq[word]++;
    }

    file.close();

    // ✅ DISPLAY RESULT
   std:: cout << "\nWORD FREQUENCY:\n\n";
//for(Map<std::string,int>::iterator it = freq.begin(); it != freq.end(); ++it) {
 //   std::pair<std::string,int> p = *it;
  //  std::cout << p.first << " -> " << p.second << std::endl;
//}

  //  for(auto x : freq)
     //   std::cout << x.first << " -> " << x.second << std::endl;

    Map<int,std::string> m;

    m.insert(10, "red");
    m.insert(5, "Black");
    m.insert(20, "blue");
      m.insert(10, "purpel");//this will not add bcz map take unique key;
 //   m[40]="purpel";
     m.insert(50, "Black barrey");
   std::cout<<"\nThe size = "<<  m.size()<<std::endl;
   std:: cout << "Map contains pair of contents are below:\n";
    m.display();

    std::string val;
    if (m.find(5, val))
      {
      	std:: cout << "\nusing find function displaying Value for key 5 -> " << val << std::endl;

	   } 
	   else {
	   	std::cout<<"\n not exist : ";
	   }
    m.erase(10);
std::cout<<"\nthe size = "<<  m.size()<<std::endl;
   std:: cout << "\nAfter deleting key 10 :\n";
   std::cout<<"\n Map contains\n ";
    m.display();
  if (  m.count(10))
      {
      	std:: cout << "\n value exist" << std::endl;

	   } 
	   else {
	   	std::cout<<"\n not exist : ";
	   }
	Map<int,std::string> ::iterator it = m.begin();

while (it != m.end()) {
    std::pair<int, std::string> present = *it;
   std:: cout << present.first << " = " << present.second <<std:: endl;
    ++it;
}
std::cout<<"\n Empty function = "<<m.empty()<<std::endl;
    return 0;
}
