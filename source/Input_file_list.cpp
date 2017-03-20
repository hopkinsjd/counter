//
//  Input_file_list.cpp
//  counter
//
//  Created by John D. Hopkins on 3/14/17.
//

#include "Input_file_list.hpp"

namespace counterLib {

	Input_file_list::Input_file_list (const std::string& inputFileName) {
		iFile.open(inputFileName);
		if (!iFile.is_open()) {
			throw std::invalid_argument {"Input_file_list unable to open the input file: " + inputFileName + ". Make sure it exists in relationship to the program you are running."};
		}
		std::string line;
		while ( getline(iFile, line) ) {
			fileNameList.emplace_back(line);
		}
	}

	Input_file_list::Input_file_list (Input_file_list&& other) noexcept {
		iFile = std::move(other.iFile);
		fileNameList = std::move(other.fileNameList);
	}

	Input_file_list::~Input_file_list() {
		iFile.close(); // not strictly necessary because ifstream closes itself when it goes out of scope, but makes things explicit if iFile implementation ever changed
	}

	Input_file_list& Input_file_list::operator= (Input_file_list&& x) noexcept {
		iFile = std::move(x.iFile);
		fileNameList = std::move(x.fileNameList);
		return *this;
	}

	void Input_file_list::swap (Input_file_list& other) noexcept {
		iFile.swap(other.iFile);
		fileNameList.swap(other.fileNameList);
	}
	
	void swap(Input_file_list & left,
			  Input_file_list & right) noexcept {
		left.swap(right);
	}

}
