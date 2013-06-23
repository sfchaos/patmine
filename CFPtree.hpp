#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>
#include <stddef.h>

namespace fpg {

using namespace std;

template <typename K, typename V>
bool less(const pair<K, V>& lhs, const pair<K, V>& rhs)
{
  return lhs.second < rhs.second;
}

template <typename K, typename V>
bool greater(const pair<K, V>& lhs, const pair<K, V>& rhs)
{
	return !less(lhs, rhs);
}

template <typename K, typename V>
ostream& operator<< (ostream& os, const pair<K, V>& x)
{
	os << "key: " << x.first << " value: " << x.second << endl;
	return os;
}

template <typename K, typename V>
struct Node
{
	typedef std::pair<K, V> NodeInfo;
	NodeInfo ni;
	Node *lch;
	Node *rch;
};

template <typename K = string, typename V = unsigned int>
class FPtree
{
public:
	typedef pair<K, V> node_info;
	typedef Node<K, V> node_type;

private:
	//vector<pair<K, vector<V> > > data;
	vector<vector<K> > tran;
	map<K, V> itemfreq;
	list<pair<K, V> > itemlist;
	unsigned int minsup_;

public:
	FPtree(unsigned int minsup) : minsup_(minsup) {}

	node_type *insert(node_type *p, node_info &node) {
		if (p == NULL) {
			p = new node_type;
			p->ni = node;
			p->lch = NULL;
			p->rch = NULL;
			return p;
		}
	}

	istream& readData(istream &is) {
		string line;
		vector<K> tmp;
		//multimap<K, V> tmp;
		K item;
		ifstream ifs;

		while (getline(is, line)) {
			tmp.clear();
			istringstream istrs((char *) line.c_str());
			while (istrs >> item) {
				if (tmp.find(item)==tmp.end()) {
					tmp.push_back(item);
				}
				if (!itemfreq.insert(std::pair<K, V>(item, 1)).second) {
					itemfreq[item]++;
				}
			}
			tran.push_back(tmp);
		}

		return is;
	}

	void construct() {
		for (typename map<K, V>::iterator itr = itemfreq.begin();
				itr != itemfreq.end(); ++itr) {
			V value = itr->second;
			if (value >= minsup_) {
				itemlist.push_back(*itr);
			}
		}
		/*
		for (typename list<pair<K, V> >::iterator itr = itemlist.begin();
				itr != itemlist.end(); ++itr) {
			K key = itr->first;
			V value = itr->second;
			std::cout << "key: " << key << ", value: " << value << std::endl;
		}
		*/
		itemlist.sort(&greater<K, V>);
		//copy(itemlist.begin(), itemlist.end(),
		//		ostream_iterator<pair<K, V> >(cout, "\n"));
		for (typename list<pair<K, V> >::iterator itr = itemlist.begin();
				itr != itemlist.end(); ++itr) {
			K key = itr->first;
			V value = itr->second;
			std::cout << "key: " << key << " value: " << value << std::endl;
			std::cout << "successful" << std::endl;
		}


	}
};

}
