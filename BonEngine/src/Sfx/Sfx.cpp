#include <Sfx/Sfx.h>
#include <Diagnostics/IDiagnostics.h>
#include <BonEngine.h>

namespace bon
{
	namespace sfx
	{
		// init sfx manager
		void Sfx::_Initialize()
		{
			_Implementor.Initialize();
		}

		// dispose sfx resources
		void Sfx::_Dispose()
		{
			_Implementor.Dispose();
		}

		// do updates
		void Sfx::_Update(double deltaTime)
		{
		}

		// called on main loop start
		void Sfx::_Start()
		{
			if (!_Implementor.IsInit()) {
				_Implementor.InitAudio();
			}
		}

		// set audio properties
		void Sfx::SetAudioProperties(int frequency, AudioFormats format, bool stereo, int audio_chunk_size)
		{
			_Implementor.SetAudioProperties(frequency, format, stereo ? 2 : 1, audio_chunk_size);
			if (_Implementor.IsInit()) {
				_Implementor.InitAudio();
			}
		}

		// start playing a music track
		void Sfx::PlayMusic(assets::MusicAsset music, int volume, int loops, float fadeInTime)
		{
			_Implementor.PlayMusic(music, loops, fadeInTime);
			SetMusicVolume(volume);
		}

		// pause / resume music
		void Sfx::PauseMusic(bool pause)
		{
			_Implementor.PauseMusic(pause);
		}

		// fade out channel
		void Sfx::FadeOutChannel(SoundChannelId channel, float fadeOutTime)
		{
			_Implementor.FadeOut(channel, fadeOutTime);
		}

		// fade out music
		void Sfx::FadeOutMusic(float fadeOutTime)
		{
			_Implementor.FadeOutMusic(fadeOutTime);
		}

		// set music volume
		void Sfx::SetMusicVolume(int volume)
		{
			_musicVolume = volume;
			int calcVol = max((int)((float)volume * _masterMusicVolume), 1);
			_Implementor.SetMusicVolume(calcVol);
		}

		// play a sound effect
		SoundChannelId Sfx::PlaySound(assets::SoundAsset sound, int volume, int loops, float pitch, float fadeInTime)
		{
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::PlaySoundCalls);
			volume = (int)((float)volume * _masterVolume);
			SoundChannelId ret = _Implementor.PlaySound(sound, volume, loops, pitch, fadeInTime);
			return ret != AllChannels ? ret : InvalidSoundChannel;
		}

		// play a sound effect
		SoundChannelId Sfx::PlaySound(assets::SoundAsset sound, int volume, int loops, float pitch, float panLeft, float panRight, float distance, float fadeInTime)
		{
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::PlaySoundCalls);
			volume = (int)((float)volume * _masterVolume);
			SoundChannelId ret = _Implementor.PlaySound(sound, volume, loops, pitch, fadeInTime);
			if (ret >= 0)
			{
				SetChannelPanning(ret, panLeft, panRight);
				SetChannelDistance(ret, distance);
			}
			return ret != AllChannels ? ret : InvalidSoundChannel;
		}

		// set channel panning
		void Sfx::SetChannelPanning(SoundChannelId channel, float panLeft, float panRight)
		{
			if (channel == InvalidSoundChannel) return;
			_Implementor.SetChannelPanning(channel, panLeft, panRight);
		}

		// set channel distance
		void Sfx::SetChannelDistance(SoundChannelId channel, float distance)
		{
			if (channel == InvalidSoundChannel) return;
			_Implementor.SetChannelDistance(channel, distance);
		}

		// stop a channel
		void Sfx::StopChannel(SoundChannelId channel)
		{
			_Implementor.StopChannel(channel);
		}

		// stop music
		void Sfx::StopMusic()
		{
			_Implementor.StopMusic();
		}

		// set channel's volume
		void Sfx::SetChannelVolume(SoundChannelId channel, int volume)
		{
			if (channel == InvalidSoundChannel) return;
			int calcVol = max((int)((float)volume * _masterVolume), 1);
			_Implementor.SetVolume(channel, calcVol);
		}

		// check if sound is playing
		bool Sfx::IsPlaying(assets::SoundAsset sound, SoundChannelId channel) const
		{
			if (channel == InvalidSoundChannel) return false;
			return _Implementor.IsPlaying(sound, channel);
		}

		// set master volumes
		void Sfx::SetMasterVolume(int soundEffectsVolume, int musicVolume)
		{
			_masterVolume = (float)soundEffectsVolume / 100.0f;
			_masterMusicVolume = (float)musicVolume / 100.0f;
			SetMusicVolume(_musicVolume);
		}
	}
}