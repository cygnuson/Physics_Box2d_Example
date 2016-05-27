
#include "TextureManager.hpp"


/*!
* \brief Get the singleton instance
*
* get the singleton instance of the texture manager.
*
* \return the instance of the singleton
*/
TextureManager& TextureManager::GetInstance(){
	static TextureManager texMan;
	return texMan;
}
void TextureManager::PopTexture(const std::string& name) {
	for (unsigned int i = 0; i < loadedTextures.size(); i++) {
		if (loadedTextures[i].first == name) {
			loadedTextures.erase(loadedTextures.begin() + i);
		}
	}
	if (textureMap.count(name) > 0) {
		textureMap.erase(name);
	}
	else {
		throw std::runtime_error("Texture does not exists on the map.");
	}
}
/*!
* \brief
*
* Add a texture to the map.  Will only add if the name and path both do not exist
*
* \param[in] name the name of the texture to add
* \param[in] path the path of the texture to add.
*
* \return true if the texture was added.
*/
sf::Texture& TextureManager::PushTexture(const std::string& name, const std::string& path){
	if (!UniqueTextureCheck(name, path)){
		if (std::ifstream(path).good()){
			textureMap[name].loadFromFile(path);
			loadedTextures.push_back(make_pair(name, path));
			return textureMap[name];
		}
		else{
			throw std::runtime_error("TextureManager: File not found!");
		}
	}
	else{
		throw std::runtime_error("TextureManager: Tried to add a texture that already existed!");
	}
}
/*!
* \brief
*
* A strong check, if the name of the texture exists,
* OR if the path of the texture exists under a different name.
*
* \param[in] name the name of the texture to check
* \param[in] path the path of the teture.
*
* \return true if the texture exists
*/
bool TextureManager::UniqueTextureCheck(const std::string& name, const std::string& path){
	if (!std::ifstream(path).good()){
		return false;
	}
	for (const auto& elem : loadedTextures){
		if (elem.first == name || elem.second == path){
			return true;
		}
	}
	return false;
}
/*!
* \brief
*
* Check to see if a texture exists on the texturemap.
*
* \param[in] name A uniRef name that is the name of the texture to check for.
*
* \return true if the texture exists
*/
bool TextureManager::TextureExists(const std::string& name){
	return textureMap.count((name)) == 0 ? false : true;
}

sf::Texture& TextureManager::GetTexture(const std::string& name){
	if (TextureExists((name))){
		return textureMap[(name)];
	}
	else{
		throw std::runtime_error("TextureManager: Texture does not exists!");
	}
}