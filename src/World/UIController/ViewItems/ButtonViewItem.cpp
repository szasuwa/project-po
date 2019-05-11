#include "ButtonViewItem.h"


ButtonViewItem::~ButtonViewItem()
{
	delete fOnClick;
	delete fOnMouseEnter;
	delete fOnMouseOver;
	delete fOnMouseExit;
}

void ButtonViewItem::update(GameEngineInterface& f)
{
	if (fOnMouseEnter == nullptr && fOnMouseOver == nullptr && fOnMouseExit == nullptr && fOnClick == nullptr)
		return;

	if (fText.getGlobalBounds().contains(f.getFrameInterface().getMousePosition(Frame::FrameLayer::Interface)))
	{
		if (!fIsMouseOver)
		{
			fIsMouseOver = true;
			if (fOnMouseEnter != nullptr)
			{
				(*fOnMouseEnter)();
			}
		}
		

		if (fOnMouseOver != nullptr)
		{
			(*fOnMouseOver)();
		}


		if (fOnClick != nullptr && f.getInputInterface().wasKeyToggled((unsigned int)KeyBindingIndex::LeftClick, true))
		{
			(*fOnClick)();
		}
	}
	else 
	{
		if (fIsMouseOver)
		{
			fIsMouseOver = false;
			if (fOnMouseExit != nullptr)
			{
				(*fOnMouseExit)();
			}
		}
	}
}

void ButtonViewItem::draw(GameEngineInterface& f) const
{
	if (fVisible)
	{
		f.getFrameInterface().draw(fText, Frame::FrameLayer::Interface);
	}
}

void ButtonViewItem::setOnClick(ViewAction* f, bool persistent)
{
	if(!persistent)
		delete fOnClick;
	fOnClick = f;
}

void ButtonViewItem::setOnMouseEnter(ViewAction* f, bool persistent)
{
	if (!persistent)
		delete fOnMouseEnter;
	fOnMouseEnter = f;
}

void ButtonViewItem::setOnMouseOver(ViewAction* f, bool persistent)
{
	if (!persistent)
		delete fOnMouseOver;
	fOnMouseOver = f;
}

void ButtonViewItem::setOnMouseExit(ViewAction* f, bool persistent)
{
	if (!persistent)
		delete fOnMouseExit;
	fOnMouseExit = f;
}