#ifndef BE_CORE_IO_FILEUTILS_HPP
#define BE_CORE_IO_FILEUTILS_HPP 1
/*!
 * \file FileUtils.hpp
 * \brief Classe permettant le chargements et sauvegardes des fichiers
 * \author mgallo, mploux, jblondea
 */
#include <fstream>
#include <iterator>
#include "../Core.hpp"
/*! \namespace BeerEngine
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
	/*! \namespace IO
	* espace de nommage regroupant les fonctionnalité pour les fichiers
	*/
	namespace IO
	{
		/*! \class FileUtils
		* \brief classe regroupant les fonctionnalité de chargements et sauvegardes des fichiers
		*/
		class FileUtils
		{
		public:
			static std::string  LoadFile(std::string const &path);
			static void WriteFile(std::string const &path, std::string const &content);
			static std::string GetDirectory(std::string const &file);
		};
	}
}

#endif