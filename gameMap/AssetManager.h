#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

class AssetManager
{
public:
	AssetManager();

	static sf::Texture& GetTexture(std::string const& filename);
	static sf::Shader* GetShader(
		std::string const& vsFile,
		std::string const& fsFile);
	static sf::Font& GetFont(std::string const& filename);
	//static sf::SoundBuffer& GetSoundBuffer(std::string const& filename);

private:
	std::map<std::string, sf::Texture> m_Textures;
	std::map<std::string, std::unique_ptr<sf::Shader>> m_Shaders;
	std::map<std::string, sf::Font> m_Fonts;
	//std::map < std::string, sf::SoundBuffer > m_SoundBuffers; this line makes to program not run the exe
	//AssetManager is a singelton, so only one instance can exist at a time
	//sInstance holds a static pointer to the single manager instance
	static AssetManager* sInstance;
};

#endif

