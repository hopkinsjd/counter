/**
 *	@file String_utils.hpp
 *
 *  Created by John D. Hopkins on 3/17/17.
 */

#ifndef String_utils_hpp
#define String_utils_hpp

#include <string>

namespace counterLib {
	
	/**
	 Trims punctuation from both ends of the given word string.
	 
	 @param aWord [IN] A string containing a word, no whitespace, that may have punctuation on either or both ends.
	 @return A new string with any punctuation trimmed from the end. (Moved, not copied.)
	 */
	std::string trim_punc (const std::string& aWord);
	
	/**
	 Ensures that the given word string is all lowercase.
	 
	 @param aWord [IN/OUT] A word string that may have upper case characters.
	 */
	void make_lowercase (std::string& aWord);
	
	/**
	 Trims off punctuation from both ends of the given string <aWord>
	 and ensures that any alphabetic characters are set to lowercase.
	 
	 @param aWord [IN] A string representing a word (token).
	 There should be no whitespace in the string.
	 @return A new cleaned word (trimmed and set to lowercase).
	 Note that the string is moved, not copied, in C++11.
	 */
	std::string clean_word (const std::string& aWord);

}

#endif /* String_utils_hpp */
