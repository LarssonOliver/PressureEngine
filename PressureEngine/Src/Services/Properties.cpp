#include "Properties.h"

#include <sstream>
#include "FileStream.h"
#include "../Math/Math.h"

namespace Pressure {

	Properties* Properties::m_Inst = nullptr;

	Properties* Properties::Inst() {
		if (!m_Inst)
			m_Inst = new Properties();
		return m_Inst;
	}

	Properties::~Properties() {
		m_Inst = nullptr;
	}

	std::string Properties::get(const char* property) {
		return std::string(properties[property]);
	}

	void Properties::set(const char* property, const char* value) {
		properties[property] = value;
	}

	Properties::Properties()
	: properties() {
		if (!loadFromFile())
			createFileWithDefaults();
	}

	bool Properties::loadFromFile() {
		std::istringstream file(*FileStream::read("pressure.properties"));
		std::string line;

		while (std::getline(file, line)) {
			if (line[0] == '#')
				continue;
			
			int nPos;
			if ((nPos = line.find("=")) != line.npos) {
				properties[line.substr(0, nPos)] = line.substr(nPos + 1);				
			}
		}
		return (properties.size());
	}

	bool Properties::createFileWithDefaults() {
		properties = defaults;
		
		std::string out;
		out += "# Pressure Engine Properties #\n";
		for (auto pair : defaults) {
			out += pair.first + "=" + pair.second + "\n";
		}
		return FileStream::write("pressure.properties", out.c_str());
	}

	const std::unordered_map<std::string, std::string> Properties::defaults = {
		{"s", "s"},
		{"f", "f"}
	};

}
