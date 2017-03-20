//
//  Output_sorting_file.cpp
//  counter
//
//  Created by John D. Hopkins on 3/14/17.
//

#include "Output_sorting_file.hpp"

namespace counterLib {

	bool Output_sorting_file::TC_compare::operator() (const Token_count& a, const Token_count& b) {
		bool AIsGreaterThanB = false;
		if (a.second > b.second) {
			AIsGreaterThanB = true;
		}
		else if (a.second == b.second && a.first < b.first) {
			AIsGreaterThanB = true;
		}
		return AIsGreaterThanB;
	}

	Output_sorting_file::Output_sorting_file(const std::string outputFileName) {
		oFile.open(outputFileName);
		if (!oFile.is_open()) {
			throw std::invalid_argument {"Output_sorting_file_unable to open output file: " + outputFileName};
		}
	}
	
	Output_sorting_file::Output_sorting_file (Output_sorting_file&& other) noexcept {
		oFile = std::move(other.oFile);
		tcSet = std::move(other.tcSet);
	}

	Output_sorting_file::~Output_sorting_file() {
		oFile.close(); // not strictly necessary because ofstream closes itself when it goes out of scope, but makes things explicit if oFile implementation ever changed
	}

	void Output_sorting_file::set_sorted(Token_count_map& wcm) {
		for(auto i = wcm.begin(); i != wcm.end(); ++i) {
			tcSet.emplace(*i);
		}
	}

	void Output_sorting_file::write_to_output( std::ostream& out ) const {
		for (auto i : *this) {
			out << i.first << ", " << i.second << std::endl;
		}
	}

	void Output_sorting_file::write_to_file() {
		oFile.seekp(std::ios_base::beg);
		write_to_output(oFile);
	}
	
	void Output_sorting_file::swap (Output_sorting_file& other) noexcept {
		tcSet.swap(other.tcSet);
		oFile.swap(other.oFile);
	}
	
	void swap(Output_sorting_file& left, Output_sorting_file& right ) noexcept {
		left.swap(right);
	}

}
