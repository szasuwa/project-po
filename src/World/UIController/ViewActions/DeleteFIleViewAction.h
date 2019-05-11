#pragma once
#include "../ViewItems/TextViewItem.h"


class DeleteFileViewAction : public ViewAction {
	std::string fFile;

public:
	explicit DeleteFileViewAction(std::string& f) : fFile(f) {};
	virtual void operator() () { 
		remove(fFile.c_str()); 
	};
};