#include <Gfx/Gfx.h>
#include <Framework/Point.h>
#include <BonEngine.h>
#include <Diagnostics/IDiagnostics.h>
#include <algorithm>


namespace bon
{
	namespace gfx
	{
		// init gfx manager
		void Gfx::_Initialize()
		{
			_Implementor.Initialize();
		}

		// dispose gfx resources
		void Gfx::_Dispose()
		{
		}

		// do updates
		void Gfx::_Update(double deltaTime)
		{
			// on update start, display previous frame
			_Implementor.UpdateWindow();

			// reset effect
			UseEffect(nullptr);
		}

		// called on main loop start
		void Gfx::_Start()
		{
			// if main loop started and user didn't set his own window, create a default one
			if (!_Implementor.HaveValidWindow())
			{
				SetWindowProperties("BonEngine Application", 800, 600, WindowModes::Windowed, true);
			}
		}

		// draw image
		void Gfx::DrawImage(const ImageAsset& sourceImage, const PointF& position, const PointI* size, BlendModes blend)
		{
			static PointI defaultSize(0, 0);
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
			_Implementor.DrawImage(sourceImage, position, size ? *size : defaultSize, blend);
		}

		/**
		 * Bring the main window forward and focus input on it.
		 */
		void Gfx::FocusWindow()
		{
			_Implementor.FocusWindow();
		}

		// draw image
		void Gfx::DrawImage(const ImageAsset& sourceImage, const PointF& position, const PointI* size, BlendModes blend, const framework::RectangleI* sourceRect, const PointF* origin, float rotation, const Color* color)
		{
			static PointI defaultSize(0, 0);
			static PointF defaultOrigin(0, 0);
			static Color defaultColor(1, 1, 1, 1);
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
			_Implementor.DrawImage(sourceImage, position, size ? *size : defaultSize, blend, sourceRect, origin ? *origin : defaultOrigin, rotation, color ? *color : defaultColor);
		}

		// draw sprite
		void Gfx::DrawSprite(const Sprite& sprite, const framework::PointF* offset)
		{
			if (offset) {
				framework::PointF position = sprite.Position + *offset;
				DrawImage(sprite.Image, position, &sprite.Size, sprite.Blend, &sprite.SourceRect, &sprite.Origin, sprite.Rotation, &sprite.Color);
			}
			else {
				DrawImage(sprite.Image, sprite.Position, &sprite.Size, sprite.Blend, &sprite.SourceRect, &sprite.Origin, sprite.Rotation, &sprite.Color);
			}
		}

		// currently set viewport
		framework::RectangleI _viewport = framework::RectangleI::Zero;

		// set viewport
		void Gfx::SetViewport(const framework::RectangleI* viewport)
		{
			_viewport = viewport ? *viewport : RectangleI::Zero;
			_Implementor.SetViewport(viewport);
		}

		// draw text
		void Gfx::DrawText(const FontAsset& font, const char* text, const framework::PointF& position, const Color* color, int fontSize, int maxWidth, BlendModes blend, const PointF* origin, float rotation, int outlineWidth, const Color* outlineColor)
		{
			static Color defaultColor(1, 1, 1, 1);
			static Color defaultOutlineColor(0, 0, 0, 1);
			static PointF defaultOrigin(0, 0);

			// draw text outline
			if (outlineWidth > 0)
			{
				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						if (i == 0 && j == 0) { continue; }
						_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
						_Implementor.DrawText(font, text, position + framework::PointF((float)i * outlineWidth, (float)j * outlineWidth),
							outlineColor ? *outlineColor : defaultOutlineColor, fontSize, blend, origin ? *origin : defaultOrigin, rotation, maxWidth, nullptr);
					}
				}
			}

			// draw text fill
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
			_Implementor.DrawText(font, text, position, color ? *color : defaultColor, fontSize, blend, origin ? *origin : defaultOrigin, rotation, maxWidth, nullptr);
		}

		// calculate and get text bounding box
		RectangleI Gfx::GetTextBoundingBox(const assets::FontAsset& font, const char* text, const framework::PointF& position, int fontSize, int maxWidth, const PointF* origin, float rotation)
		{
			static PointF defaultOrigin(0, 0);
			RectangleI ret;
			_Implementor.DrawText(font, text, position, Color::White, fontSize, BlendModes::AlphaBlend, origin ? *origin : defaultOrigin, rotation, maxWidth, &ret, true);
			return ret;
		}

		// draw line
		void Gfx::DrawLine(const framework::PointI& from, const framework::PointI& to, const framework::Color& color, BlendModes blendMode)
		{
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
			_Implementor.DrawLine(from, to, color, blendMode);
		}
		
		// draw pixel
		void Gfx::DrawPixel(const framework::PointI& position, const framework::Color& color, BlendModes blendMode)
		{
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
			_Implementor.DrawPixel(position, color, blendMode);
		}
		
		// draw rectangle
		void Gfx::DrawRectangle(const framework::RectangleI& rect, const framework::Color& color, bool filled, BlendModes blendMode, const PointF* origin, float rotation)
		{
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
			_Implementor.DrawRectangle(rect, color, filled, blendMode, origin ? *origin : PointF::Zero, rotation);
		}

		// draws a circle
		void Gfx::DrawCircle(const framework::PointI& center, int radius, const framework::Color& color, bool filled, BlendModes blendMode)
		{
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
			if (filled) {
				_Implementor.DrawCircleFill(center, radius, color, blendMode);
			}
			else {
				_Implementor.DrawCircleLines(center, radius, color, blendMode);
			}
		}

		// draw a 2d polygon
		void Gfx::DrawPolygon(const framework::PointI& a, const framework::PointI& b, const framework::PointI& c, const framework::Color& color, BlendModes blend)
		{
			_Implementor.DrawPolygon(a, b, c, color, blend);
		}

		// draw a 2d quad
		void Gfx::DrawQuad(const framework::PointI& a, const framework::PointI& b, const framework::PointI& c, const framework::PointI& d, const framework::Color& color, BlendModes blend)
		{
			_Implementor.DrawQuad(a, b, c, d, color, blend);
		}


		// create image asset from screen
		assets::ImageAsset Gfx::CreateImageFromScreen() const
		{
			_ImageHandle* handle = _Implementor.RenderScreenToImage();
			return _GetEngine().Assets()._CreateImageFromHandle(handle);
		}

		// get window size
		const PointI& Gfx::WindowSize() const
		{
			static PointI ret;
			ret.X = _Implementor.WindowWidth();
			ret.Y = _Implementor.WindowHeight();
			return ret;
		}

		void Gfx::SetTitle(const char* title)
		{
			_Implementor.SetTitle(title);
		}

		// currently set render target
		ImageAsset _renderTarget;

		// set render target
		void Gfx::SetRenderTarget(const ImageAsset& target)
		{
			// set render target
			_Implementor.SetRenderTarget(target);
			_renderTarget = target;
		}

		// get currently set render target
		const assets::ImageAsset& Gfx::GetRenderTarget() const
		{
			return _renderTarget;
		}

		// get renderable size
		framework::PointI Gfx::RenderableSize() const
		{
			// return size
			PointI ret;

			// set from render target
			if (_renderTarget != nullptr) 
			{
				ret.Set(_renderTarget->Width(), _renderTarget->Height());
			}

			// set from viewport
			if (!_viewport.Empty())
			{
				ret.X = ret.X == 0 ? _viewport.Width : std::min(ret.X, _viewport.Width);
				ret.Y = ret.Y == 0 ? _viewport.Height : std::min(ret.Y, _viewport.Height);
			}

			// set from window size
			PointI windowSize = WindowSize();
			ret.X = ret.X == 0 ? windowSize.X : std::min(ret.X, windowSize.X);
			ret.Y = ret.Y == 0 ? windowSize.Y : std::min(ret.Y, windowSize.Y);

			// return renderable size
			return ret;
		}

		// clear the entire screen or part of it
		void Gfx::ClearScreen(const Color& color, const RectangleI& clearRect)
		{
			_GetEngine().Diagnostics().IncreaseCounter(DiagnosticsCounters::DrawCalls);
			if (clearRect.Empty())
			{
				auto rs = RenderableSize();
				_Implementor.ClearScreen(color, RectangleI(0, 0, rs.X, rs.Y));
			}
			else
			{
				_Implementor.ClearScreen(color, clearRect);
			}
		}

		// set window properties
		void Gfx::SetWindowProperties(const char* title, int width, int height, WindowModes windowMode, bool showCursor)
		{
			_Implementor.CreateWindow(title, width, height, windowMode);
			_Implementor.ShowCursor(showCursor);
		}

		// set active effect
		void Gfx::UseEffect(assets::EffectAsset effect)
		{
			_Implementor.SetEffect(effect);
		}

		// get active effect
		assets::EffectAsset Gfx::GetActiveEffect() const
		{
			return _Implementor.GetActiveEffect();
		}
	}
}