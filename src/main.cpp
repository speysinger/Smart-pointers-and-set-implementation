#include <stdlib.h>
#include <iostream>

#include "unique_ptr.h"
#include "shared_ptr.h"
#include "set.h"

struct Author {
	int id = 0;
	const char *name;
	Author(int id, const char *name) {
		this->id = id;
		this->name = name;
	}
	bool operator==(const Author& other) const {
		return other.id == id;
	}

	friend bool operator<(const Author& x, const Author& y) {
		return x.id > y.id;
	}
	friend bool operator>(const Author& x, const Author& y) {
		return x.id < y.id;
	}
};

int main()
{
	int id = 0;
	Author author(1, "nikita");
	Author author1(2, "sasha");
	Author author2(3, "sergey");
	Author author3(4, "kostya");
	Author author4(5, "pasha");
	set<Author> authorsList;

	authorsList.insert(author);
	authorsList.insert(author1);
	authorsList.insert(author2);
	authorsList.insert(author3);
	authorsList.insert(author4);

	Author requiredAuthor(3, "");
	auto reqAuthor = authorsList.find(requiredAuthor);

	system("pause");
	return 0;
}