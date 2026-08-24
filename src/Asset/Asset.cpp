#include "../Logger/Logger.h"
#include "Asset.h"
#include <fstream>
#include <sstream>

std::string ZY::Asset::getFileContent(const std::string& path)
{
	std::ifstream file{ path };
	if (!file.is_open())
	{
		LOG_ERROR("Error opening file {}", path);
	}

	std::ostringstream content;
	content << file.rdbuf();
	return content.str();
}
