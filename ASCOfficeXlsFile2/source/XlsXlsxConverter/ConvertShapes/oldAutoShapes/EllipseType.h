#pragma once
#include "../CustomShape.h"

// 3
namespace NSCustomShapesConvert
{
class CEllipseType : public CCustomShape
{
public:
	CEllipseType()

    {
        m_bConcentricFill = true;
		m_eJoin = NSOfficeDrawing::lineJoinMiter;
        m_strPath = _T("m,10800qy10800,,21600,10800,10800,21600,,10800xe");
		LoadTextRect(_T("3233,3233,18367,18367"));
    }
};
}