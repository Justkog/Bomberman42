#include "Core/IO/FileUtils.hpp"

namespace BeerEngine
{
	namespace IO
	{
		std::string  FileUtils::LoadFile(std::string const &path)
		{
			std::string result = "";
			std::cout << "[CONFIG] " << path << "\n";
			std::ifstream ifs(path);
			if (ifs.is_open())
			{
				result = std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
				ifs.close();
			}
			else
			{
				std::cerr << "Failed to load: " << path << "\n";
			}
			return result;
		}

		std::string FileUtils::GetDirectory(std::string const &file)
		{
			std::string result;

			std::size_t lastSlashIndex = file.rfind('/');
			if (std::string::npos != lastSlashIndex)
				result = file.substr(0, lastSlashIndex);
			return result;
		}

		void  FileUtils::WriteFile(std::string const &path, std::string const &content)
		{
			std::ofstream myfile(path);
			if (myfile.is_open())
			{
				myfile << content;
				myfile.close();
			}
		}
	}
}