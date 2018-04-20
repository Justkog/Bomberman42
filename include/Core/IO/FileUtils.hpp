#ifndef BE_CORE_IO_FILEUTILS_HPP
#define BE_CORE_IO_FILEUTILS_HPP 1

#include <fstream>
#include <iterator>
#include "../Core.hpp"

namespace BeerEngine
{
	namespace IO
	{
		class FileUtils
		{
		public:
			static std::string  LoadFile(std::string const &path);
			static void WriteFile(std::string const &path, std::string const &content);

		};
	}
}

#endif