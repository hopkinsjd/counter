//
//  counter.cpp
//  counter
//
//  Created by John D. Hopkins on 3/13/17.
//

#include "Counter.hpp"
#include <future>

namespace counterLib {
	/*
	 C++11 mandates that the initializer for a local static variable is only run once,
	 even in the presence of concurrency. So, assuming you’ve got a modern C++ compiler,
	 this code is thread-safe, where the classic example from Design Patterns 
	 (Gamma, et al) is not. (See http://gameprogrammingpatterns.com/singleton.html ). 
	 Though this article discourages the use of Singletons, 
	 this is a simple enough program that the issues don't really matter.
	 It also uses the solution they give for thread safety.
	 It shows some application of object-oriented design patterns.
	 Since this is a singleton, there's no need to worry about copy, move, or swap.
	 */
	Counter* Counter::singleton_instance(const std::string inputFileName, const std::string outputFileName) {
		static Counter * instance = new Counter(inputFileName, outputFileName);
		return instance;
	}

	Counter::Counter(const std::string inputFileName, const std::string outputFileName) :
		ifl {new Input_file_list { inputFileName } },
		osf {new Output_sorting_file { outputFileName } } { }

	Counter::~Counter() {
		delete ifl;
		delete osf;
	}

	void Counter::execute() {
		count_tokens();
		generate_output();
	}

	unsigned long Counter::count_tokens() {
		tcm.clear();
		for (auto fnIter = ifl->begin(); fnIter != ifl->end(); ++fnIter ) {
			File_token_counter tc(*fnIter);
			tc.add_to_map(tcm);
		}
		return tcm.size();
	}

	void Counter::generate_output() {
		osf->clear();
		osf->set_sorted(tcm);
		osf->write_to_file();
	}

}
