#pragma once
#include "../CustomShape.h"

// 19
namespace NSCustomShapesConvert
{
class CArcType : public CCustomShape
{
public:
	CArcType()

    {
        m_bConcentricFill = true;
		m_eJoin = NSOfficeDrawing::lineJoinRound;
        m_strPath = _T("wr-21600,,21600,43200,,,21600,21600nfewr-21600,,21600,43200,,,21600,21600l,21600nsxe");

		AddGuide(_T("val #2"));
		AddGuide(_T("val #3"));
		AddGuide(_T("val #4"));

		m_arAdjustments.push_back(-5898240);
		m_arAdjustments.push_back(0);
		m_arAdjustments.push_back(0);
		m_arAdjustments.push_back(43200/*ShapeSizeVML*/);//43200??
		m_arAdjustments.push_back(43200/*ShapeSizeVML*/);//??43200

		LoadConnectorsList(_T("0,0;21600,21600;0,21600"));

		CHandle_ oHandle1;
		oHandle1.position = _T("@2,#0");
		oHandle1.polar = _T("@0,@1");
		m_arHandles.push_back(oHandle1);

		CHandle_ oHandle2;
		oHandle2.position = _T("@2,#1");
		oHandle2.polar = _T("@0,@1");
		m_arHandles.push_back(oHandle2);
    }
};
}