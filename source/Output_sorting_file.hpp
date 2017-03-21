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
	 Encapsulates an output file that sorts its content before writing.
	 The output text is a list of total unique tokens and their count,
	 supplied to this object, each on a separate line, sorted by frequency.
	 The sort order goes from most frequent to least frequent.
	 */
	class Output_sorting_file {
	public:
		
		/**
		 Holds the token and its frequency.
		 */
		using Token_count = std::pair<std::string, int>;
		
		/**
		 Constant iterator to traverse internal set of sorted Token_count's.
		 Prevents alteration of private data member (read-only).
		 */
		using TC_set_const_iter = std::set<Token_count>::const_iterator;
		
		/**
		 Regular iterator for traversing internal set of sorted Token_count's.
		 Allows use of Range For loop.
		 */
		using TC_set_iter = std::set<Token_count>::iterator;
		
		/**
		 Initializing Constructor
		 
		 Opens an output file for writing.
		 
		 @param outputFileName [IN] A filename (path) of an output file.
		 */
		Output_sorting_file(const std::string& outputFileName);
		
		/**
		 Copy constructer (deleted)
		 
		 Deleted because can't copy ofstreams (iFile).
		*/
		Output_sorting_file (const Output_sorting_file&) = delete;

		/**
		 Move constructor (works)
		 
		 @param other [IN] rvalue of another Input_file_list.
		 */
		Output_sorting_file (Output_sorting_file&& other) noexcept;

		/**
		 Destructor
		 
		 Closes the output file opened by the initializing constructor.
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
		TC_set_const_iter cbegin() const { return _tcSet.cbegin(); }
		
		/**
		 Non-const starting iterator of this objects' current sorted data output.
		 Allows use of Range For loop.

		 @return Iterator to the beginning of the set of unique token counts.
		 */
		TC_set_iter begin() const { return _tcSet.begin(); }
		
		/**
		 Gets the ending constant iterator of this object's current sorted data output.

		 @return A constant iterator to just past the end of unique token counts.
		 */
		TC_set_const_iter cend() const { return _tcSet.cend(); }
		
		/**
		 Gets the ending iterator of this object's current sorted data output.
		 
		 @return An iterator to just past the end of unique token counts.
		 */
		TC_set_iter end() const { return _tcSet.end(); }
		
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
		 Will return 0 initially until after a call to set_sorted(). 

		 @return The number of unique tokens.
		 */
		unsigned long token_count() { return _tcSet.size(); }
		
		/**
		 Clears the set of unique token counts currently stored in the object.
		 */
		void clear() { _tcSet.clear(); }
		
		/**
		 Member function that efficiently swaps the contents of this object.
		 'swap' is used by various STL containers.
		 So this member function is added in case an instance finds itself there.
		 
		 @param other [IN/OUT] Reference to another Input_file_list.
		 */
		void swap (Output_sorting_file& other) noexcept;
		
	private:
		/**
		 Sorting functor for the token count set.
		 Sorts the set by the frequency of the token, largest first and
		 also then by token itself in alphabetical order.
		 */
		struct TC_compare {
			bool operator() (const Token_count& a, const Token_count& b);
		};
		
		std::set<Token_count, TC_compare> _tcSet; // token count set
		std::ofstream _oFile; // output file
	};
	
	/**
	 Forwards swapping to the member function
	 that implements the operation most efficiently.
	 
	 @param left [IN/OUT] First Input_file_list. When done this will have the right values.
	 @param right [IN/OUT] Second Input_file_list. When done this will have the left values
	 */
	void swap(Output_sorting_file& left, Output_sorting_file& right ) noexcept;
	
}
#endif /* Output_sorting_file_hpp */
