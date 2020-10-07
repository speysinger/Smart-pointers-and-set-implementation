#include <stdlib.h>
#include <iostream>
#include "unique_ptr.h"

class Price{
public:
	Price() { value = 10; };
	~Price() {};
	int value = 0;
};

int main()
{

	unique_ptr<Price> test(new Price);
	unique_ptr<Price> test3 = std::move(test);
	test3->value = 5;

	unique_ptr<Price> test4(new Price);
	test4.swap(test3);

	system("pause");
	return 0;
}