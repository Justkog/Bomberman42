#include "Core/IO/FileUtils.hpp"

namespace BeerEngine
{
	namespace IO
	{
		std::string  FileUtils::LoadFile(std::string const &path)
		{
			std::cout << "Loading: " << path << "\n";
			std::ifstream ifs(path);
			return std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
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