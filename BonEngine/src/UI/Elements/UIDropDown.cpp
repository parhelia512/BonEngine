#include <UI/Elements/UIDropDown.h>
#include <UI/Elements/UIList.h>
#include <BonEngine.h>

using namespace bon::framework;
using namespace bon::gfx;

namespace bon
{
	namespace ui
	{
		// optional extra initialization code to apply after creating element.
		void _UIDropDown::_Init()
		{
			// init base list stuff
			_UIList::_Init();

			// set if opened
			_isOpened = false;
			
			// create selected text background
			UIElement tempPtrThatDoesntDelete = std::shared_ptr<_UIElement>(this, [](_UIElement*) {});
			SelectedTextBackground = bon::_GetEngine().UI().CreateImage(nullptr, tempPtrThatDoesntDelete);

			// create selected text element
			SelectedText = bon::_GetEngine().UI().CreateText(nullptr, SelectedTextBackground, "");
			SelectedText->WordWrap = false;

			// register callback to handle clicking on the selected text to show / hide list
			SelectedTextBackground->OnMousePressed = SelectedText->OnMousePressed = [this](bon::_UIElement& element, void* data)
			{
				this->ShowDropdownList(!this->_isOpened);
			};

			// by default hide list
			_isOpened = false;
		}

		// show / hide dropdown list
		void _UIDropDown::ShowDropdownList(bool show) 
		{
			// open
			_isOpened = show; 

			// update list position
			int selectedHeight = SelectedTextBackground->GetActualDestRect().Height;
			Background->_ExtraPixelsOffset.Y = selectedHeight;

			// update list items
			Background->MarkAsDirty();
			RebuildListItems();
			UpdateScrollbarMinMax();
			if (_scrollbar) { _scrollbar->Update(0.1); }

			// set if locked
			Locked = !_isOpened;
		}

		// initialize element style from config file.
		void _UIDropDown::LoadStyleFrom(const assets::ConfigAsset& config)
		{
			// call base init
			_UIList::LoadStyleFrom(config);

			// load text styles
			const char* textStylesheet = config->GetStr("selected_text", "text_style", nullptr);
			if (textStylesheet) { 
				SelectedText->LoadStyleFrom(bon::_GetEngine().Assets().LoadConfig(ToRelativePath(textStylesheet).c_str())); 
			}
			SelectedText->SetOffset(config->GetPointF("selected_text", "text_offset", framework::PointF::Zero));
			SelectedText->ExemptFromAutoArrange = true;
			framework::PointF anchor = config->GetPointF("selected_text", "text_anchor", framework::PointF(-1000.0f, -1000.0f));
			if (anchor.X != -1000.0f) { SelectedText->SetAnchor(anchor); }

			// load selected text background style
			const char* textBackgroundStylesheet = config->GetStr("selected_text", "background_style", nullptr);
			if (textBackgroundStylesheet) { 
				SelectedTextBackground->LoadStyleFrom(bon::_GetEngine().Assets().LoadConfig(ToRelativePath(textBackgroundStylesheet).c_str())); 
			}
		}

		// set if to draw as top layer this element and all its children, recursively.
		void _UIDropDown::SetDrawAsTopLayerRecursive(bool drawTopLayer)
		{
			_UIList::SetDrawAsTopLayerRecursive(drawTopLayer);
			SelectedTextBackground->SetDrawAsTopLayerRecursive(drawTopLayer);
		}

		// do self updates
		void _UIDropDown::UpdateSelf(double deltaTime)
		{
			// update selected text
			auto newSelected = SelectedItem();
			auto currentSelected = SelectedText->GetText();
			if ((newSelected && !currentSelected) || (!newSelected && currentSelected) || 
				(newSelected && (strcmp(SelectedText->GetText(), newSelected) != 0))) 
			{
				SelectedText->SetText(newSelected);
			}

			// update draw layer of self, but not background
			if (DrawAsTopLayer != _isOpened)
			{
				SetDrawAsTopLayerRecursive(_isOpened);
				SelectedTextBackground->SetDrawAsTopLayerRecursive(false);
			}

			// call base updates
			_UIList::UpdateSelf(deltaTime);
		}

		// draw ui element and children.
		void _UIDropDown::Draw(bool topLayer)
		{
			if (_isOpened) {
				_UIList::Draw(topLayer);
			}
			else {
				SelectedTextBackground->Draw(topLayer);
			}
		}
	}
}