/*****************************************************************//**
 * \file   Engine.h
 * \brief  Define the main class that manage the game main loop.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"
#include "../Assets/IAssets.h"
#include "../Gfx/IGfx.h"
#include "../Sfx/ISfx.h"
#include "../Game/IGame.h"
#include "../Input/IInput.h"
#include "../Log/ILog.h"
#include "../Framework/Exceptions.h"
#include <vector>
#pragma warning ( push )
#pragma warning ( disable: 4251 ) // "..needs to have dll-interface to be used by clients..." it's ok in this case because its private.


namespace bon
{
	namespace engine
	{
		/**
		 * Different states the engine can be in.
		 */
		enum class DLLEXPORT EngineStates
		{
			// Engine was not initialized yet.
			BeforeInitialize,

			// engine is initializing now.
			Initialize,

			// engine is doing managers updates.
			InternalUpdate,

			// engine is doing fixed updates.
			FixedUpdate,

			// engine is doing regular updates.
			Update,

			// engine is drawing.
			DrawImage,

			// engine is doing other main-loop code that isn't updates or drawing.
			MainLoopInBetweens,

			// engine is handling events
			HandleEvents,
			
			// engine is stopping
			Stopping,

			// engine is completely stopped and destroyed
			Destroyed,
		
			// engine is currently switching scenes (not set on first scene set).
			SwitchScene,
		};

		/**
		 * The main class that runs the BonEngine engine.
		 * This is the class that gets instanciated and fire up the game main loop.
		 */
		class DLLEXPORT Engine
		{
		private:
			// is the engine currently running?
			bool _isRunning = false;

			// active managers - you can replace them before Start() is called.
			assets::IAssets* _assetsManager = nullptr;
			gfx::IGfx* _gfxManager = nullptr;
			sfx::ISfx* _sfxManager = nullptr;
			game::IGame* _gameManager = nullptr;
			input::IInput* _inputManager = nullptr;
			log::ILog* _logManager = nullptr;

			// list of all manager instances
			std::vector<IManager*> _managers;
			std::vector<IManager*> _customManagers;

			// engine state
			EngineStates _state = EngineStates::BeforeInitialize;

			// currently active scene
			Scene* _activeScene = nullptr;
			Scene* _previousScene = nullptr;
			Scene* _nextScene = nullptr;

			// mark if engine is being destroyed
			bool _destroyed = false;

			// mark if the main loop have started during this run. note: this doesn't mean that engine wasn't already closed.
			bool _mainLoopStarted = false;

			// count update frames
			unsigned long long _updatesCount = 0;
			
			// count fixed update frames
			unsigned long long _fixedUpdatesCount = 0;

			// total elapsed time since application started
			double _elapsedTime = 0.0;

		public:

			/**
			 * Fixed updates inverval, in seconds.
			 */
			double FixedUpdatesInterval = 30.0 / 1000.0;

			/**
			 * Start running the engine.
			 * 
			 * \param scene Active scene to set on start.
			 */
			void Start(Scene& startingScene);

			/**
			 * Stop running the engine.
			 * This will end the application.
			 */
			void Stop();

			/**
			 * Set the currently active scene.
			 * Note: will actually change the scene after current frame ends.
			 * 
			 * \param scene Active scene to set.
			 */
			void SetScene(Scene& scene);

			/**
			 * Set the currently active assets manager.
			 * Note: the pointer you set must not be deleted until the end of the program, unless you replace it manually.
			 * 
			 * \param assets New assets manager.
			 */
			inline void SetAssetsManager(assets::IAssets* assets) { AssertIfRunning(); _assetsManager = assets; }

			/**
			 * Get assets manager instance.
			 * 
			 * \return Assets manager.
			 */
			inline assets::IAssets& Assets() { return *_assetsManager; }

			/**
			 * Set the currently active gfx manager.
			 * Note: the pointer you set must not be deleted until the end of the program, unless you replace it manually.
			 *
			 * \param gfx New gfx manager.
			 */
			inline void SetGfxManager(gfx::IGfx* gfx) { AssertIfRunning(); _gfxManager = gfx; }

			/**
			 * Get gfx manager instance.
			 *
			 * \return Gfx manager.
			 */
			inline gfx::IGfx& Gfx() { return *_gfxManager; }

			/**
			 * Set the currently active sfx manager.
			 * Note: the pointer you set must not be deleted until the end of the program, unless you replace it manually.
			 *
			 * \param gfx New sfx manager.
			 */
			inline void SetSfxManager(sfx::ISfx* sfx) { AssertIfRunning(); _sfxManager = sfx; }

			/**
			 * Get sfx manager instance.
			 *
			 * \return Sfx manager.
			 */
			inline sfx::ISfx& Sfx() { return *_sfxManager; }

			/**
			 * Set the currently active game manager.
			 * Note: the pointer you set must not be deleted until the end of the program, unless you replace it manually.
			 *
			 * \param game New game manager.
			 */
			inline void SetGameManager(game::IGame* game) { AssertIfRunning(); _gameManager = game; }

			/**
			 * Get game manager instance.
			 *
			 * \return Game manager.
			 */
			inline game::IGame& Game() { return *_gameManager; }

			/**
			 * Set the currently active input manager.
			 * Note: the pointer you set must not be deleted until the end of the program, unless you replace it manually.
			 *
			 * \param game New input manager.
			 */
			inline void SetInputManager(input::IInput* input) { AssertIfRunning(); _inputManager = input; }

			/**
			 * Get input manager instance.
			 *
			 * \return Input manager.
			 */
			inline input::IInput& Input() { return *_inputManager; }

			/**
			 * Set the currently active log manager.
			 * Note: the pointer you set must not be deleted until the end of the program, unless you replace it manually.
			 *
			 * \param game New log manager.
			 */
			inline void SetLogManager(log::ILog* game) { AssertIfRunning(); _logManager = game; }

			/**
			 * Get log manager instance.
			 *
			 * \return log manager.
			 */
			inline log::ILog& Log() { return *_logManager; }

			/**
			 * Register a custom manager class.
			 * 
			 * \param manager Manager to add.
			 */
			void RegisterCustomManager(IManager* manager);

			/**
			 * Get if the engine is currently running.
			 * 
			 * \return If engine is running.
			 */
			inline bool Running() const { return _isRunning; }

			/**
			 * Get if the engine started the disposing sequence.
			 * Thins may behave unexpectedly during this time.
			 *
			 * \return If engine is destroyed / being destroyed.
			 */
			inline bool Destroyed() const { return _destroyed; }

			/**
			 * Get manager by id.
			 * This method is slower so it is recommended to cache the manager after getting it.
			 * For built-in managers, use the specific getters.
			 * 
			 * \param id Manager id to get.
			 * \return Manager instance.
			 */
			IManager* GetManagerById(const char* id);

			/**
			 * Get how many update calls we had since main loop started.
			 * 
			 * \return Updates count.
			 */
			inline unsigned long long UpdatesCount() const { return _updatesCount; }

			/**
			 * Get how many fixed update calls we had since main loop started.
			 *
			 * \return Updates count.
			 */
			inline unsigned long long FixedUpdatesCount() const { return _fixedUpdatesCount; }

			/**
			 * Return engine's current state.
			 * 
			 * \return Engine's state.
			 */
			inline EngineStates CurrentState() const { return _state; }

			/**
			 * Get the previously loaded scene.
			 * Note: scene may already be deleted at this point.
			 * 
			 * \return Previous scene, or nullptr if called from first scene loaded.
			 */
			inline Scene* PreviousScene() const { return _previousScene; }

		private:

			/**
			 * Throw exception if engine is running.
			 */
			inline void AssertIfRunning() const {
				if (_isRunning) {
					throw framework::InvalidState("Cannot perform this action after engine had started!");
				}
			}

			/**
			 * Throw exception if engine is NOT running.
			 */
			inline void AssertIfNotRunning() const {
				if (!_isRunning) {
					throw framework::InvalidState("Cannot perform this action before engine had started!");
				}
			}

			/**
			 * Do the actual scene switch, from _activeScene to _nextScene.
			 */
			void DoSceneSwitch();

			/**
			 * Start the engine's main loop.
			 */
			void StartMainLoop();

			/**
			 * Cleanup resources after main loop ends.
			 */
			void CleanUp();
		};
	}
}

#pragma warning (pop)