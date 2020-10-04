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
	unique_ptr<Price> test2(test);
	unique_ptr<Price> test3 = std::move(test2);
	system("pause");
	return 0;
}