//
//  String_utils.cpp
//  counter
//
//  Created by John D. Hopkins on 3/17/17.
//

#include "String_utils.hpp"

namespace counterLib {
	
	std::string trim_punc (const std::string& aWord) {		// trim punctuation
		
		// get the position of the first alpha-numeric character
		auto i = aWord.begin();
		while(ispunct(*i) && i != aWord.end()) {
			++i;
		}
		
		if (i == aWord.end()) {
			return ""; // no alpha-numeric characters
		}
		
		// get position of last alpha-numeric character
		auto j = aWord.rbegin();
		while(ispunct(*j) && j != aWord.rend()) {
			++j;
		} // j will never == aWord.rend() actually at this point
		
		return std::string (i, j.base()); // make and return trimmed word
		
	}

	void make_lowercase (std::string& w) {
		// set all to lowercase for sure
		for (int k = 0; k < w.size(); ++k) {
			if (isupper(w[k])) {
				w[k] = tolower(w[k]);
			}
		}
	}

	std::string clean_word (const std::string& aWord) {
		std::string w = trim_punc(aWord);
		
		make_lowercase(w);
		
		return w;
	}

}
