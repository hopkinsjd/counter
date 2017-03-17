/**
 *	@file Output_sorting_file.hpp
 *
 *  Created by John D. Hopkins on 3/14/17.
 */

#ifndef Output_sorting_file_hpp
#define Output_sorting_file_hpp

#include <set>
#include "File_token_counter.hpp"

namespace counterLib {

	/**
	 *	Encapsulates an output file that sorts its content before writing.
	 *	The output text is a list of total unique tokens and their count,
	 *	supplied to this object, each on a separate line, sorted by frequency.
	 *	The sort order goes from most frequent to least frequent.
	 */
	class Output_sorting_file {
	public:
		
		/**
		 *	Holds the token and its frequency.
		 */
		using Token_count = std::pair<std::string, int>;
		
		/**
		 *	Constant iterator to traverse internal set of sorted Token_count's.
		 *	Prevents alteration of private data member (read-only).
		 */
		using TC_set_const_iter = std::set<Token_count>::const_iterator;
		
		/**
		 *	Initializing Constructor
		 *
		 *	Opens an output file for writing.
		 *
		 *	@param outputFileName [IN] A filename (path) of an output file.
		 */
		Output_sorting_file(const std::string outputFileName);
		
		/**
		 *	Copy constructer (deleted)
		 *
		 *	Deleted because can't copy ofstreams (iFile).
		 *
		 */
		Output_sorting_file (const Output_sorting_file&) = delete;

		/**
		 *	Move constructor (works)
		 *
		 *	@param other [IN] rvalue of another Input_file_list.
		 */
		Output_sorting_file (Output_sorting_file&& other) noexcept;

		/**
		 *	Destructor
		 *
		 *	Closes the output file opened by the initializing constructor.
		 */
		~Output_sorting_file();
		
		/**
		 Sets this object to the keys and values
		 of the given Token_count_map. They are sorted by frequency,
		 starting with the most frequent to the least.
		 Clears the contents before setting it. 
		 This does not write to the file of the object.
		 
		 @param tcm [IN] A map of unique token counts - unsorted.
		 */
		void set_sorted(Token_count_map& tcm);
		
		/**
		 Gets the starting iterator of this object's current sorted data output.

		 @return A constant iterator to the beginning of the set of unique token counts.
		 */
		TC_set_const_iter cbegin () const { return tcSet.cbegin(); }
		
		/**
		 Gets the ending iterator of this object's current sorted data output.

		 @return A constant iterator to just past the end of unique token counts.
		 */
		TC_set_const_iter cend () const { return tcSet.cend(); }
		
		/**
		 Writes the current sorted data to the given output stream.

		 @param out [OUT] the data stream to write to, including ofstreams.
		 */
		void write_to_output( std::ostream& out ) const;
		
		/**
		 Writes the current data to the open file of this object.
		 Resets the position to the beginning of the file before doing so,
		 just in case it was called previously.
		 */
		void write_to_file();
		
		/**
		 Gets the number of unique tokens currently stored in the object.

		 @return The number of unique tokens.
		 */
		unsigned long token_count() { return tcSet.size(); }
		
		/**
		 Clears the set of unique token counts currently stored in the object.
		 */
		void clear() { tcSet.clear(); }
		
	private:
		/**
		 Sorting functor for the token count set.
		 Sorts the set by the frequency of the token, largest first and
		 also then by token itself in alphabetical order.
		 */
		struct TC_compare {
			bool operator() (const Token_count& a, const Token_count& b);
		};
		
		std::set<Token_count, TC_compare> tcSet; // token count set
		std::ofstream oFile; // output file
	};
	
}
#endif /* Output_sorting_file_hpp */
