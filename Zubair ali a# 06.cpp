#include <iostream>
#include <list>

template<typename k, typename T>
class unordered_map {
private:
    std::list<std::pair<k, T> >* table;
    int m, n;
	float max_load_factor;
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
        max_load_factor=0;
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
	T& operator[](const k& key) {
		int h = hash(key);
		typename std::list<std::pair<const k, T>>::iterator it_list = table[h].begin();
		while (it_list != table[h].end()) {
			if (key == it_list->first) {
				return it_list->second;
			}
			else
				++it_list;
		}
		it_list = table[h].insert(it_list, { key,T() });
		++n;
		return it_list->second;
	}
void erase(const k& key) {
    int h = hash(key); 
    typename std::list<std::pair<k, T> >::iterator it = find(table[h], key);

    if (it != table[h].end()) {
        table[h].erase(it); 
        --n;               
    }
}
	int count(const k& key) const {
		iterator it;
		it = find(key);
		if (it == end())
			return 0;
		else
			return 1;
	}
	bool contains(const k& key) const {
		iterator it;
		it = find(key);
		if (it == end())
			return false;
		else
			return true;
	}
		T& at(const k& key) {
		int h = hash(key);
		typename std::list<std::pair<const k, T>>::iterator it_list = table[h].begin();
		while (it_list != table[h].end()) {
			if (key == it_list->first) {
				return it_list->second;
			}
			else
				++it_list;
		}
		throw ("Out Of Range!");
	}
	void rehash(int new_bucket_count) {
    std::list<std::pair<k, T>>* previous_table = table;
    int previous_bucket_count = m;
    m = new_bucket_count;
    table = new std::list<std::pair<k, T>>[m];
    n = 0;  
    for (int i = 0; i < previous_bucket_count ; i++) {
       for (typename std::list<std::pair<k,T>>::iterator it5 = previous_table[i].begin();it5 != previous_table[i].end();++it5) {
            int new_index = hash(it5.first);
            table[new_index].push_back(*it5);
            n++;
        }
    }
    delete[] previous_table;
}
void reserve(int require_value) {
    int require_buckets = require_value / max_load_factor+1;
    if (require_buckets > m) {
        rehash(require_buckets);
    }
}

bool empty ()const{
	return n==0;
}
int size ()const{
	return n;
}
int bucket_count() const {
    return m;
}
float maximum_load_factor() const {
    return max_load_factor;
}
float load_factor() const {
    if (m == 0)
       {
       	return 0.0f;
		} else{
			 return (float)n / m;
		}
   
}

int bucket_size(int index) const {
    if (index < 0 || index >= m){
    	 return 0;//index less than 0 and greater than m not ecceptable ;
	}
	else
    {
    	 return table[index].size();
	 }
}

void swap(unordered_map<k, T>& other) {
		std::swap(this, other);
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
   std::cout<<"\nAfter erase  unordered map conatians :\n";
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
  std::cout << "\nTotal buckets in list are : " << sqr.bucket_count() <<std:: endl;
std::cout << "\nElements in bucket at index  2: " << sqr.bucket_size(2) <<std:: endl;
    sq.clear(); 
   std::cout<<" \nis unordered map empty or not  = "<<sq.empty()<<std::endl;

    return 0;
}