#include <_CAPI/CAPI_Managers_Assets.h>
#include <BonEngine.h>

/**
* Load and return an Image asset.
*/
bon::ImageAsset* BON_Assets_LoadImage(const char* filename, BON_ImageFilterMode filter, bool useCache)
{
	return new bon::ImageAsset(bon::_GetEngine().Assets().LoadImage(filename, (bon::ImageFilterMode)filter, useCache));
}

/**
* Creates and return an empty image asset.
*/
bon::ImageAsset* BON_Assets_CreateEmptyImage(int x, int y, BON_ImageFilterMode filter)
{
	return new bon::ImageAsset(bon::_GetEngine().Assets().CreateEmptyImage(bon::PointI(x, y), (bon::ImageFilterMode)filter));
}

/**
* Load and return a music asset.
*/
bon::MusicAsset* BON_Assets_LoadMusic(const char* filename, bool useCache)
{
	return new bon::MusicAsset(bon::_GetEngine().Assets().LoadMusic(filename, useCache));
}

/**
* Load and return a sound effect asset.
*/
bon::SoundAsset* BON_Assets_LoadSound(const char* filename, bool useCache)
{
	return new bon::SoundAsset(bon::_GetEngine().Assets().LoadSound(filename, useCache));
}

/**
* Load and return a font asset.
*/
bon::FontAsset* BON_Assets_LoadFont(const char* filename, int fontSize, bool useCache)
{
	return new bon::FontAsset(bon::_GetEngine().Assets().LoadFont(filename, fontSize, useCache));
}

/**
* Load and return a configuration asset.
*/
bon::ConfigAsset* BON_Assets_LoadConfig(const char* filename, bool useCache)
{
	return new bon::ConfigAsset(bon::_GetEngine().Assets().LoadConfig(filename, useCache));
}

/**
* Create and return an empty configuration file.
*/
bon::ConfigAsset* BON_Assets_CreateEmptyConfig()
{
	return new bon::ConfigAsset(bon::_GetEngine().Assets().CreateEmptyConfig());
}

/**
* Save configuration file.
*/
bool BON_Assets_SaveConfig(bon::ConfigAsset* config, const char* filename)
{
	return bon::_GetEngine().Assets().SaveConfig(*config, filename);
}

/**
* Clear all assets from cache.
*/
void BON_Assets_ClearCache()
{
	bon::_GetEngine().Assets().ClearCache();
}

/**
* Delete an asset pointer.
*/
void BON_Assets_FreeAssetPointer(bon::AssetPtr* asset)
{
	delete asset;
}