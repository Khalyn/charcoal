#include <iostream>

#include "charcoal/core/boolean.hpp"
namespace cc = charcoal;

int main()
{
	cc::boolean constexpr displayHelloWorld = cc::True;
	if ( displayHelloWorld )
	{
		std::cout << "Hello World!" << std::endl;
	}

    return 0;
}
