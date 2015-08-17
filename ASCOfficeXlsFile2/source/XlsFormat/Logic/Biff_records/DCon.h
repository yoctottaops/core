#pragma once

#include "BiffRecord.h"

namespace XLS
{


// Logical representation of DCon record in BIFF8
class DCon: public BiffRecord
{
	BIFF_RECORD_DEFINE_TYPE_INFO(DCon)
	BASE_OBJECT_DEFINE_CLASS_NAME(DCon)
public:
	DCon();
	~DCon();

	BaseObjectPtr clone();

	void writeFields(CFRecord& record);
	void readFields(CFRecord& record);

	static const ElementType	type = typeDCon;
//-----------------------------
//	BIFF_WORD userName;
	unsigned short iiftab;
	unsigned short fLeftCat;
	unsigned short fTopCat;
	unsigned short fLinkConsole;


public:
	//BO_ATTRIB_MARKUP_BEGIN
//		//BO_ATTRIB_MARKUP_ATTRIB(userName)
	//BO_ATTRIB_MARKUP_END

};

} // namespace XLS

