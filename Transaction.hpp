#ifndef TRANSACTION_HPP_
#define TRANSACTION_HPP_

#include <algorithm>
#include "Item.hpp"

namespace cfp {
using namespace std;


class Transaction {
public:
  typedef vector<Item> transaction;

	Transaction() {}
	Transaction(Item &item) { tran_.push_back(item); }
	Transaction(transaction &tran) : tran_(tran) {}
	~Transaction() {}

	void push_back(Item &item) { tran_.push_back(item); }
	void clear() { tran_.clear(); }

private:
	transaction tran_;
};

class TransactionDB {
public:
	TransactionDB() {}
	~TransactionDB() {
		std::for_each(tranDB.begin(), tranDB.end(), [](Transaction* p) { delete p; });
		tranDB.clear();
	}
	void push_back(Transaction &tran) {
		tranDB.push_back(&tran);
	}
private:
	vector<Transaction*> tranDB;
};

} /* namespace cfp */
#endif /* TRANSACTION_HPP_ */
