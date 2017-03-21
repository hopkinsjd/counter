//
//  counter.cpp
//  counter
//
//  Created by John D. Hopkins on 3/13/17.
//

#include "Counter.hpp"
#include <future>

namespace counterLib {
	const int Counter::concurrency_file_number_threshold = 2;
	
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
	Counter* Counter::singleton_instance(const char* inputFileName, const char* outputFileName) {
		static Counter * instance = new Counter(inputFileName, outputFileName);
		return instance;
	}

	Counter::Counter(const std::string& inputFileName, const std::string& outputFileName) :
		_ifl {new Input_file_list { inputFileName } },
		_osf {new Output_sorting_file { outputFileName } } { }

	Counter::~Counter() {
		delete _ifl;
		delete _osf;
	}

	void Counter::execute() {
		concurrent_count_tokens();
		generate_output();
	}

	unsigned long Counter::count_tokens() {
		_tcm.clear();
		for (auto fnIter = _ifl->cbegin(); fnIter != _ifl->cend(); ++fnIter ) {
			File_token_counter tc(*fnIter);
			tc.add_to_map(_tcm);
		}
		return _tcm.size();
	}
	
	Token_count_map get_file_token_map(std::string filename) {
		Token_count_map tcmf; // just for this file
		
		File_token_counter ftc(filename);
		ftc.add_to_map(tcmf);
		
		return tcmf;
	}

	unsigned long Counter::concurrent_count_tokens() {
		unsigned long token_count = 0;
		
		if (_ifl->file_count() < concurrency_file_number_threshold) {
			token_count = count_tokens();
		}
		else {
			// get token counts concurrently
			// make a list of futures based on token count maps
			// of each file of our input file list, taken from async calls
			std::list<std::future<Token_count_map>> futureTCMList;
			for (auto s = _ifl->cbegin(); s != _ifl->cend(); ++s ) {
				auto futureTCM = std::async(get_file_token_map, *s);
				futureTCMList.push_back(std::move(futureTCM));
			}
			// get each file's token map and combine it with this object's
			for (auto fi = futureTCMList.begin();
				 fi != futureTCMList.end(); ++fi ) {
				add_map(fi->get());
			}
			token_count = _tcm.size();
		}
		
		return token_count;
	}
	
	void Counter::add_map(const Token_count_map& aTCM) {
		for (auto tc: aTCM) {
			auto i = _tcm.find(tc.first);
			if (i == _tcm.end()) {
				// doesn't exist, add
				_tcm.emplace(tc.first, tc.second);
			}
			else {
				i->second += tc.second;
			}
		}
	}

	void Counter::generate_output() {
		_osf->clear();
		_osf->set_sorted(_tcm);
		_osf->write_to_file();
	}

}
