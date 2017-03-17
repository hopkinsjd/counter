//
//  counter.cpp
//  counter
//
//  Created by John D. Hopkins on 3/13/17.
//

#include "Counter.hpp"

namespace counterLib {
	/*
	 C++11 mandates that the initializer for a local static variable is only run once,
	 even in the presence of concurrency. So, assuming you’ve got a modern C++ compiler,
	 this code is thread-safe, where the classic example from Design Patterns 
	 (Gamma, et al) is not.
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
		for (auto fnIter = ifl->cbegin(); fnIter != ifl->cend(); ++fnIter ) {
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
