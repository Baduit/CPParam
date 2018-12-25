#include <iostream>

#include "Param.hpp"

using namespace std::string_literals;

struct Test
{
	int a;
	int b;
	int c;
	int d;
};

void my_test_function(Param<std::string> str, Param<double> decimal)
{
	std::cout << std::is_same<decltype(str), const std::string&>::value << std::endl;
	std::cout << std::is_same<decltype(decimal), double>::value << std::endl;
}

int main()
{
	std::cout << std::boolalpha;
	Test t;

	{
		Param<int> p(12);
		std::cout << std::is_same<decltype(p), int>::value << std::endl;
	}

	{
		Param<Test> p(t);
		std::cout << std::is_same<decltype(p), const Test&>::value << std::endl;
	}

	my_test_function("Hi"s, 9.9);
}