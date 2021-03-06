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
#include "UIVerticalScrollbar.h"
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
		protected:

			// the struct that holds a single item in list.
			struct ListItem
			{
				int Index = 0;
				UIText Text = nullptr;
				UIImage Background = nullptr;
			};

			// items in list
			std::list<ListItem> _items;

			// list scrollbar
			UIVerticalScrollbar _scrollbar;

			// stylesheet for items in list
			assets::ConfigAsset _itemsSheet;

			// stylesheet for items background
			assets::ConfigAsset _itemsBackgroundSheet;

			// mark that list is dirty and we need to rearrange items in it
			bool _listDirty = true;

			// height, in pixels, of a single line in list.
			int _lineHeight = 24;

			// how many visible items can be visible at any given time (based on line height and list height).
			int _maxVisibleEntitiesInList = 0;

			// currently selected index
			int _selected = -1;

			// an internal container for list items
			UIElement _itemsContainer;

		public:

			/**
			 * Get element type.
			 */
			virtual UIElementType GetType() const override { return UIElementType::List; }

			/**
			 * List background window.
			 */
			UIWindow Background;

			/**
			 * If true, will ignore list selection from user (you can still select item via code though).
			 */
			bool Locked;

			/**
			 * Set the height, in pixels, of an item in list.
			 * 
			 * \param val Line height to set.
			 */
			inline void SetLineHeight(int val) { _lineHeight = val; _listDirty = true; }

			/**
			 * Get the height, in pixels, of an item in list.
			 */
			inline int GetLineHeight() const { return _lineHeight; }

			/**
			 * Optional extra initialization code to apply after creating element.
			 */
			virtual void _Init() override;

			/**
			 * Get list items list.
			 */
			std::vector<std::string> Items() const;

			/**
			 * Set if to draw as top layer this element and all its children, recursively.
			 */
			virtual void SetDrawAsTopLayerRecursive(bool drawTopLayer) override;

			/**
			 * Get if list contains a given value.
			 */
			bool Contains(const char* value) const;

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
			 *				*		- vscrollbar_style = Stylesheet for list vertical scrollbar (UIVerticalScrollbar).
			 */
			virtual void LoadStyleFrom(const assets::ConfigAsset& config) override;

			/**
			 * Show / hide scrollbar.
			 * Note: only work if scrollbar stylesheet is defined, otherwise no scrollbar is created.
			 * 
			 * \param show Show / hide scrollbar.
			 */
			inline void ShowScrollbar(bool show) { if (_scrollbar) { _scrollbar->Visible = show; } }

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
			 * \param removeAll If true, will remove all items matching the value. If false, will remove only first occurance found.
			 */
			void RemoveItem(const char* item, bool removeAll);

			/**
			 * Remove item from list.
			 *
			 * \param index Item index to remove.
			 */
			void RemoveItem(int index);

			/**
			 * Clear list.
			 */
			void Clear();

			/**
			 * Update the UI element and children.
			 *
			 * \param deltaTime Update frame delta time.
			 */
			virtual void Update(double deltaTime) override;

			/**
			 * Get currently selected index.
			 * 
			 * \return Selected index, or -1 if no item is selected.
			 */
			inline int SelectedIndex() const { return _selected; }

			/**
			 * Get currently selected item text.
			 * 
			 * \return Selected item text, or nullptr if no item is selected.
			 */
			const char* SelectedItem() const;

			/**
			 * Selet list item by index.
			 * 
			 * \param index Index to select, or -1 to clear selection.
			 */
			virtual void Select(int index);

			/**
			 * Selet list item by value (if duplications exist, will select first item found.
			 *
			 * \param item Item value to select, or nullptr to clear selection.
			 */
			virtual void Select(const char* item);

			/**
			 * Clear currently selected index.
			 */
			inline void ClearSelection() { Select(-1); }

			/**
			 * Draw ui element and children.
			 */
			virtual void Draw(bool topLayer) override;

		protected:

			/**
			 * Update list items.
			 */
			void RebuildListItems();
			
			/**
			 * Update scrollbar min, max and offset.
			 */
			void UpdateScrollbarMinMax();
		};
	}
}