#pragma once

#include "BiffRecord.h"

namespace XLS
{


// Logical representation of Qsi record in BIFF8
class Qsi: public BiffRecord
{
	BIFF_RECORD_DEFINE_TYPE_INFO(Qsi)
	BASE_OBJECT_DEFINE_CLASS_NAME(Qsi)
public:
	Qsi();
	~Qsi();

	BaseObjectPtr clone();

	void writeFields(CFRecord& record);
	void readFields(CFRecord& record);

	static const ElementType	type = typeQsi;

//-----------------------------
//	BIFF_WORD userName;
public:
	//BO_ATTRIB_MARKUP_BEGIN
//		//BO_ATTRIB_MARKUP_ATTRIB(userName)
	//BO_ATTRIB_MARKUP_END

};

} // namespace XLS

