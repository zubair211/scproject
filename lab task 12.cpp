#include <iostream>
#include <list>

template<typename k, typename T>
class unordered_map {
private:
    std::list<std::pair<k, T> >* table;
    int m, n;

    int hash(const k& key) const {
        return key % m;
    }

    typename std::list<std::pair<k, T> >::iterator
    find(std::list<std::pair<k, T> >& l, const k& key) {
        typename std::list<std::pair<k, T> >::iterator it = l.begin();
        while (it != l.end()) {
            if (it->first == key)
                return it;
            ++it;
        }
        return it;
    }

public:

    unordered_map(int s = 11) {
        m = s;
        n = 0;
        table = new std::list<std::pair<k, T> >[m];
    }

   void insert(const std::pair<k, T>& p) {
        int h = hash(p.first);
        typename std::list<std::pair<k, T> >::iterator it_list = find(table[h], p.first);
        if (it_list == table[h].end()) {
            table[h].push_back(p);
            ++n;
        }
        else{
        	it_list->second=p.second;
		}
    }


    class iterator {
    private:
        int index;
        typename std::list<std::pair<k, T> >::iterator it_list;
        unordered_map<k, T>* um;

    public:
        friend class unordered_map<k, T>;

        iterator(){
        
        	index=0;
		}

        iterator& operator++() {
            ++it_list;
            while (index < um->m && it_list == um->table[index].end()) {
                ++index;
                if (index < um->m)
                    it_list = um->table[index].begin();
            }
            return *this;
        }

        std::pair<k, T>& operator*() {
		 return *it_list;
		  }
        std::pair<k, T>* operator->() {
		 return &(*it_list); 
		 }

        bool operator!=(const iterator& other) const {
            return index != other.index;
        }
  bool operator==(const iterator& other)const {
			return index == other.index;
		}

    };
    iterator begin() {
        iterator it;
        it.um = this;
        it.index = 0;

        while (it.index < m && table[it.index].empty())
           {
           	++it.index;
			} 

        if (it.index == m)
           {
           	 return end();
			}

        it.it_list = table[it.index].begin();
        return it;
    }

    iterator end() {
        iterator it;
        it.um = this;
        it.index = m; 
        return it;
    }
          void clear() {
    for (int i = 0; i < m; ++i)
      {
      	table[i].clear(); 
		}  
    n = 0;
}
void erase(const k& key) {
    int h = hash(key); 
    typename std::list<std::pair<k, T> >::iterator it = find(table[h], key);

    if (it != table[h].end()) {
        table[h].erase(it); 
        --n;               
    }
}
bool empty ()const{
	return n==0;
}
int size ()const{
	return n;
}
bool operator==( unordered_map<k,T>&other)const{
	if(n!=other.n){
		return false;
	}
	int h;
	typename std::list<std::pair<k, T> >::iterator it;
	 typename std::list<std::pair<k, T> >::iterator	it2;
	for(int i=0;i<m;i++){
	
		for(  it=table[i].begin();it!=table[i].end();it++ ){
			 h=other.hash(it->first);
		}
	 	it2=other.find(other.table[h],it->first);
		if(it2==other.table[h].end()){
			return false;
		}
		if(it2->second!=it->second){
			return false;
		}
	}
	return true;
}
};


int main() {
    unordered_map<int,std:: string> sq(11);
  unordered_map<int, int> sqr(11);
    for (int i = 1; i < 10; i++)
       {
       	 sqr.insert(std::pair<int,int>(i, i * 1));
		}
		unordered_map<int, int> sqr2(11);
    for (int i = 1; i < 10; i++)
       {
       	 sqr2.insert(std::pair<int,int>(i, i * 5));
		}
		sq.insert(std::pair<int,std::string>(2,"Aslam"));
		sq.insert(std::pair<int,std::string>(3,"zubair"));
		sq.insert(std::pair<int,std::string>(4,"Junaid"));
		sq.insert(std::pair<int,std::string>(6,"Taha"));
		sq.insert(std::pair<int,std::string>(5,"talha"));
		sq.insert(std::pair<int,std::string>(7,"javed"));
		sq.insert(std::pair<int,std::string>(7,"husnain"));//it will just update the p.second bcz key same;
  std::cout<<" \nThe size of unordered map is = "<<sq.size()<<std::endl;
    unordered_map<int, std::string>::iterator it = sq.begin();
    unordered_map<int, std::string>::iterator it2 = sq.end();
std::cout<<"\nMap contains \n";
    while (it != it2) {
        std::cout << it->first << " -> " << it->second << std::endl;
        ++it;
    }
    sq.erase(7);
   std::cout<<"\nAfter erase 3 unordered map conatians :\n";
   unordered_map<int, std::string>::iterator it3 = sq.begin();
    unordered_map<int, std::string>::iterator it4 = sq.end();

     while (it3 != it4) {
        std::cout << it3->first << " -> " << it3->second << std::endl;
        ++it3;
    }
  if(sqr==sqr2){
  	std::cout<<"\nThe list are same ";
  }
  else{
  	std::cout<<"\nThe lists are not same";
  }
    sq.clear(); 
   std::cout<<" \nis unordered map empty or not  = "<<sq.empty()<<std::endl;

    return 0;
}