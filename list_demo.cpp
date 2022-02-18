#include <iostream>
#include <list>

using namespace std;

class human
{
    const char *name;
    bool sex;
    int age;

public:
    human() : name("TL-Yu"), sex(1), age(18) {}
    const char *get_name()
    {
        return name;
    }
};

int main()
{

    /* Intro to stl::list

	   List is an useful container we can store data in, you can roughly imagine it as an array with dynamic size.
	   To use a list, all you need to do is #include <list>. then you can call the functions that manupilate a list, without the need to worry about newing and deleting any memory.

	   In this project, we will be treating a list as a stack, so below i'll demonstrate 3 main utilities to acheive this purpose
	   	1. list.push_back()	// push a data into the stack
		2. list.back()		// get the data stored on the top of the stack
		3. list.pop_back()	// pop a data out of the stack

	   Let's begin.

	*/

    // declaring a list for integers (as you can see, list is written as a template)
    list<int> stack;

    // pushing an integer 1 to the stack
    stack.push_back(1);

    // pushing another integer 2 to the stack
    stack.push_back(2);

    // getting the data on the top, in this case, an int 2 is returned
    cout << stack.back() << endl;

    // popping the integer from the top of the stack
    stack.pop_back(); // Attention!
                      // pop_back() returns void, it does not return the data stored on the top of your stack
                      // If you want the value instead, use back()

    // this time back() returns 1, as 2 is already popped
    cout << stack.back() << endl;

    // std::list can also store class objects!
    list<human> another_stack;

    // initializing an object and push it into the stack
    human professor;
    another_stack.push_back(professor);
    cout << another_stack.back().get_name() << endl;

    return 0;
}
