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
		return std::string(Inst()->m_Properties[property]);
	}

	void Properties::set(const char* property, const char* value) {
		Inst()->m_Properties[property] = value;
	}

	Properties::Properties()
		: m_Properties() {
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
				m_Properties[line.substr(0, nPos)] = line.substr(nPos + 1);
			}
		}
		return (m_Properties.size());
	}

	bool Properties::createFileWithDefaults() {
		m_Properties = s_Defaults;

		std::string out;
		out += "# Pressure Engine Properties #\n";
		for (auto pair : s_Defaults) {
			out += pair.first + "=" + pair.second + "\n";
		}
		return FileStream::write("pressure.properties", out.c_str());
	}

	const std::unordered_map<std::string, std::string> Properties::s_Defaults = {
		{ "windowWidth", "1280" },
		{ "windowHeight", "720" },
		{ "windowTitle", "PressureEngine" },
		{ "windowFullscreen", "0" },
		{ "windowVsync", "0" },

		{ "fov", "70" },
		{ "hideConsole", "1" },

		{ "renderGrass", "1" },
		{ "useDepthOfField", "1" },

		{ "mouseLookSensitivity", "1.0" }

	};

}
