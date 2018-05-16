#ifndef BE_CORE_JSON_SERIALIZABLE_HPP
#define BE_CORE_JSON_SERIALIZABLE_HPP 1

#include "Core/Core.hpp"

/*!
 * \file JsonSerializable.hpp
 * \brief Classes gérant la sérialisation
 * \author jblondea
 */
namespace BeerEngine
{
	/*! \struct JsonLoader
	* \brief Structure utilisée lors de la désérialisation d'une scène ou d'un prefab afin de maintenir une liste de callbacks et d'ids dans le scope du fichier désérialisé.
	*/
	struct JsonLoader
	{
		std::map<int, JsonSerializable *> serializables;
		std::stack<std::function<void (void)>> serializationCallBacks;

		JsonSerializable *getSerializableByID(int id);
		void executeCallBacks();
	};

	/*! \class JsonSerializable
	* \brief Classe de base gérant la sérialisation et désérialisation des classes qui en héritent.
	*/
    class JsonSerializable
    {
	private:
		static int idCounter;

    public:
		int			_serializationID;

		JsonSerializable();
		JsonSerializable(int id);

		/*!
		*  \brief Serialisation sur place
		*  Sérialisation des champs de la classe, la fonction serialize du parent doit être appelée au début de la fonction
		*/
        virtual nlohmann::json	serialize();

		/*!
		*  \brief Désérialisation sur place
		*  Désérialisation des champs de la classe, la fonction deserialize du parent doit être appelée au début de la fonction
		*/
		virtual void deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader);

		/*!
		*  \brief Désérialisation avec retour d'une instance de la classe
		*/
        static void Deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader);

        static JsonSerializable &toSerializable(JsonSerializable & item);
        static JsonSerializable *toSerializable(JsonSerializable * item);

        template<typename T>
        std::vector<JsonSerializable *> toSerializables(std::vector<T *> items)
        {
            std::vector<JsonSerializable *> serializables;
            for (auto item: items)
            {
                serializables.push_back(item);
            }
            return serializables;
        }
    };
}

#endif