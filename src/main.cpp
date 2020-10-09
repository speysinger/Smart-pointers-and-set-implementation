#include <stdlib.h>
#include <iostream>

#include "unique_ptr.h"
#include "shared_ptr.h"

class Price{
public:
	Price() { value = 10; };
	~Price() {};
	int value = 0;
};

int main()
{
	shared_ptr<Price> test(new Price);
	shared_ptr<Price> test2(test);
	shared_ptr<Price> test4 = test2;

	system("pause");
	return 0;
}