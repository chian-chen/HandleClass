#include <iostream>
#include <cstring>
#include <string>

using namespace std;

int main()
{
    /* Intro to C-Style string	
   		
	   	String in ordinary C is just char array terminated by '\0'
		We call it NULL-terminated since ASCII for '\0' is just 0
		
		To use c-style string, you need to either
		1. #include <string.h> if you are writing a C program
		2. #include <cstring> if you are writing a C++ program

	*/

    // declaring a c string ('\0' terminated char array)
    char sound[] = "mepu";

    // prints mepu
    cout << sound << endl;

    // mepu again
    printf("%s\n", sound);

    // length will be 4, but size is actually 5 becuase sound[4] is '\0'
    cout << "length of c-style string is : " << strlen(sound) << endl;
    cout << "size of memory allocated for c-style string is : " << sizeof(sound) << endl;

    // comparing two strings, strcmp returns 0 if two strings are identical
    char country[] = "Taiwan";

    if (!strcmp(country, "China"))
    {
    }
    else
    {
        cout << "you mad? cuz im not" << endl;
    }

    // copying one string into another
    char *new_sound = new char(sizeof(sound)); // remember to allocate space for the '\0' too
    strcpy(new_sound, sound);
    cout << new_sound << endl;

    // splitting a string
    char sentence[] = "over my dead body";
    char *word;
    word = strtok(sentence, " "); // split the sentence with the first " " it can find and return the former substring
    cout << word << endl;         // prints over
    word = strtok(NULL, " ");     // continue splitting the sentence with the first " " it can find and return the former substring
        // you must NOT write strtok(sentence," ") or else it will start from the beginning of sentence
        // and you will get word = "over" again

    cout << word << endl; // prints my
    word = strtok(NULL, " ");
    cout << word << endl;

    /* Intro to std::string
		
	   	std::string is a class that provides easier and more intuitive interface

		To use std::string, you need to do #include <string>

	*/

    // declaring a string
    string s("What's my name?");
    cout << s << endl;
    string myname = "Francis";
    cout << myname << endl;

    // get the length of string
    cout << myname.length() << endl;

    // assigning a string
    string newname = myname; // the operator '=' is overloaded for the string class

    // comparing a string
    if (newname == myname)
    { // the operator '==' is also overloaded
        // do something
    }

    // converting a std::string into cstring
    char *name = new char(myname.length() + 1);
    strcpy(name, myname.c_str());
    cout << name << endl;
}
