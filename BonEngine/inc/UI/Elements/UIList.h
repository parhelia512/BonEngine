/*****************************************************************//**
 * \file   UIList.h
 * \brief  A UI list you can pick elements from.
 *
 * \author Ronen Ness
 * \date   June 2020
 *********************************************************************/
#pragma once
#include "UIWindow.h"
#include "UIText.h"
#include "UIImage.h"
#include "../../Assets/Types/Config.h"
#include <list>

namespace bon
{
	namespace ui
	{

#pragma warning ( push )
#pragma warning ( disable: 4251 ) // "..needs to have dll-interface to be used by clients..." it's ok in this case because its private.

		/**
		 * A UI list with background window and text items.
		 */
		class BON_DLLEXPORT _UIList : public _UIElement
		{
		private:

			// the struct that holds a single item in list.
			struct ListItem
			{
				UIText Text;
				UIImage Background;
			};

			// items in list
			std::list<ListItem> _items;

			// stylesheet for items in list
			assets::ConfigAsset _itemsSheet;

			// stylesheet for items background
			assets::ConfigAsset _itemsBackgroundSheet;

		public:

			/**
			 * List background window.
			 */
			UIWindow Background;

			/**
			 * Height, in pixels, of a single line in list.
			 */
			int LineHeight;

			/**
			 * Optional extra initialization code to apply after creating element.
			 */
			virtual void _Init() override;

			/**
			 * Initialize element style from config file.
			 *
			 * \param config Config file to init element from.
			 *				* In addition to all the settings from UIElement and UIImage stylesheet files, you can add the following:
			 *				*	[list]
			 *				*		- list_background_style = Stylesheet to use for list background window (UIWindow).
			 *				*		- item_background_style = Stylesheet to use for list item background image (UIImage).
			 *				*		- items_style = Stylesheet to use for text items in list.
			 *				*		- line_height = Height, in pixels, of a single line in list.
			 */
			virtual void LoadStyleFrom(const assets::ConfigAsset& config);

			/**
			 * Add item to list.
			 * 
			 * \param item Item text to add.
			 */
			void AddItem(const char* item);
			
			/**
			 * Remove item from list.
			 *
			 * \param item Item text to remove.
			 */
			void RemoveItem(const char* item);

			/**
			 * Clear list.
			 */
			void Clear();
		};
	}
}