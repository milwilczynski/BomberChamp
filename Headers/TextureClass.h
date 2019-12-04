#pragma once
#include "../Headers/Main.h"
#include <unordered_map>

class TextureClass final
{
public:
	typedef unordered_map<string, Texture *> TexturesUM;

	~TextureClass();

	TextureClass(const TextureClass &Other) = delete;

	void operator = (const TextureClass &Other) = delete;

	static Texture* Load(const string &texture, const string pathToTexture);

	static bool Unload(const std::string &texture);

	static size_t CleanTextureUp();

	static Texture* CheckTexture(const string &texture);

	inline static bool TextureExists(const string &texture)
	{
		return TextureClass::CheckTexture(texture) != nullptr;
	}

private:
	TextureClass();

	inline static TextureClass& Instance()
	{
		static TextureClass instance;
		return instance;
	}

	TexturesUM apk_textures; // tutaj przechowujemy tekstury UM - unordered_map
};


