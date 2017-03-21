//
//  File_token_counter.cpp
//  counter
//
//  Created by John D. Hopkins on 3/14/17.
//

#include "File_token_counter.hpp"

namespace counterLib {

	File_token_counter::File_token_counter (const std::string& textFileName) {
		_tcFile.open(textFileName);
		if (!_tcFile.is_open()) {
			throw std::invalid_argument {"File_token_counter unable to open listed file: " + textFileName + ". Make sure it exists in relationship to the program you are running."};
		}
		_tcFile.setf(std::ios_base::skipws); // make the file stream skip white space
	}
	
	File_token_counter::File_token_counter (File_token_counter&& other) noexcept {
		_tcFile = std::move(other._tcFile);
	}

	File_token_counter::~File_token_counter() {
		_tcFile.close();
		// Not strictly necessary because ifstream closes itself when it goes out of scope.
		// But makes things explicit if _tcFile implementation is ever changed.
	}

	void File_token_counter::add_to_map(Token_count_map& tcm) {
		// always start at beginning in case of multiple calls (tests)
		_tcFile.clear();
		_tcFile.seekg(0, _tcFile.beg);
		
		std::string aWord;
		while ( _tcFile >> aWord ) {
			std::string cleanWord = clean_word(aWord);
			if (cleanWord != "") {
				auto i = tcm.find(cleanWord);
				if (i == tcm.end()) {
					// doesn't exist, add for value of one
					tcm.emplace(cleanWord, 1);
				}
				else {
					i->second++;
				}
			}
		}
	}

	File_token_counter& File_token_counter::operator= (File_token_counter&& other) noexcept {
		_tcFile = std::move(other._tcFile);
		return *this;
	}
	
	void swap(File_token_counter & left, File_token_counter & right) noexcept {
		left.swap(right);
	}
		
}
