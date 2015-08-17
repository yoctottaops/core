#pragma once

#include <Logic/Biff_records/BiffRecord.h>
#include <Logic/Biff_structures/BiffString.h>


namespace XLS
{

class List12DisplayName: public BiffStructure
{	
	BASE_STRUCTURE_DEFINE_CLASS_NAME(List12DisplayName)
public:
	BiffStructurePtr clone();

	List12DisplayName();
	~List12DisplayName();

	static const ElementType	type = typeList12DisplayName;
	
	virtual void load(CFRecord& record);
	virtual void store(CFRecord& record);

	XLNameUnicodeString stListName;
	XLUnicodeString stListComment;
};

typedef boost::shared_ptr<List12DisplayName> List12DisplayNamePtr;

} // namespace XLS