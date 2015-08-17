
#include "PIVOTSELECT.h"
#include <Logic/Biff_records/SxSelect.h>
#include <Logic/Biff_unions/PIVOTRULE.h>

namespace XLS
{


PIVOTSELECT::PIVOTSELECT()
{
}


PIVOTSELECT::~PIVOTSELECT()
{
}


BaseObjectPtr PIVOTSELECT::clone()
{
	return BaseObjectPtr(new PIVOTSELECT(*this));
}


// PIVOTSELECT = SxSelect PIVOTRULE
const bool PIVOTSELECT::loadContent(BinProcessor& proc)
{
	if(!proc.mandatory<SxSelect>())
	{
		return false;
	}
	proc.mandatory<PIVOTRULE>();

	return true;
}

} // namespace XLS

