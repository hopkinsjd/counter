# counter
C++ code exercise for counting and displaying token frequencies in given files. 

### Implementation Notes
This exercise was implemented using C++11. A couple of extras were added beyond what is mentioned in the original documentation below. They help to make the implementation a better example of modern software development. 

First was that exercise was built using test-driven development (see "Unit Tests/counter_test.cpp). The framework used was the Boost Unit Test Framework. This is freely available and popular with many C++ developers. It only affects the above mentioned file. No Boost libraries were used in the actual implementation code. 

Second, some extra class methods (and non-class methods) were added to make the classes "smart" to work with. This includes move constructors, move assignment operators, and swap for most of the classes. Copy constructors and copy assignment operators were deleted because file streams can't be copied. There was not time to add unit tests for these extras however. These extras were also not added to the main Counter class because it is meant to be used as a Singleton.  

Note further that the implemenation widely uses the RAII principle (Resource Acquisition Is Initialization) as encouraged by Bjarne Stroustrup, the maker of the C++ language. All new/deletes and file open/closes are hidden in constructor/destructor methods.

The Single Responsibility Principle of the SOLID software development principles was also followed. For example string utility functions were separated out into their own file (String_utils.hpp/cpp), instead of included in the File_token_counter class. 

### Original Exercise Documentation

Using C++, write a program to do the following:

1. Open a file specified as the first parameter on the command-line that contains a list of
filenames, one filename per line.
2. For each filename in the list, read each file and tokenize the contents.  
  a. Tokenizing for this problem is defined as separating the file into words
(characters delimited by whitespace), stripping leading and trailing punctuation,
and forcing the token to be lowercase.
3. Output a file specified by the second parameter on the command line containing a list of
total unique tokens and their count, each on a separate line, sorted by frequency.

For instance, if the first file (input.txt) contained a single line:

test.txt

And that file contained the text:
```
This is only a test. A *very* short test!
```

Running the program:
```
> ./counter input.txt output.txt
```

Would result in an output file (output.txt) that looks like:
```
a 2
test 2
is 1
only 1
short 1
this 1
very 1
```

You can use STL, but avoid usage of third-party libraries. Note that although the above example
is frequency and alphabetically sorted, only frequency sorting is required. For purposes of this
problem, you can assume all valid input files will be UTF-8 encoded English text. Use
Doxygen-style function documentation.

You should approach this project as you would if you worked at a company in terms of quality, style,
and performance.
