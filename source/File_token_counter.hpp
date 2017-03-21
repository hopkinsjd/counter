/** @file File_token_counter.hpp
 *
 *	Created by John D. Hopkins on 3/14/17.
 */

#ifndef File_token_counter_hpp
#define File_token_counter_hpp

#include <fstream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include "String_utils.hpp"

namespace counterLib {
	
	using Token_count_map = std::unordered_map<std::string, int>;
	// Using an unordered (hash) map provides speed entry and lookup.

	/**
	 *	Encapsulates the opening, processing, and closing of a file
	 *	of UTF-8 text for tokenization and counting of their frequency.
	 */
	class File_token_counter {
	public:
		
		/**
		 *	Initializing Constructor
		 *
		 *	@param textFileName [IN] Filename (path) of a text file,
		 *	containing UTF-8 text to be tokenized and 
		 *	each token's frequency counted.
		 */
		File_token_counter (const std::string& textFileName);
		
		/**
		 *	Copy constructer (deleted)
		 *
		 *	Deleted because can't copy ifstreams (_tcFile).
		 *
		 */
		File_token_counter (const File_token_counter&) = delete;
		
		/**
		 *	Move constructor (works)
		 *
		 *	@param other [IN] rvalue of another Input_file_list.
		 */
		File_token_counter (File_token_counter&& other) noexcept;

		/**
		 *	Destructor
		 *
		 *	Closes the file opened by the initializing constructor.
		 */
		~File_token_counter();
		
		/**
		 Tokenizes the file of this object.
		 Adds the unique tokens and their frequency counts 
		 to the given Token_count_map.
		 Always starts at beginning of the open file of this object,
		 even when called again. 
		 
		 Tokenizing here is defined as separating the file into words
			(characters delimited by whitespace),
			stripping leading and trailing punctuation,
			and forcing the token to be lowercase.

		 @param tcm [IN] A Token_count_map for accumulating token counts.
		 */
		void add_to_map(Token_count_map& tcm);
		
		/**
		 Copy Assignment Operator (deleted)
		 
		 Deleted because copy assignment is also deleted on ifstreams.
		 */
		File_token_counter& operator= (const File_token_counter&) = delete;
		
		/**
		 Move Assignment Operator (works)
		 
		 @param other [IN] rvalue of another File_token_counter.
		 @return reference to an File_token_counter.
		 */
		File_token_counter& operator= (File_token_counter&& other) noexcept;

		/**
		 Member function that efficiently swaps the contents of this object.
		 'swap' is used by various STL containers.
		 So this member function is added in case an instance finds itself there.
		 
		 @param other [IN/OUT] Reference to another File_token_counter.
		 */
		void swap (File_token_counter& other) noexcept { _tcFile.swap(other._tcFile); }
		
	private:
		std::ifstream _tcFile; // stores the open file stream of this object
				
	};
	
	/**
	 Forwards swapping request to the member function
	 that implements the operation most efficiently.
	 
	 @param left [IN/OUT] First Input_file_list. When done this will have the right values.
	 @param right [IN/OUT] Second Input_file_list. When done this will have the left values
	 */
	void swap(File_token_counter & left, File_token_counter & right) noexcept;
	
}
#endif /* File_token_counter_hpp */
