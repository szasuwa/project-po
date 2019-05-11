#pragma once
#include <vector>
#include <cstdarg>

#include "ViewAction.h"


class GroupViewAction : public ViewAction {
	std::vector<ViewAction*> fActions;

public:
	explicit GroupViewAction(int count...) {
		va_list args;
		va_start(args, count);

		for (int i = 0; i < count; ++i)
		{
			fActions.push_back(va_arg(args, ViewAction*));
		}

		va_end(args);
	};

	virtual ~GroupViewAction() {
		for (int i = 0; i < fActions.size(); ++i)
		{
			delete fActions[i];
		}
	}

	virtual void operator() () { 
		for (ViewAction* action : fActions)
		{
			(*action)();
		}
	};
};