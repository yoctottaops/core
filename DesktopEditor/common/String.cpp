﻿/*
 * (c) Copyright Ascensio System SIA 2010-2018
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at Lubanas st. 125a-25, Riga, Latvia,
 * EU, LV-1021.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */
#include "CPEncodings/CodePage.h"
#include "String.h"

namespace NSStringExt
{
#define NSSTRING_COMMON_CP(UnicodeMapCP, lCount, pData) \
	for (long i = 0; i < lCount; ++i)\
	{\
		unsigned char unChar = (unsigned char)pData[i];\
		if (unChar < MSCP_FIRST_CHAR || unChar > MSCP_LAST_CHAR)\
			pUnicode[i] = (wchar_t)unChar;\
		else\
			pUnicode[i] = (wchar_t)(UnicodeMapCP[unChar - MSCP_FIRST_CHAR]);\
	}
// end define

    void NSSTRING_WITHLEADBYTE_CP(wchar_t** ppUnicode, unsigned short LEAD_CHAR, const unsigned short* UnicodeMapCP, const TCodePagePair* UnicodeMapWithLeadByte, long lCount, const unsigned char* pData)
	{
		int nLeadByte = -1;
		int nUnicodePos = 0;
		for (long i = 0; i < lCount; ++i)
		{
			unsigned char  unCode = (unsigned char)pData[i];
			unsigned short ushUnicode = UnicodeMapCP[unCode];
			if (-1 == nLeadByte)
			{
				if (LEAD_CHAR != ushUnicode)
				{
					(*ppUnicode)[nUnicodePos++] = ushUnicode;
					nLeadByte = -1;
				}
				else
				{
					nLeadByte = unCode;
				}
			}
			else
			{
				unsigned short ushCode = (nLeadByte << 8) | unCode;
				TCodePagePair *pPair = (TCodePagePair*)UnicodeMapWithLeadByte;
				while (0xFFFF != pPair->ushCode)
				{
					if (ushCode == pPair->ushCode)
					{
						(*ppUnicode)[nUnicodePos++] = pPair->ushUnicode;
						break;
					}
					pPair++;
				}
				nLeadByte = -1;
			}
		}
		(*ppUnicode)[nUnicodePos++] = 0x0000;
	}

    std::wstring CConverter::GetUnicodeFromSingleByteString(const unsigned char* pData, long lCount, ESingleByteEncoding eType)
    {
        wchar_t* pUnicode = new wchar_t[lCount + 1];
        if (!pUnicode)
            return std::wstring(L"");

        switch (eType)
        {
            default:
            case SINGLE_BYTE_ENCODING_DEFAULT:
            {
                for (long i = 0; i < lCount; ++i)
                    pUnicode[i] = (wchar_t)(unsigned char)pData[i];

                break;
            }
            case SINGLE_BYTE_ENCODING_SYMBOL:
            {
                // Добавляем 0xF000 к кодам всех символов
                for (long i = 0; i < lCount; ++i)
                {
                    pUnicode[i] = (wchar_t)(0xF000 | (unsigned char)pData[i]);
                }

                break;
            }
            case SINGLE_BYTE_ENCODING_CP866: NSSTRING_COMMON_CP(NSStringExt::c_anUnicodeMapCP866, lCount, pData); break;
            case SINGLE_BYTE_ENCODING_CP874: NSSTRING_COMMON_CP(NSStringExt::c_anUnicodeMapCP874, lCount, pData); break;
            case SINGLE_BYTE_ENCODING_CP1250: NSSTRING_COMMON_CP(NSStringExt::c_anUnicodeMapCP1250, lCount, pData); break;
            case SINGLE_BYTE_ENCODING_CP1251: NSSTRING_COMMON_CP(NSStringExt::c_anUnicodeMapCP1251, lCount, pData); break;
            case SINGLE_BYTE_ENCODING_CP1252: NSSTRING_COMMON_CP(NSStringExt::c_anUnicodeMapCP1252, lCount, pData); break;
            case SINGLE_BYTE_ENCODING_CP1253: NSSTRING_COMMON_CP(NSStringExt::c_anUnicodeMapCP1253, lCount, pData); break;
            case SINGLE_BYTE_ENCODING_CP1254: NSSTRING_COMMON_CP(NSStringExt::c_anUnicodeMapCP1254, lCount, pData); break;
            case SINGLE_BYTE_ENCODING_CP1255: NSSTRING_COMMON_CP(NSStringExt::c_anUnicodeMapCP1255, lCount, pData); break;
            case SINGLE_BYTE_ENCODING_CP1256: NSSTRING_COMMON_CP(NSStringExt::c_anUnicodeMapCP1256, lCount, pData); break;
            case SINGLE_BYTE_ENCODING_CP1257: NSSTRING_COMMON_CP(NSStringExt::c_anUnicodeMapCP1257, lCount, pData); break;
            case SINGLE_BYTE_ENCODING_CP1258: NSSTRING_COMMON_CP(NSStringExt::c_anUnicodeMapCP1258, lCount, pData); break;
            case SINGLE_BYTE_ENCODING_CP932: NSSTRING_WITHLEADBYTE_CP(&pUnicode, MSCP932_LEAD_CHAR, NSStringExt::c_anUnicodeMapCP932, c_aoUnicodeMapCP932WithLeadByte, lCount, pData); break;
            case SINGLE_BYTE_ENCODING_CP936: NSSTRING_WITHLEADBYTE_CP(&pUnicode, MSCP936_LEAD_CHAR, NSStringExt::c_anUnicodeMapCP936, NSStringExt::c_aoUnicodeMapCP936WithLeadByte, lCount, pData); break;
            case SINGLE_BYTE_ENCODING_CP949: NSSTRING_WITHLEADBYTE_CP(&pUnicode, MSCP949_LEAD_CHAR, NSStringExt::c_anUnicodeMapCP949, NSStringExt::c_aoUnicodeMapCP949WithLeadByte, lCount, pData); break;
            case SINGLE_BYTE_ENCODING_CP950: NSSTRING_WITHLEADBYTE_CP(&pUnicode, MSCP950_LEAD_CHAR, NSStringExt::c_anUnicodeMapCP950, NSStringExt::c_aoUnicodeMapCP950WithLeadByte, lCount, pData); break;
            case SINGLE_BYTE_ENCODING_CP1361:NSSTRING_WITHLEADBYTE_CP(&pUnicode, MSCP1361_LEAD_CHAR, NSStringExt::c_anUnicodeMapCP1361, NSStringExt::c_aoUnicodeMapCP1361WithLeadByte, lCount, pData); break;
        }

        pUnicode[lCount] = 0;
        std::wstring s(pUnicode);

        if (pUnicode)
            delete[] pUnicode;

        return s;
    }
    std::wstring CConverter::GetUnicodeFromUTF16(const unsigned short* pData, long lCount)
    {
        if (0 == lCount)
            return L"";

        if (2 == sizeof(wchar_t))
            return std::wstring((wchar_t*)pData, lCount);

        wchar_t* pUnicode = new wchar_t[lCount + 1];
        if (!pUnicode)
            return L"";

        wchar_t* pCur = pUnicode;
        int nCurPos = 0;
        while (nCurPos < lCount)
        {
            int nLeading = pData[nCurPos]; nCurPos++;
            if (nLeading < 0xD800 || nLeading > 0xDFFF)
            {
                *pCur = (wchar_t)nLeading;
                pCur++;
            }
            else
            {
                if (nCurPos >= lCount)
                    break;

                int nTrailing = pData[nCurPos]; nCurPos++;
                if (nTrailing >= 0xDC00 && nTrailing <= 0xDFFF)
                {
                    *pCur =		(wchar_t)(((nLeading & 0x03FF) << 10) | (nTrailing & 0x03FF));
                    *pCur +=	(wchar_t) (0x10000);
                    pCur++;
                }
            }
        }

        if (0 == pCur - pUnicode)
            return L"";

        std::wstring sRet(pUnicode, pCur - pUnicode);

        if (pUnicode)
            delete[] pUnicode;

        return sRet;
    }
    std::wstring CConverter::GetUnicodeFromUTF32(const unsigned int* pData, long lCount)
    {
        if (0 == lCount)
            return L"";

        if (4 == sizeof(wchar_t))
            return std::wstring((wchar_t*)pData, lCount);

        wchar_t* pUnicode = new wchar_t[2 * lCount + 1];
        if (!pUnicode)
            return L"";

        wchar_t* pCur = pUnicode;

        memset(pUnicode, 0x00, sizeof(wchar_t) * (2 * lCount + 1));
        for (long lIndex = 0; lIndex < lCount; lIndex++)
        {
            unsigned int unUnicode = pData[lIndex];
            if (unUnicode < 0x10000)
            {
                *pCur = unUnicode;
                pCur++;
            }
            else
            {
                unUnicode = unUnicode - 0x10000;
                *pCur = 0xD800 | (unUnicode >> 10);
                pCur++;
                *pCur = 0xDC00 | (unUnicode & 0x3FF);
                pCur++;
            }
        }

        if (0 == pCur - pUnicode)
            return L"";

        std::wstring sRet(pUnicode, pCur - pUnicode);

        if (pUnicode)
            delete[] pUnicode;

        return sRet;
    }
    unsigned int* CConverter::GetUtf32FromUnicode(const std::wstring& wsUnicodeText, unsigned int& unLen)
    {
        if (wsUnicodeText.size() <= 0)
            return NULL;

        unsigned int* pUnicodes = new unsigned int[wsUnicodeText.size()];
        if (!pUnicodes)
            return NULL;

        unsigned int* pOutput = pUnicodes;
        unLen = 0;
        if (2 == sizeof(wchar_t))
        {
            const wchar_t* wsEnd = wsUnicodeText.c_str() + wsUnicodeText.size();
            wchar_t* wsInput = (wchar_t*)wsUnicodeText.c_str();

            wchar_t wLeading, wTrailing;
            unsigned int unCode;
            while (wsInput < wsEnd)
            {
                wLeading = *wsInput++;
                if (wLeading < 0xD800 || wLeading > 0xDFFF)
                {
                    pUnicodes[unLen++] = (unsigned int)wLeading;
                }
                else if (wLeading >= 0xDC00)
                {
                    // Такого не должно быть
                    continue;
                }
                else
                {
                    unCode = (wLeading & 0x3FF) << 10;
                    wTrailing = *wsInput++;
                    if (wTrailing < 0xDC00 || wTrailing > 0xDFFF)
                    {
                        // Такого не должно быть
                        continue;
                    }
                    else
                    {
                        pUnicodes[unLen++] = (unCode | (wTrailing & 0x3FF) + 0x10000);
                    }
                }
            }
        }
        else
        {
            unLen = (unsigned int)wsUnicodeText.size();
            for (unsigned int unIndex = 0; unIndex < unLen; unIndex++)
            {
                pUnicodes[unIndex] = (unsigned int)wsUnicodeText.at(unIndex);
            }
        }

        return pUnicodes;
    }
    unsigned short* CConverter::GetUtf16FromUnicode(const std::wstring& wsUnicodeText, unsigned int& unLen)
    {
        unsigned int unTextLen = (unsigned int)wsUnicodeText.size();
        if (unTextLen <= 0)
            return NULL;

        unsigned short* pUtf16 = NULL;
        unLen = 0;
        if (2 == sizeof(wchar_t))
        {
            pUtf16 = new unsigned short[unTextLen];
            if (!pUtf16)
                return NULL;

            unLen = unTextLen;
            for (unsigned int unIndex = 0; unIndex < unLen; unIndex++)
            {
                pUtf16[unIndex] = (unsigned short)wsUnicodeText.at(unIndex);
            }
        }
        else
        {
            pUtf16 = new unsigned short[2 * unTextLen + 1];
            if (!pUtf16)
                return NULL;

            unsigned short* pCur = pUtf16;
            memset(pUtf16, 0x00, sizeof(unsigned short) * (2 * unTextLen + 1));

            for (unsigned int lIndex = 0; lIndex < unTextLen; lIndex++)
            {
                unsigned int unUnicode = wsUnicodeText.at(lIndex);
                if (unUnicode < 0x10000)
                {
                    *pCur = unUnicode;
                    pCur++;
                }
                else
                {
                    unUnicode = unUnicode - 0x10000;
                    *pCur = 0xD800 | (unUnicode >> 10);
                    pCur++;
                    *pCur = 0xDC00 | (unUnicode & 0x3FF);
                    pCur++;
                }
            }

            unLen = (unsigned int)(pCur - pUtf16);
            if (!unLen)
            {
                delete[] pUtf16;
                return NULL;
            }
        }

        return pUtf16;
    }
}