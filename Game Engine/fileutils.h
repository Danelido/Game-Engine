#pragma once
#include <string>


namespace Utils 
{

	struct FileUtils
	{
	
	public:
		static std::string read_file(const char* filepath)
		{
			FILE* file = fopen(filepath, "rt");		// r = read only and t = textfile
			fseek(file, 0, SEEK_END);				// Seek to the end to find out the length
			unsigned long length = ftell(file);		// Set length to the length of the file
			char* data = new char[length + 1];		// Data arrays to store all data + 1 extra slot for a termination char
			memset(data, 0, length + 1);			// To get rid of extra data (Important)
			fseek(file, 0, SEEK_SET);				// Set it back to the beginning 
			fread(data, 1, length, file);			// Read the file and store the data in "data" 
			fclose(file);							// Close it

			std::string result(data);				// Store the result to be able to return it
			delete[] data;							// Free the memory
			return result;							// Return the result
		}

	};

}