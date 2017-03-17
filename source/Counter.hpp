/**
 *  @file Counter.hpp
 *
 *  Created by John D. Hopkins on 3/13/17.
 */

#ifndef Counter_hpp
#define Counter_hpp


#include "Input_file_list.hpp"
#include "File_token_counter.hpp"
#include "Output_sorting_file.hpp"

namespace counterLib {

	/**
	 *	Main class for the 'counter' program.
	 *	Brings together all other classes.
	 *	Directly instantiated and called in main().
	 *	All other custom classes for this program essentially wrap files.
	 *	Following RAII (Resource Acquisition Is Initialization),
	 *	each of the other classes opens a file for the name passed to its constructor.
	 *	The file is then closed in the class's destructor. 
	 *	As this class initializes the input and output file classes as data members,
	 *	their files are also open for the lifetime of an instance of this class. 
	 *	Because the file stream data members of this class's aggregate classes
	 *	are not copyable, neither is this class.
	 */

	class Counter {
	public:
		
		static Counter* singleton_instance(const std::string inputFileName, const std::string outputFileName);
		
		/**
		 *	Destructor
		 *
		 *	Closes both the input file and the output file,
		 *	opened by the initializing constructor.
		 */
		~Counter();
		
		/**
		 Counts the tokens of the files listed in the input file. 
		 Then generates the output and writes it to the output file.
		 Equivalent to running count_tokens() and then generate_output().
		 */
		void execute();

		/**
		 Tokenizes the files listed in the input file, 
		 counting their unique individual frequencies.
		 Call before generate_output().

		 @return The total number of unique tokens found.
		 */
		unsigned long count_tokens();
		
		/**
		 Sorts the unique tokens according to their frequency (from most to least),
		 Then writes them to the output file. Each line is a token, 
		 followed by its frequency.
		 */
		void generate_output();
		
		/**
		 Writes the result of generate_output() above to the given stream.

		 @param out [IN/OUT] The output stream to write to.
		 */
		void result_to_output(std::ostream& out) {
			osf->write_to_output(out);
		}
		
	private:
		/**
		 *	Initializing Constructor
		 *
		 *	Opens the named input file for reading and
		 *	the named output file for writing.
		 *
		 *	@param inputFileName [IN] The filename (path) of the input file,
		 *		which contains a list of filenames, one filename per line.
		 *		The files should contain UTF-8 text for tokenization and counting.
		 *
		 *	@param outputFileName [IN/OUT] The filename (path) of the output file.
		 */
		Counter(const std::string inputFileName, const std::string outputFileName);
		
		Input_file_list* ifl;
		Output_sorting_file* osf;
		Token_count_map tcm;
		
	};
	
}

#endif /* Counter_hpp */
