#pragma once

#include "BiffStructure.h"
#include <Logic/Biff_structures/RRD.h>
#include <Logic/Biff_structures/BiffString.h>
#include <Logic/Biff_structures/BitMarkedStructs.h>

namespace XLS
{

class CFRecord;

class NoteRR : public BiffStructure
{
	BASE_STRUCTURE_DEFINE_CLASS_NAME(NoteRR)
public:
	NoteRR();
	NoteRR(CFRecord& record);
	BiffStructurePtr clone();

	static const ElementType	type = typeNoteRR;

	virtual void load(CFRecord& record);
	virtual void store(CFRecord& record);

	RRD rrd;
	bool bitfDelNote;
	bool bitfAddNote;
	RwU row;
	ColU col;
	bool fShow;
	bool fRwHidden;
	bool fColHidden;
	_GUID_ guid;
	unsigned int ichEnd;
	unsigned int cchNote;
	XLUnicodeString stAuthor;



};

} // namespace XLS

