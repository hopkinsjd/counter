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
	// legitimate file opens
	Input_file_list ifl("input.txt");
	BOOST_REQUIRE(ifl.file_count() > 0); // one or more listed filenames
	// We can iterate over them with range for loop and they are not empty strings.
	for (auto fli : ifl)
		BOOST_REQUIRE(!fli.empty());
}

BOOST_AUTO_TEST_CASE( Throw_error_when_opening_bad_input_file ) {
	BOOST_REQUIRE_THROW(Input_file_list("bogus_file.txt"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE ( Move_constructor_and_assignment ) {
	auto f = [](){ return Input_file_list ("input.txt"); }; // lambda
	auto ifl1 = f(); // move assignment works
	// Input_file_list ifl2(ifl1); // compiler error because copy constructor deleted
	Input_file_list ifl2(std::move(ifl1)); // move constructor ok
	// ifl1 = ifl2; // compiler error because copy assignment is deleted
	BOOST_REQUIRE (ifl2.file_count() > 0);
	BOOST_REQUIRE (ifl1.file_count() == 0);
}

BOOST_AUTO_TEST_CASE ( Swapping ) {
	Input_file_list ifl1("input.txt");
	Input_file_list ifl2("input2.txt");
	unsigned long origFC1 = ifl1.file_count();
	unsigned long origFC2 = ifl2.file_count();
	
	swap(ifl1, ifl2);
	
	BOOST_REQUIRE( ifl1.file_count() == origFC2 );
	BOOST_REQUIRE( ifl2.file_count() == origFC1 );
	
	ifl1.swap(ifl2);
	
	BOOST_REQUIRE( ifl1.file_count() == origFC1 );
	BOOST_REQUIRE( ifl2.file_count() == origFC2 );
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

BOOST_AUTO_TEST_CASE ( Move_constructor_and_assignment ) {
	Token_count_map tcm1, tcm2, tcm3;

	auto f = [](){ return File_token_counter ("test.txt"); }; // lambda
	auto ftc1 = f(); // move assignment works
	
	ftc1.add_to_map(tcm1);
	auto origTCTokenCount1 = tcm1.size();
	BOOST_REQUIRE (origTCTokenCount1 > 0);
	
	//File_token_counter ftc2(ftc1); // compiler error because copy constructor deleted
	File_token_counter ftc2(std::move(ftc1)); // move constructor ok
	//ftc1 = ftc2; // compiler error because copy assignment is deleted
	
	ftc2.add_to_map(tcm2);
	auto origTCTokenCount2 = tcm2.size();
	
	BOOST_REQUIRE (origTCTokenCount1 == origTCTokenCount2);
	
	ftc1.add_to_map(tcm3);
	BOOST_REQUIRE (tcm3.size() == 0);
}

BOOST_AUTO_TEST_CASE ( Swapping ) {
	File_token_counter ftc1("test.txt");
	File_token_counter ftc2("test2.txt");
	
	Token_count_map tcm1, tcm2, tcm3, tcm4, tcm5, tcm6;
	
	ftc1.add_to_map(tcm1);
	ftc2.add_to_map(tcm2);
	
	auto origTC1 = tcm1.size();
	auto origTC2 = tcm2.size();
	
	BOOST_REQUIRE(origTC1 > 0);
	BOOST_REQUIRE(origTC2 != origTC1);
	
	swap(ftc1, ftc2);
	
	ftc1.add_to_map(tcm3);
	ftc2.add_to_map(tcm4);
	
	BOOST_REQUIRE( tcm3.size() == origTC2 );
	BOOST_REQUIRE( tcm4.size() == origTC1 );
	
	ftc1.swap(ftc2);
	
	ftc1.add_to_map(tcm5);
	ftc2.add_to_map(tcm6);
	
	BOOST_REQUIRE( tcm5.size() == origTC1 );
	BOOST_REQUIRE( tcm6.size() == origTC2 );
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

BOOST_AUTO_TEST_CASE ( Move_constructor_and_assignment ) {
	File_token_counter ftc("test.txt");
	Token_count_map tcm;
	ftc.add_to_map(tcm);
	
	auto f = [](){ return Output_sorting_file ("output.txt"); }; // lambda
	auto osf1 = f(); // move assignment works
	
	osf1.set_sorted(tcm);
	auto origTokenCount = osf1.token_count();
	BOOST_REQUIRE( origTokenCount > 0 );
	
	// Input_file_list ifl2(osf1); // compiler error because copy constructor deleted
	Output_sorting_file osf2(std::move(osf1)); // move constructor ok
	// osf1 = osf2; // compiler error because copy assignment is deleted
	
	BOOST_REQUIRE( osf2.token_count() == origTokenCount );
	
	BOOST_REQUIRE( osf1.token_count() == 0);
}

BOOST_AUTO_TEST_CASE ( Swapping ) {
	File_token_counter ftc1 { "test.txt" };
	File_token_counter ftc2 { "test2.txt" };
	
	Token_count_map tcm1, tcm2;
	
	ftc1.add_to_map(tcm1);
	ftc2.add_to_map(tcm2);
	
	Output_sorting_file osf1 { "output.txt" };
	Output_sorting_file osf2 { "output2.txt" };
	
	osf1.set_sorted(tcm1);
	osf2.set_sorted(tcm2);
	
	auto origTCount1 = osf1.token_count();
	auto origTCount2 = osf2.token_count();
	
	BOOST_REQUIRE( origTCount1 != origTCount2 );
	
	swap( osf1, osf2 );
	
	BOOST_REQUIRE( osf1.token_count() == origTCount2 );
	BOOST_REQUIRE( osf2.token_count() == origTCount1 );
	
	osf1.swap(osf2);
	
	BOOST_REQUIRE( osf1.token_count() == origTCount1 );
	BOOST_REQUIRE( osf2.token_count() == origTCount2 );
}

BOOST_AUTO_TEST_SUITE_END()


/* COUNTER SINGLETON TESTS */
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

