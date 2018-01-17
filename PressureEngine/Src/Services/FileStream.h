#pragma once
#include <string>
#include <memory>

namespace Pressure {

	class FileStream {

	public: 
		FileStream() = delete;

		static std::shared_ptr<std::string> read(const char* filename);
		static bool write(const char* filename, const char* content);

	};

}