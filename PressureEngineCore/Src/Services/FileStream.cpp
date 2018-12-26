#include "FileStream.h"

#include <fstream>
#include <streambuf>

namespace Pressure {

	std::shared_ptr<std::string> FileStream::read(const char* filename) {
		std::ifstream file(filename);
		auto string = std::make_shared<std::string>();

		if (!file.is_open())
			return string;

		file.seekg(0, std::ios::end);
		string->reserve(file.tellg());
		file.seekg(0, std::ios::beg);

		string->assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		file.close();

		return string;
	}

	bool FileStream::write(const char* filename, const char* content) {
		std::ofstream file(filename);
		
		if (!file.is_open())
			return false;

		file.clear();
		file << content;
		file.close();
		return true;
	}

}