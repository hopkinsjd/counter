//
//  counter_test.cpp
//  counter
//
//  Created by John D. Hopkins on 3/13/17.
//

#include "counter.hpp"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CounterTests
#include <boost/test/unit_test.hpp>

using namespace counterLib;

/*	1.	Open a file specified as the first parameter on the command-line
		that contains a list of filenames, one filename per line.
 */
BOOST_AUTO_TEST_SUITE( Input_file_list_suite )

BOOST_AUTO_TEST_CASE( Open_input_file ) {
	BOOST_REQUIRE_NO_THROW(Input_file_list("input.txt"));
}

BOOST_AUTO_TEST_CASE( Get_a_list_of_files ) {
	Input_file_list fl("input.txt");
	BOOST_REQUIRE(fl.file_count() > 0);
}

BOOST_AUTO_TEST_CASE( Throw_error_when_opening_bad_input_file ) {
	BOOST_REQUIRE_THROW(Input_file_list("bogus_file.txt"), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()


/*
	2.	For each filename in the list, read each file and tokenize the contents.
		a.	Tokenizing for this problem is defined as separating the file into words
			(characters delimited by whitespace), 
			stripping leading and trailing punctuation, 
			and forcing the token to be lowercase.
 */
BOOST_AUTO_TEST_SUITE ( File_token_counter_test_suite )

BOOST_AUTO_TEST_CASE( Open_each_file_for_token_counts ) {
	Input_file_list ifl("input.txt");

	for (auto fnIter = ifl.cbegin(); fnIter != ifl.cend(); ++fnIter ) {
		BOOST_REQUIRE_NO_THROW(File_token_counter tc(*fnIter));
	}
}

BOOST_AUTO_TEST_CASE( Tokenized_content_exists ) {
	Input_file_list ifl("input.txt");
	
	Token_count_map tcm;
	for (auto fnIter = ifl.cbegin(); fnIter != ifl.cend(); ++fnIter ) {
		File_token_counter tc(*fnIter);
		tc.add_to_map(tcm);
	}
	BOOST_REQUIRE(tcm.size() > 0);
	
}

BOOST_AUTO_TEST_CASE( Token_keys_are_strictly_alphanumeric ) {
	Input_file_list ifl("input.txt");
	
	Token_count_map tcm;

	for (auto fnIter = ifl.cbegin(); fnIter != ifl.cend(); ++fnIter ) {
		File_token_counter tc(*fnIter);
		tc.add_to_map(tcm);
	}
	
	for (auto p : tcm) {
		for (auto c : p.first) {
			BOOST_REQUIRE(isalnum(c));
		}
	}
}

BOOST_AUTO_TEST_CASE( Token_keys_are_strictly_lowercase ) {
	Input_file_list ifl("input.txt");
	
	Token_count_map tcm;
	
	for (auto fnIter = ifl.cbegin(); fnIter != ifl.cend(); ++fnIter ) {
		File_token_counter tc(*fnIter);
		tc.add_to_map(tcm);
	}
	
	for (auto p : tcm) {
		for (auto c : p.first) {
			BOOST_REQUIRE(islower(c));
		}
	}
}

BOOST_AUTO_TEST_CASE( Throw_error_when_opening_bad_token_file ) {
	BOOST_REQUIRE_THROW(File_token_counter("bogus_file.txt"), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

/*
	3.	Output a file specified by the second parameter on the command line
		containing a list of total unique tokens and their count, 
		each on a separate line, sorted by frequency.
*/
BOOST_AUTO_TEST_SUITE ( Output_sorting_file_test_suite )

BOOST_AUTO_TEST_CASE( Can_open_output_file ) {
	BOOST_REQUIRE_NO_THROW(Output_sorting_file("output.txt"));
}

BOOST_AUTO_TEST_CASE ( Output_is_generated ) {
	Input_file_list ifl("input.txt");
	
	Token_count_map tcm;
	
	for (auto fnIter = ifl.cbegin(); fnIter != ifl.cend(); ++fnIter ) {
		File_token_counter tc(*fnIter);
		tc.add_to_map(tcm);
	}
	
	Output_sorting_file osf("output.txt");
	osf.set_sorted(tcm);
	
	BOOST_REQUIRE( osf.token_count() > 0 );
}

BOOST_AUTO_TEST_CASE ( Output_is_sorted_by_frequency ) {
	Input_file_list ifl("input.txt");
	
	Token_count_map tcm;
	
	for (auto fnIter = ifl.cbegin(); fnIter != ifl.cend(); ++fnIter ) {
		File_token_counter tc(*fnIter);
		tc.add_to_map(tcm);
	}
	
	Output_sorting_file osf("output.txt");
	osf.set_sorted(tcm);
	
	auto a = osf.cbegin(), b = osf.cbegin();
	for ( ++b ; b != osf.cend(); ++a, ++b) {
		BOOST_REQUIRE(a->second >= b->second);
	}
}

BOOST_AUTO_TEST_CASE ( Output_tokens_are_unique ) {
	Input_file_list ifl("input.txt");
	
	Token_count_map tcm;
	
	for (auto fnIter = ifl.cbegin(); fnIter != ifl.cend(); ++fnIter ) {
		File_token_counter tc(*fnIter);
		tc.add_to_map(tcm);
	}
	
	Output_sorting_file osf("output.txt");
	osf.set_sorted(tcm);
	
	std::set<std::string> token_set;
	for (auto i = osf.cbegin(); i != osf.cend(); ++i) {
		token_set.insert(i->first);
	}
	
	BOOST_REQUIRE(token_set.size() == osf.token_count());
	
}

BOOST_AUTO_TEST_SUITE_END()


namespace utf = boost::unit_test;

struct F {
	F() {
		 Counter_singleton = Counter::singleton_instance( "input.txt", "output.txt");
	}
	
	~F() {
		delete Counter_singleton;
	}

	static Counter* Counter_singleton;
		
};

Counter* F::Counter_singleton = nullptr;

BOOST_AUTO_TEST_SUITE ( Counter_singleton_test_suite, * utf::fixture<F>() )

BOOST_AUTO_TEST_CASE ( Output_file_generated ) {
	
	F::Counter_singleton->execute();
	
	std::ifstream output_file ("output.txt");
	bool canOpen = false;
	if (output_file.is_open()) {
		canOpen = true;
		output_file.close();
	}
	
	BOOST_REQUIRE(canOpen);
}

BOOST_AUTO_TEST_CASE( Output_file_lines_match_token_count ) {
	unsigned long token_count = 0;
	
	token_count = F::Counter_singleton->count_tokens();
	F::Counter_singleton->generate_output();
	
	std::ifstream output_file ("output.txt");
	unsigned long line_count = 0;
	std::string line;
	if (output_file.is_open()) {
		while ( getline(output_file, line)) {
			line_count++;
		}
	}
	
	BOOST_REQUIRE(line_count == token_count);
}

BOOST_AUTO_TEST_SUITE_END()

