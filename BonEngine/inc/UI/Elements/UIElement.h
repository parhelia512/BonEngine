/*****************************************************************//**
 * \file   UIElement.h
 * \brief  Define a basic UI element class.
 *
 * \author Ronen Ness
 * \date   June 2020
 *********************************************************************/
#pragma once
#include "Defs.h"
#include "../../dllimport.h"
#include "../../Framework/Point.h"
#include "../../Assets/Types/Config.h"
#include "../../Framework/Rectangle.h"
#include "../../Framework/Color.h"
#include "../../Assets/Types/Config.h"
#include "../../Assets/Defs.h"
#include <list>


#pragma warning ( push )
#pragma warning ( disable: 4251 ) // "..needs to have dll-interface to be used by clients..." it's ok in this case because its private.

namespace bon
{
	namespace ui
	{
		/**
		 * Base UI element class.
		 */
		class BON_DLLEXPORT UIElement
		{
		private:
			// element position.
			UICoords _position;

			// element size.
			UICoords _size;

			// child elements.
			std::list<UIElementPtr> _children;

			// internal padding
			UISides _padding;

			// parent ui element.
			UIElement* _parent = nullptr;

			// element calculated dest rect (based on position and size)
			framework::RectangleI _destRect;

			// do we need to recalculate dest rect?
			bool _isDestDirty = true;

			// every time we recalculate dest rect this increases by 1.
			unsigned long _destCalcId = 0;

			// last known parent dest id. if changes, we need to update ourselves as well
			unsigned long _parentLastDestCalcId = (unsigned long)-1;

		public:

			/**
			 * Initialize element style from config file.
			 * 
			 * \param config Config file to init element from.
			 *				* config must contain the following section:
			 *				*	[style]
			 *				*		- width = Element width value.
			 *				*		- width_type = Width coordinate types (pixels / parent_percent).
			 *				*		- height = Element height value.
			 *				*		- height_type = Height coordinate types (pixels / parent_percent). 
			 *				*		- color = Element color, with values ranging from 0 to 255 (r,g,b,a).
			 *				*		- padding_left = Element padding left.
			 *				*		- padding_right = Element padding right.
			 *				*		- padding_top = Element padding top.
			 *				*		- padding_bottom = Element padding bottom.
			 */
			virtual void InitStyle(const assets::ConfigAsset& config);

			/**
			 * Element drawing color.
			 */
			framework::Color Color;

			/**
			 * Mark dest rect as dirty.
			 */
			inline void MarkAsDirty() { _isDestDirty = true; }

			/**
			 * Set element position.
			 */
			inline void SetPosition(UICoords position) { _position = position; MarkAsDirty(); }
			
			/**
			 * Get element position.
			 */
			inline const UICoords& GetPosition() const { return _position; }

			/**
			 * Set element size.
			 */
			inline void SetSize(UICoords size) { _size = size; MarkAsDirty(); }

			/**
			 * Get element size.
			 */
			inline const UICoords& GetSize() const { return _size; }

			/**
			 * Set internal padding.
			 */
			inline void SetPadding(UISides padding) { _padding = padding; MarkAsDirty(); }

			/**
			 * Get internal padding.
			 */
			inline const UISides& GetPadding() const { return _padding; }

			/**
			 * Get parent element.
			 * 
			 * \return Parent element, or null.
			 */
			inline const UIElement* Parent() const { return _parent; }

			/**
			 * Add child element.
			 * 
			 * \param child Element to add.
			 */
			void AddChild(UIElementPtr child);

			/**
			 * Remove child element.
			 * 
			 * \param child Element to remove.
			 */
			void RemoveChild(UIElementPtr child);

			/**
			 * Remove self from parent.
			 */
			void Remove();

			/**
			 * Draw ui element and children.
			 */
			virtual void Draw();

			/**
			 * Update the UI element and children.
			 * 
			 * \param deltaTime Update frame delta time.
			 */
			virtual void Update(double deltaTime);

		protected:

			/**
			 * Recalculate destination rect.
			 */
			void CalcDestRect();

			/**
			 * Calculate and return coords based on parent, return absolute value in pixels.
			 */
			framework::PointI CalcCoords(const UICoords& coords, const framework::RectangleI& region, bool addRegionPosition);

			/**
			 * Get the last dest rect we calculated.
			 * Note: may be outdated if actions were done without calling CalcDestRect() or Update(). 
			 * Sometimes you need to Update() parent too.
			 */
			inline const framework::RectangleI& GetCalculatedDestRect() const { return _destRect; }

			/**
			 * Implement just the drawing of this element
			 */
			virtual void DrawSelf();

			/**
			 * Implement just the updating of this element
			 *
			 * \param deltaTime Update frame delta time.
			 */
			virtual void UpdateSelf(double deltaTime);
		};
	}
}

#pragma warning (pop)