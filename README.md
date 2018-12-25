# CPParam
A very short C++ 11 header-only library to help you know if you have to pass a function's paramter by value (with a copy) or by constant reference.

# The problem
You can pass 3 types of parameter to a function:
* __in__ : a parameter you only use as an input so you don't modify it
* __out__ : a parameter you only use as a return value so you modify it
* __in and out__: a parameter you use as input and return value

This library is focused on __in__ parameter. In c++ there is 2 ways to do it: by value or by const reference (or by const pointer but this is a bad practice, because it is not safe, if you want an optional value use the __optional__ class from the std or boost).

But how to know which one should be used in which case?

# The difference between passing argument by value or constant reference
First to know which one you should use, it is important to know the differences between them.

## Passing by value
The synxtaxe is simple you just write the type like this
```C++
int value
```
The the function signature look like this
```C++
void function(int value);
```

When you pass a parameter it is important to know that a copy will be made callinf the copy constructor (if this is an object), if the parameter is big (for example a structure with a lot of attributes) or if the parameter if not trivially copy constructible (for example a std::vector it needs to allocate memory for the new vector) it can slow down the program. Even worse, if the class is not copyable (std::thread for example) the code won't compile.

## Passing by constant reference
The synxtaxe is a bit more complicated, you need to add the keyword __const__ and the operator __&__
```C++
const std::string& value
```
The the function signature look like this
```C++
void function(const std::string& value);
```

When you pass a parameter by constant reference you are passing a pointer to the variable you want to send (a reference is basically a pointer which can't be null) and you can't change the value. It works approximately the same way as passing it as a value. (If you capture the constant reference in the contexte of a lambda function by reference and you are using the lambda later when the reference is not valid anmymore it will make the program crash, so be carefull with reference when you are using lambda)

# How to choose?
When you need to send a parameter which is smaller or have the same size as a pointer and which is trivially copy constructible pass the argument by value, because it will be faster or as fast as a contant reference and the synxtaxe is simpler. For example pass by value integral types (int, int32_t, char etc), floating types (float, double) and small types like a structure containing only one integer.

For everything else in most case a constant reference should be used because it is faster.

# What does this library do?
This library chooses automatically between passing a parameter by value or by constant reference.

# How does this lib work?
The __Param__ type is an alias for a __std::conditional__. It look like this __std::conditional<Condition, type1, type2>__ at compile time, if the condition return true the type used will be __type1__ else it will be __type2__.

The condition used here get the size of the parameter's type with the __sizeof__ operator and compare it with the size of a pointer. It also check if the type is trivially copy constructible.

# How to use it?
The following example is pretty explicit:
```C++
void my_test_function(Param<std::string> str, Param<double> decimal)
{
	std::cout << str << std::endl;
	std::cout << decimal << std::endl;
}
```
You just need to pass the type of your paramter as template parameter of the __Param__ class then you can use the parameter as usual.

You can run the an example by compiling the file __src/main.cpp__ (with cmake or with the command "g++ src/main.cpp -std=c++14"), note this lib need only c++ 11 but the example need c++14.

# How to install it?
You just need to add the header file __Param.hpp__ located in the __src__ folder to your project.
