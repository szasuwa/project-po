#include "UIController.h"


UIController::UIController()
{
	init();
}

UIController::~UIController()
{
	destroyAllUIViews();
}

void UIController::init()
{
	for (int i = 0; i < (unsigned int)InterfaceType::num_values; ++i)
		fUIViews.push_back(nullptr);
}

void UIController::updateView()
{
	FrameInterface & frame = fEngine->getFrameInterface();
	sf::View view(sf::FloatRect(0,0, frame.getFrameWidth(), frame.getFrameHeight()));
	frame.updateView(view, FrameInterface::FrameLayer::Interface);
}

void UIController::update()
{
	for (UIViewInterface* item : fUIViews)
	{
		if (item != nullptr && item->getVisibility()) 
		{
			item->update(*fEngine);
		}
	}
}

void UIController::draw() const 
{
	for (UIViewInterface* item : fUIViews)
	{
		if (item != nullptr)
		{
			item->draw(*fEngine);
		}
	}
}

void UIController::addUIView(const unsigned int & i)
{
	if (i >= (unsigned int)InterfaceType::num_values)
		return;

	switch ((InterfaceType)i)
	{
		case InterfaceType::MainMenu:
			delete fUIViews[i];
			fUIViews[i] = new MainMenu(*fEngine);
			break;

		case InterfaceType::MapSelection:
			delete fUIViews[i];
			fUIViews[i] = new MapSelection();
			break;

		case InterfaceType::Gui:
			delete fUIViews[i];
			fUIViews[i] = new GraphicalUserInterface();
			break;

		case InterfaceType::MapEditor:
			delete fUIViews[i];
			fUIViews[i] = new MapEditorInterface();
			break;

		case InterfaceType::Debug:
			delete fUIViews[i];
			fUIViews[i] = new DebugInterface();
			break;

		case InterfaceType::EndGame:
			delete fUIViews[i];
			fUIViews[i] = new EndGameInterface(*fEngine);
			break;

		default:
			break;
	}
}

unsigned int UIController::addUIView(UIViewInterface* i) 
{
	fUIViews.push_back(i);
	return fUIViews.size();
}

void UIController::removeUIView(const unsigned int& i) 
{
	if (i >= fUIViews.size())
		return;

	fUIViews.erase(fUIViews.begin() + i);
}

void UIController::removeAllUIViews() 
{
	fUIViews.clear();
}

unsigned int UIController::removeAllUIViewsBut(const unsigned int& i)
{
	if (i >= fUIViews.size())
		return i;

	UIViewInterface* temp = fUIViews[i];
	fUIViews.clear();
	init();

	if (i < fUIViews.size())
	{
		fUIViews[i] = temp;
		return i;
	}
	else
	{
		fUIViews.push_back(temp);
		return fUIViews.size();
	}
}

void UIController::destroyUIView(const unsigned int& i) 
{
	if (i >= fUIViews.size())
		return;

	delete fUIViews[i];
	removeUIView(i);
}

void UIController::destroyAllUIViews() 
{
	for (size_t i = 0; i < fUIViews.size(); ++i)
	{
		if (fUIViews[i] != nullptr)
		{
			delete fUIViews[i];
			fUIViews[i] = nullptr;
		}
	}
	removeAllUIViews();
}

unsigned int UIController::destroyAllUIViewsBut(const unsigned int& i)
{
	if (i >= fUIViews.size())
		return i;

	for (size_t j = 0; i < fUIViews.size(); ++j)
	{
		if (j != i && fUIViews[j] != nullptr)
		{
			delete fUIViews[j];
			fUIViews[j] = nullptr;
		}
	}

	return removeAllUIViewsBut(i);
}

UIViewInterface * UIController::getUIView(const unsigned int& i)
{
	if (i >= fUIViews.size())
		return nullptr;
	
	return fUIViews[i];
}

void UIController::setViewVisibility(const unsigned int& i, const bool& v)
{
	if (i >= fUIViews.size())
		return;

	if (fUIViews[i] == nullptr)
		addUIView(i);

	if (fUIViews[i] != nullptr)
		fUIViews[i]->setVisibility(v);
}

void UIController::toggleViewVisibility(const unsigned int& i)
{
	if (i >= fUIViews.size())
			return;

	if (fUIViews[i] == nullptr)
		addUIView(i);
	else
		fUIViews[i]->setVisibility(!fUIViews[i]->getVisibility());
}

bool UIController::isViewVisible(const unsigned int& i)
{
	if (i >= fUIViews.size() || fUIViews[i] == nullptr)
		return false;

	return fUIViews[i]->getVisibility();
}

void UIController::broadcastVisibilityChange(const bool& v)
{
	for (UIViewInterface* item : fUIViews)
	{
		if (item != nullptr)
		{
			item->setVisibility(v);
		}
	}
}

std::string UIController::getProperty(const unsigned int& view, const unsigned int& id)
{
	if (view >= fUIViews.size() || fUIViews[view] == nullptr)
		throw std::out_of_range("View does not exist (Size: " + std::to_string(fUIViews.size()) + " , requested: " + std::to_string(view) + ")");

	return fUIViews[view]->getProperty(id);
}

void UIController::setProperty(const unsigned int& view, const unsigned int& id, const std::string& v)
{
	if (view >= fUIViews.size() || fUIViews[view] == nullptr)
		throw std::out_of_range("View does not exist (Size: " + std::to_string(fUIViews.size()) + " , requested: " + std::to_string(view) + ")");

	fUIViews[view]->setProperty(id, v);
}

