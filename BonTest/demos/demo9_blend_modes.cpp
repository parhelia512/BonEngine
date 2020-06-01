#include "../demos.h"
#include "../../BonEngine/inc/BonEngine.h"

namespace demo9_blend_modes
{
	/**
	 * Basic hello world scene.
	 */
	class BlendModesScene : public bon::engine::Scene
	{
	private:
		// default font
		bon::FontAsset _font;

		// cursor image
		bon::ImageAsset _cursorImage;

		// sprite and background
		bon::ImageAsset _spriteImage;
		bon::ImageAsset _backgroundImage;

		// show / hide background
		bool _showBackground = true;

	public:
		// on scene load
		virtual void _Load() override
		{
			if (IsFirstScene())
				Game().LoadConfig("../TestAssets/config.ini");
		}

		// on scene start
		virtual void _Start() override
		{
			// load assets
			_cursorImage = Assets().LoadImage("../TestAssets/gfx/cursor.png");
			_spriteImage = Assets().LoadImage("../TestAssets/gfx/gnu.png");
			_backgroundImage = Assets().LoadImage("../TestAssets/gfx/background.png");
			_font = Assets().LoadFont("../TestAssets/gfx/OpenSans-Regular.ttf");
		}

		// per-frame update
		virtual void _Update(double deltaTime) override
		{
			if (Input().Down("exit")) { Game().Exit(); }
			if (Input().ReleasedNow(bon::KeyCodes::KeySpace)) { _showBackground = !_showBackground; }
		}

		// drawing
		virtual void _Draw() override
		{
			// clear screen
			Gfx().ClearScreen(bon::Color(0.2f, 0.5f, 1.0f));

			// get window size
			bon::PointI windowSize = Gfx().WindowSize();

			// draw background
			if (_showBackground) {
				bon::PointF origin(0.5f, 1.0f);
				Gfx().DrawImage(_backgroundImage, bon::PointF((float)windowSize.X / 2.0f, (float)windowSize.Y), &bon::PointI(800, 600), bon::BlendModes::Opaque, nullptr, &origin, 0, nullptr);
			}

			// draw text
			Gfx().DrawText(_font, "Demo #9: Blend Modes", bon::PointF(100, 100));
			Gfx().DrawText(_font, "You can draw sprites with different blend modes.\n\
Left to right: Alpha Blend, Additive, Mod, Multiply, Opaque.\n\
Press space to toggle background.\
\nHit escape to exit.", bon::PointF(100, 200), &bon::Color(1, 1, 0, 1), 16);

			// draw test sprite
			bon::PointF origin(0.0f, 1.0f);
			Gfx().DrawImage(_spriteImage, bon::PointF(0.0f, (float)windowSize.Y), &bon::PointI(160, 160), bon::BlendModes::AlphaBlend, nullptr, &origin, 0, nullptr);
			Gfx().DrawImage(_spriteImage, bon::PointF(160.0f * 1, (float)windowSize.Y), &bon::PointI(160, 160), bon::BlendModes::Additive, nullptr, &origin, 0, nullptr);
			Gfx().DrawImage(_spriteImage, bon::PointF(160.0f * 2, (float)windowSize.Y), &bon::PointI(160, 160), bon::BlendModes::Mod, nullptr, &origin, 0, nullptr);
			Gfx().DrawImage(_spriteImage, bon::PointF(160.0f * 3, (float)windowSize.Y), &bon::PointI(160, 160), bon::BlendModes::Multiply, nullptr, &origin, 0, nullptr);
			Gfx().DrawImage(_spriteImage, bon::PointF(160.0f * 4, (float)windowSize.Y), &bon::PointI(160, 160), bon::BlendModes::Opaque, nullptr, &origin, 0, nullptr);

			// draw cursor
			Gfx().DrawImage(_cursorImage, Input().CursorPosition(), &bon::PointI(64, 64));
		}
	};

	/**
	 * Init demo.
	 */
	void main()
	{
		auto scene = BlendModesScene();
		bon::Start(scene);
	}

}