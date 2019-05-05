#include "ButtonViewItem.h"


ButtonViewItem::~ButtonViewItem()
{
	delete fOnClick;
	delete fOnMouseEnter;
	delete fOnMouseOver;
	delete fOnMouseExit;
}

void ButtonViewItem::update(UIInterface& f)
{
	if (fOnMouseEnter == nullptr && fOnMouseOver == nullptr && fOnMouseExit == nullptr && fOnClick == nullptr)
		return;

	if (fText.getGlobalBounds().contains(f.getFrame().getMousePosition(Frame::FrameLayer::Interface)))
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


		if (fOnClick != nullptr && f.getInput().wasKeyToggled((unsigned int)KeyBindingIndex::LeftClick, true))
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

void ButtonViewItem::draw(UIInterface& f) const
{
	if (fVisible)
	{
		f.getFrame().draw(fText, Frame::FrameLayer::Interface);
	}
}

void ButtonViewItem::setOnClick(ViewAction* f)
{
	delete fOnClick;
	fOnClick = f;
}

void ButtonViewItem::setOnMouseEnter(ViewAction* f)
{
	delete fOnMouseEnter;
	fOnMouseEnter = f;
}

void ButtonViewItem::setOnMouseOver(ViewAction* f)
{
	delete fOnMouseOver;
	fOnMouseOver = f;
}

void ButtonViewItem::setOnMouseExit(ViewAction* f)
{
	delete fOnMouseExit;
	fOnMouseExit = f;
}