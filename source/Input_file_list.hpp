/**	@file Input_file_list.hpp
 *
 *	Created by John D. Hopkins on 3/14/17.
 */

#ifndef Input_file_list_hpp
#define Input_file_list_hpp

#include <fstream>
#include <string>
#include <stdexcept>
#include <list>

namespace counterLib {
	
	using Filename_list_const_iter = std::list<std::string>::const_iterator;

	/**
	 *	The class encapsulates an input file and its contents. 
	 *	The input file should contain a list of file names, one name (path) per line.
	 *	Because the file stream data member of this class is not copyable, 
	 *	neither is this class.
	 *	The file given to the constructor, if successfully opened,
	 *	will remain open for the lifetime of the instance.
	 *	The destructor will close it.
	 */
	class Input_file_list {
	public:
		/**
		 *	Initializing Constructor
		 *
		 *	@param inputFileName [IN] Filename (path) of a text file,
		 *		containing a list of filenames, one filename per line.
		 *		Each file listed should contain UTF-8 text, 
		 *		with word/tokens of which you may count 
		 *		using the File_token_counter class.
		 *		The constructor will try to open the file and 
		 *		read the contained file names,
		 *		putting them into the instance's fileNameList.
		 *		The filenames in the list are not checked for their validity here,
		 *		but will be when you use the File_token_counter class to open them.
		 *		You can access them with this object's cbegin and cend const iterators.
		 */
		Input_file_list (const std::string& inputFileName);
		
		/**
		 *	Copy constructer (deleted)
		 *
		 *	Deleted because can't copy ifstreams (iFile).
		 *
		 */
		Input_file_list (const Input_file_list&) = delete;
		
		/**
		 *	Move constructor (works)
		 *
		 *	@param other [IN] rvalue of another Input_file_list.
		 */
		Input_file_list (Input_file_list&& other) noexcept;
		
		/**
		 Destructor
		 
		 Closes the file opened by the initializing constructor.
		 */
		~Input_file_list();
		
		/**
		 * @return Gets the number of file names found in the file name list.
		 * This should correspond with the number of lines in the input file
		 * supplied to the initializing constructor.
		 */
		unsigned long file_count() const noexcept {
			return fileNameList.size();
		}
		
		
		/**
		 Gets the beginning iteratator of the filename list of strings,
		 extracted from the input file fed to the initializing constructor.
		 Works with a range for loop.

		 @return The beginning iterator of the filename string list as a const_iterator
		 to avoid violation of encapsulation.
		 */
		Filename_list_const_iter begin() const noexcept {
			return fileNameList.begin();
		}
		
		/**
		 Equivalent explicit const_iterator version of begin().

		 @return The beginning const_iterator of the filename string list.
		 */
		Filename_list_const_iter cbegin() const noexcept {
			return fileNameList.cbegin();
		}
		
		/**
		 Gets the ending iterator of the filename list of strings.
		 Works with a range for loop.

		 @return The ending iterator of the filename string list as a const_iterator
		 to match above begin(). 
		 */
		Filename_list_const_iter end() const noexcept {
			return fileNameList.end();
		}
		
		/**
		 Equivalent explicit const_iterator version of end().
		 
		 @return The ending const_iterator of the filename string list.
		 */
		Filename_list_const_iter cend() const noexcept {
			return fileNameList.cend();
		}
		
		/**
		 Copy Assignment Operator (deleted)
		 
		 Deleted because copy assignment is also deleted on ifstreams.

		 */
		Input_file_list& operator= (const Input_file_list&) = delete;
		
		/**
		 Move Assignment Operator (works)

		 @param x [IN] rvalue of another Input_file_list.
		 @return reference to an Input_file_list.
		 */
		Input_file_list& operator= (Input_file_list&& x) noexcept;
		
		/**
		 Member function that efficiently swaps the contents of this object.	
		 'swap' is used by various STL containers.
		 So this member function is added in case an instance finds itself there.

		 @param other [IN/OUT] Reference to another Input_file_list.
		 */
		void swap (Input_file_list& other) noexcept;
		
	private:
		std::ifstream iFile; // Stores the open input file stream.
		std::list<std::string> fileNameList; /** Stores each line of the input file as an item. Features fast entry of many unknown lines of text. */
	};

	/**
	 Forwards swapping to the member function
	 that implements the operation most efficiently.

	 @param left [IN/OUT] First Input_file_list. When done this will have the right values.
	 @param right [IN/OUT] Second Input_file_list. When done this will have the left values
	 */
	void swap(Input_file_list & left, Input_file_list & right) noexcept;

}
#endif /* Input_file_list_hpp */
