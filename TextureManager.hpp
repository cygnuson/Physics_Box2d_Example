#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP



#include <SFML/Graphics.hpp>

#include <map>
#include <memory>
#include <vector>
#include <string>
#include <fstream>


typedef std::pair<std::string, std::string> sspair;

/*!
* \class
*
* The TextureManger class keeps an arangment of textures.  It also prevent the same file from beign loaded twice by the developer.
*
* \author Matthew Eugene Swanson
* \date
*/
class TextureManager {

public:
	static TextureManager& GetInstance();

	sf::Texture& PushTexture(const std::string& name, const std::string& path);
	void PopTexture(const std::string& name);
	bool UniqueTextureCheck(const std::string& name, const std::string& path); //!<will return false if a tecture with the same name OR file exists.
	bool TextureExists(const std::string& name);
	sf::Texture& GetTexture(const std::string& name);
private:
	TextureManager() {}
	~TextureManager() {};
	TextureManager(const TextureManager&) = delete; //dont allow copying
	TextureManager(const TextureManager&&) = delete; //dont allow copying
	void operator=(const TextureManager&) = delete;//dont allow assignment.
	void operator=(const TextureManager&&) = delete;//dont allow assignment.
	std::vector<sspair> loadedTextures; //!<a list of textures that are already loaded.  cannot load the same file as a texture twice.
	std::map<std::string, sf::Texture> textureMap; //!<map of uniqe pointed textures.
};




#endif //TEXTUREMANAGER_HPP
