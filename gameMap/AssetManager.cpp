#include "AssetManager.h"
#include <assert.h> //this macro checks whether an expression is true.  If it is, nothing happens. However if it's false, the macro calls abort(),
//which terminates the program.This check prevents more than one instance of the
//class to be created, which is exactly what we want.After we've made sure that this is
//the only instance, we will set the static pointer to the this instance.

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager()
{
	//Only allow one AssetManager to exist
	//Otherwise throw an exception
	assert(sInstance == nullptr);
	sInstance = this;

}

sf::Texture & AssetManager::GetTexture(std::string const & filename)
{
	auto& texMap = sInstance->m_Textures;

	//See if the texture is already loaded
	auto pairFound = texMap.find(filename);
	//If yes, return the texture
	if (pairFound != texMap.end())
	{
		return pairFound->second;
	}
	else //Else, load the texture and return
	{
		//Create an element in the texture map
		auto& texture = texMap[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}

sf::Shader * AssetManager::GetShader(std::string const & vsFile, std::string const & fsFile)
{
	auto& shaderMap = sInstance->m_Shaders;

	//See if the texture is already loaded
	auto combinedKey = vsFile + ";" + fsFile;
	auto pairFound = shaderMap.find(combinedKey);
	//If yes, return the texture
	if (pairFound != shaderMap.end())
	{
		return pairFound->second.get();
	}
	else //Else, load the texture and return
	{
		//Create an element in the texture map
		auto& shader = shaderMap[combinedKey] = std::unique_ptr<sf::Shader>(new sf::Shader());
		shader->loadFromFile(vsFile, fsFile);
		return shader.get();
	}
}

sf::Font & AssetManager::GetFont(std::string const & filename)
{
	auto& texMap = sInstance->m_Fonts;

	//See if the font is already loaded
	auto pairFound = texMap.find(filename);
	//If yes, return the font
	if (pairFound != texMap.end())
	{
		return pairFound->second;
	}
	else //Else, load the font and return
	{
		//Create an element in the font map
		auto& texture = texMap[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}

//sf::SoundBuffer & AssetManager::GetSoundBuffer(std::string const & filename)
//{
//	auto& sBufferMap = sInstance->m_SoundBuffers;
//
//	//See if the texture is already loaded
//	auto pairFound = sBufferMap.find(filename);
//	//If yes, return the texture
//	if (pairFound != sBufferMap.end())
//	{
//		return pairFound->second;
//	}
//	else //Else, load the texture and return
//	{
//		//Create an element in the texture map
//		auto& sBuffer = sBufferMap[filename];
//		sBuffer.loadFromFile(filename);
//		return sBuffer;
//	}
//}
