#include <iostream>
#include<cstring>
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
     tnode<Key_type,V>* root_node;
     tnode<Key_type,V>* insert( tnode<Key_type,V>*node, Key_type key, V value) {
        if (node == nullptr)
          {
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
            		node->value = value;  //if only  Key exists then  update value;
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
                return temp;
            }
            else if (!node->right) {
                 tnode<Key_type,V>* temp = node->left;
                delete node;
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

public:
    Map() {
	 root_node = nullptr;
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

    void erase(Key_type key) {
        root_node = erases(root_node, key);
    }

    void display() {
        inorder(root_node);//calling existing function;
    }
};


int main() {
    Map<int,std::string> m;

    m.insert(10, "red");
    m.insert(5, "Black");
    m.insert(20, "blue");
      m.insert(10, "purpel");//this will not add bcz map take unique key;
 //   m[40]="purpel";
     m.insert(50, "Black barrey");
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

   std:: cout << "\nAfter deleting key 10 :\n";
   std::cout<<"\n Map contains\n ";
    m.display();

    return 0;
}