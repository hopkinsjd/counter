/**
 *	@file main.cpp
 *
 *	Takes care of the basic user interface and overall error handling. 
 *	Instantiates and executes the Counter class. 
 *
 *  Created by John D. Hopkins on 3/13/17.
 */

#include <iostream>
#include "Counter.hpp"

int main(int argc, const char * argv[]) {
	int theErr = 0;
	
	if (argc != 3) {
		std::cout << "Usage: ./counter input.txt output.txt" << std::endl;
		theErr = 1;
	}
	else {
		try {
			counterLib::Counter c { argv[1], argv[2] };
			c.execute();
			
			std::cout << "Output written to " << argv[2] << ":" << std::endl;
			c.result_to_output(std::cout);
		}
		catch (std::invalid_argument&  ia) {
			std::cout << "Invalid argument: " << ia.what() << std::endl;
			theErr = 2;
		}
		catch (std::exception& e ) {
			std::cout << e.what() << std::endl;
			theErr = 3;
		}
	}
	
	return theErr;
}
