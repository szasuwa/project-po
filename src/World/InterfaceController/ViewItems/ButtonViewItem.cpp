#include "ButtonViewItem.h"


#include "../../../Logger.h"
void ButtonViewItem::draw() const
{
	if (fVisible)
	{
		Frame::getInstance().draw(fText, Frame::FrameLayer::Interface);
		//if (fText.getGlobalBounds().contains(Frame::getInstance().getMousePosition(Frame::FrameLayer::Interface)) && MouseController::getInstance().wasLmbToggledDown())
		//{
		//	LogInfo(fText.getString());
		//}
	}
}

