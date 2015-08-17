
#include "AddinUdf.h"
#include <Binary/CFRecord.h>

namespace XLS
{


BiffStructurePtr AddinUdf::clone()
{
	return BiffStructurePtr(new AddinUdf(*this));
}



void AddinUdf::store(CFRecord& record)
{
	record.reserveNunBytes(4); // reserved
	record << udfName;
	unsigned short cb = 0;
	record << cb;
	record.reserveNunBytes(cb); // unused
}


void AddinUdf::load(CFRecord& record)
{
	record.skipNunBytes(4); // reserved
	record >> udfName;
	record.getGlobalWorkbookInfo()->AddinUdfs.push_back(udfName);

	unsigned short cb;
	record >> cb;
	record.skipNunBytes(cb); // unused
}


} // namespace XLS

