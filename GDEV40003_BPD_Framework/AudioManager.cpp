//#include "AudioManager.h"
//
//AudioManager::AudioManager(Mix_Chunk* chunk, const char* path, int channel, int loops, int volume)
//{
//	mixChunk = chunk;
//
//	//-1 sets it to the first available channel, otherwise it goes up to 8 channels
//	channel = -1;
//
//	this->LoadFromFile(path);
//	this->Play(channel, chunk, loops);
//	this->Pause(channel);
//	this->SetVolume(channel, volume);
//}
//
//AudioManager::~AudioManager()
//{
//	FreeChunk();
//
//	//stops all playing audio
//	Mix_CloseAudio();
//}
//
//bool AudioManager::LoadFromFile(const char* path)
//{
//	//removes the previous chunk from the memory
//	FreeChunk();
//
//	mixChunk = Mix_LoadWAV(path);
//	
//	if (mixChunk == nullptr)
//	{
//		std::cout << " Failed to load audio path for " << path << std::endl;
//		return false;
//	}
//
//	return true;
//}
//
//int AudioManager::Play(int channel, Mix_Chunk* chunk, int loops)
//{
//	//-1 for the loop variable means it indefinely loops
//	Mix_PlayChannel(channel, chunk, loops);
//
//	return channel;
//}
//
//void AudioManager::Pause(int channel)
//{
//	//1 for the channel variable pauses all sound channels
//	Mix_Pause(channel);
//}
//
//void AudioManager::SetVolume(int channel, int volume)
//{
//	//volume can be between 0-128
//	//if -1 is used for channels, it affects all channels
//	Mix_Volume(channel, volume);
//}
//
//void AudioManager::FreeChunk()
//{
//	if (mixChunk == nullptr)
//	{
//		Mix_FreeChunk(mixChunk);
//	}
//}
//
