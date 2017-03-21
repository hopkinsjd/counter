//
//  Input_file_list.cpp
//  counter
//
//  Created by John D. Hopkins on 3/14/17.
//

#include "Input_file_list.hpp"

namespace counterLib {

	Input_file_list::Input_file_list (const std::string& inputFileName) {
		_iFile.open(inputFileName);
		if (!_iFile.is_open()) {
			throw std::invalid_argument {"Input_file_list unable to open the input file: " + inputFileName + ". Make sure it exists in relationship to the program you are running."};
		}
		std::string line;
		while ( getline(_iFile, line) ) {
			_fileNameList.emplace_back(line);
		}
	}

	Input_file_list::Input_file_list (Input_file_list&& other) noexcept {
		_iFile = std::move(other._iFile);
		_fileNameList = std::move(other._fileNameList);
	}

	Input_file_list::~Input_file_list() {
		_iFile.close();
		// Not strictly necessary because ifstream closes itself when it goes out of scope.
		// But makes things explicit if _iFile implementation is ever changed.
	}

	Input_file_list& Input_file_list::operator= (Input_file_list&& x) noexcept {
		_iFile = std::move(x._iFile);
		_fileNameList = std::move(x._fileNameList);
		return *this;
	}

	void Input_file_list::swap (Input_file_list& other) noexcept {
		_iFile.swap(other._iFile);
		_fileNameList.swap(other._fileNameList);
	}
	
	void swap(Input_file_list & left,
			  Input_file_list & right) noexcept {
		left.swap(right);
	}

}
