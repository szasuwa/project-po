#include "OverlayView.h"


void OverlayView::draw()
{
	if (!fVisible)
		return;

	InterfaceView::draw();
}

bool OverlayView::getVisibility() const
{
	return fVisible;
}

void OverlayView::setVisibility(const bool& v)
{
	fVisible = v;
}

void OverlayView::toggleVisibility()
{
	fVisible = !fVisible;
}
