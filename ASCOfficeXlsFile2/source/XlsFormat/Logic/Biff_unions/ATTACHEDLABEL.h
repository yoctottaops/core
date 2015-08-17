#pragma once

#include <Logic/CompositeObject.h>

namespace XLS
{


// Logical representation of ATTACHEDLABEL union of records 
class ATTACHEDLABEL: public CompositeObject
{
	BASE_OBJECT_DEFINE_CLASS_NAME(ATTACHEDLABEL)
public:
	ATTACHEDLABEL();
	~ATTACHEDLABEL();

	BaseObjectPtr clone();

	virtual const bool loadContent(BinProcessor& proc);

};

} // namespace XLS

