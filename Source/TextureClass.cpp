#include "../Headers/TextureClass.h"
#include "../Headers/Main.h"
#include "../Headers/Game.h"

TextureClass::TextureClass()
{
	
}

TextureClass::~TextureClass()
{
	// usuwamy kazda teksture

	for(auto textureData : apk_textures)
	{
		delete(textureData.second);
	}
}

Texture* TextureClass::Load(const string &texture, const string pathToTexture)
{
	// sprawdzamy czy tekstura juz jest w klasie
	Texture *result = TextureClass::CheckTexture(texture);

	//jesli istnieje to wczytujemy nowa na miejsce istniejacej
	if(result)
	{
		result->loadFromFile(pathToTexture);
	}
	//jesli nie isniala to tworzymy nowa
	else
	{
		result = new Texture();
		//wczyt. z pliku
		result->loadFromFile(pathToTexture);
		//i zapis do instancji
		Instance().apk_textures[texture] = result;
	}
	return result;
}

bool TextureClass::Unload(const string &texture)
{
	auto &instance = Instance();

	//szukamy tekstury w klasie, find zwraca itelator
	auto textureIt = instance.apk_textures.find(texture);

	//jezeli iterator od find == iterator od end to znaczy, ze nie znalazalo tekstury
	if(textureIt == instance.apk_textures.end())
	{
		return false;
	}
	else
	{
		//znaleziono teksture
		//usuwamy
		delete(textureIt->second);

		instance.apk_textures.erase(textureIt);

		return true;
	}
}

size_t TextureClass::CleanTextureUp()	
{
	auto &instance = Instance();

	size_t texturesInClass = instance.apk_textures.size();

	for(auto textureToClean : instance.apk_textures)
	{
		delete(textureToClean.second);
	}
	return texturesInClass;
}

Texture* TextureClass::CheckTexture(const string &texture)
{
	auto &instance = Instance();

	auto textureIt = instance.apk_textures.find(texture);

	if (textureIt == instance.apk_textures.end())
	{
		return nullptr;
	}

	return textureIt->second;
}