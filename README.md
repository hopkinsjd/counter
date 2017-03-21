# counter
C++ code exercise for counting and displaying token frequencies in given files. 

### Implementation Notes
This exercise was implemented using C++11. An Xcode project unifies things, but the source files can be put into any other IDE supporting C++11. The counter Xcode target will build and run a counter executable. The Unit Test target, not surprisingly, runs the unit tests. 

A few extras were added beyond what is mentioned in the original documentation below. They help to make the implementation a better example of modern software development. 

First, the exercise was built using test-driven development (see "Unit Tests/counter_test.cpp). The Boost Unit Test Framework was used. This is freely available and popular with many C++ developers. It only affects the above mentioned file. No Boost libraries were used in the actual implementation code. 

Second, some extra class methods (and non-class methods) were added to make the classes "smart" to work with. This includes move constructors, move assignment operators, and swap for most of the classes. Copy constructors and copy assignment operators were deleted because file streams can't be copied. These extras were not added to the Counter class because it is a Singleton (Design Pattern) managing the other classes.  

Third, concurrency programming was added to handle the tokenization of multiple files at the same time. Concurrency is only invoked after a file number threshold is reached and is expressed as a `static const int` in the Counter class. Currently that threshold is set to 2 for this exercise, but could be increased upon further performance testing. Threads and how many to use are handled via the C++11 `async` function.

In addition to using concurrency to improve performance, other items specific to C++11 were used. This included using the hash-based unordered_map,  with constant-time lookup and insertion; inserting items into containers using `emplace` and `emplace_back`; as well as the use of move assignment and construction throughout. Though not specific to C++11, the `std::list` container was chosen over `std::vector` because `std::list` favors speedy element addition without needing to know the amount of elements ahead of time. 

Note further that the implementation widely uses the RAII principle (Resource Acquisition Is Initialization) as encouraged by Bjarne Stroustrup, the maker of the C++ language. All new/delete's and file open/close's are hidden in constructor/destructor methods respectively.

The Single Responsibility Principle of the SOLID software development principles was also followed. For example, string utility functions were separated out into their own file (`String_utils.hpp/cpp`), instead of included in the `File_token_counter` class. These functions are tested indirectly through the output of other classes of this exercise. 

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

You should approach this project as you would if you worked at the company in terms of quality, style,
and performance.
