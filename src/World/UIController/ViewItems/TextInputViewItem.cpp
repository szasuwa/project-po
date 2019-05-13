#include "TextInputViewItem.h"


TextInputViewItem::~TextInputViewItem()
{
	delete fOnEnterPressed;
	if (fTextWatcherHandler != nullptr)
		fTextWatcherHandler->removeTextWatcher(this);
}

void TextInputViewItem::update(GameEngineInterface& f)
{
	fElapsedTime += f.getFrameInterface().getFrameTime();
	
	if (fElapsedTime > 1)
	{
		int s1 = fTextContent.size();
		int s2 = fText.getString().getSize();

		std::string temp;
		if (s1 == 0)
			temp = fPlaceholder;
		else
			temp = fTextContent;

		if (s1 == s2 || (s1 == 0 && s2 == fPlaceholder.size()))
			temp += fInputSign;

		fText.setString(temp);
	}

	while (fElapsedTime > 1)
	{
		--fElapsedTime;
	}

	if (f.getInputInterface().wasKeyToggled((unsigned int)KeyBindingIndex::LeftClick, true))
	{
		if (fText.getGlobalBounds().contains(f.getFrameInterface().getMousePosition(Frame::FrameLayer::Interface)))
		{
			if (!fIsSelected) {
				fIsSelected = true;
				fTextWatcherHandler = &f.getInputInterface();
				fTextWatcherHandler->addTextWatcher(this);
			}
		}
		else if (fIsSelected) 
		{
			fIsSelected = false;
			fTextWatcherHandler->removeTextWatcher(this);
			fTextWatcherHandler = nullptr;
		}
	}
}

void TextInputViewItem::draw(GameEngineInterface& f) const
{
	if (fVisible)
	{
		f.getFrameInterface().draw(fText, Frame::FrameLayer::Interface);
	}
}

void TextInputViewItem::setText(const std::string& txt)
{
	fTextContent = txt;
	TextViewItem::setText(txt);
}

void TextInputViewItem::setOnEnterPressed(ViewAction* f, bool persistent)
{
	if(!persistent)
		delete fOnEnterPressed;
	fOnEnterPressed = f;
}

void TextInputViewItem::onTextInput(sf::Event::TextEvent text)
{
	fElapsedTime = 0;
	fText.setString(fTextContent);

	if (text.unicode == 0x08)
	{
		fText.removeLastCharacters();
	} 
	else if (text.unicode == 0x0D && fOnEnterPressed != nullptr)
	{
		(*fOnEnterPressed)();
	}
	else 
	{
		fText.append(sf::String(text.unicode).toAnsiString());
	}

	fTextContent = fText.getString();
	if (fTextContent.empty())
		fText.setString(fPlaceholder);
}