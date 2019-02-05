﻿/*
 * (c) Copyright Ascensio System SIA 2010-2019
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
 * You can contact Ascensio System SIA at 20A-12 Ernesta Birznieka-Upisha
 * street, Riga, Latvia, EU, LV-1050.
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
#pragma once
#include "../PptxShape.h"

namespace OOXMLShapes
{
	class CStar24 : public CPPTXShape
	{
		public:
			CStar24()
			{
				LoadFromXML(
					_T("<ooxml-shape>")
					_T("<avLst xmlns=\"http://schemas.openxmlformats.org/drawingml/2006/main\">")
					  _T("<gd name=\"adj\" fmla=\"val 37500\" />")
					_T("</avLst>")
					_T("<gdLst xmlns=\"http://schemas.openxmlformats.org/drawingml/2006/main\">")
					  _T("<gd name=\"a\" fmla=\"pin 0 adj 50000\" />")
					  _T("<gd name=\"dx1\" fmla=\"cos wd2 900000\" />")
					  _T("<gd name=\"dx2\" fmla=\"cos wd2 1800000\" />")
					  _T("<gd name=\"dx3\" fmla=\"cos wd2 2700000\" />")
					  _T("<gd name=\"dx4\" fmla=\"val wd4\" />")
					  _T("<gd name=\"dx5\" fmla=\"cos wd2 4500000\" />")
					  _T("<gd name=\"dy1\" fmla=\"sin hd2 4500000\" />")
					  _T("<gd name=\"dy2\" fmla=\"sin hd2 3600000\" />")
					  _T("<gd name=\"dy3\" fmla=\"sin hd2 2700000\" />")
					  _T("<gd name=\"dy4\" fmla=\"val hd4\" />")
					  _T("<gd name=\"dy5\" fmla=\"sin hd2 900000\" />")
					  _T("<gd name=\"x1\" fmla=\"+- hc 0 dx1\" />")
					  _T("<gd name=\"x2\" fmla=\"+- hc 0 dx2\" />")
					  _T("<gd name=\"x3\" fmla=\"+- hc 0 dx3\" />")
					  _T("<gd name=\"x4\" fmla=\"+- hc 0 dx4\" />")
					  _T("<gd name=\"x5\" fmla=\"+- hc 0 dx5\" />")
					  _T("<gd name=\"x6\" fmla=\"+- hc dx5 0\" />")
					  _T("<gd name=\"x7\" fmla=\"+- hc dx4 0\" />")
					  _T("<gd name=\"x8\" fmla=\"+- hc dx3 0\" />")
					  _T("<gd name=\"x9\" fmla=\"+- hc dx2 0\" />")
					  _T("<gd name=\"x10\" fmla=\"+- hc dx1 0\" />")
					  _T("<gd name=\"y1\" fmla=\"+- vc 0 dy1\" />")
					  _T("<gd name=\"y2\" fmla=\"+- vc 0 dy2\" />")
					  _T("<gd name=\"y3\" fmla=\"+- vc 0 dy3\" />")
					  _T("<gd name=\"y4\" fmla=\"+- vc 0 dy4\" />")
					  _T("<gd name=\"y5\" fmla=\"+- vc 0 dy5\" />")
					  _T("<gd name=\"y6\" fmla=\"+- vc dy5 0\" />")
					  _T("<gd name=\"y7\" fmla=\"+- vc dy4 0\" />")
					  _T("<gd name=\"y8\" fmla=\"+- vc dy3 0\" />")
					  _T("<gd name=\"y9\" fmla=\"+- vc dy2 0\" />")
					  _T("<gd name=\"y10\" fmla=\"+- vc dy1 0\" />")
					  _T("<gd name=\"iwd2\" fmla=\"*/ wd2 a 50000\" />")
					  _T("<gd name=\"ihd2\" fmla=\"*/ hd2 a 50000\" />")
					  _T("<gd name=\"sdx1\" fmla=\"*/ iwd2 99144 100000\" />")
					  _T("<gd name=\"sdx2\" fmla=\"*/ iwd2 92388 100000\" />")
					  _T("<gd name=\"sdx3\" fmla=\"*/ iwd2 79335 100000\" />")
					  _T("<gd name=\"sdx4\" fmla=\"*/ iwd2 60876 100000\" />")
					  _T("<gd name=\"sdx5\" fmla=\"*/ iwd2 38268 100000\" />")
					  _T("<gd name=\"sdx6\" fmla=\"*/ iwd2 13053 100000\" />")
					  _T("<gd name=\"sdy1\" fmla=\"*/ ihd2 99144 100000\" />")
					  _T("<gd name=\"sdy2\" fmla=\"*/ ihd2 92388 100000\" />")
					  _T("<gd name=\"sdy3\" fmla=\"*/ ihd2 79335 100000\" />")
					  _T("<gd name=\"sdy4\" fmla=\"*/ ihd2 60876 100000\" />")
					  _T("<gd name=\"sdy5\" fmla=\"*/ ihd2 38268 100000\" />")
					  _T("<gd name=\"sdy6\" fmla=\"*/ ihd2 13053 100000\" />")
					  _T("<gd name=\"sx1\" fmla=\"+- hc 0 sdx1\" />")
					  _T("<gd name=\"sx2\" fmla=\"+- hc 0 sdx2\" />")
					  _T("<gd name=\"sx3\" fmla=\"+- hc 0 sdx3\" />")
					  _T("<gd name=\"sx4\" fmla=\"+- hc 0 sdx4\" />")
					  _T("<gd name=\"sx5\" fmla=\"+- hc 0 sdx5\" />")
					  _T("<gd name=\"sx6\" fmla=\"+- hc 0 sdx6\" />")
					  _T("<gd name=\"sx7\" fmla=\"+- hc sdx6 0\" />")
					  _T("<gd name=\"sx8\" fmla=\"+- hc sdx5 0\" />")
					  _T("<gd name=\"sx9\" fmla=\"+- hc sdx4 0\" />")
					  _T("<gd name=\"sx10\" fmla=\"+- hc sdx3 0\" />")
					  _T("<gd name=\"sx11\" fmla=\"+- hc sdx2 0\" />")
					  _T("<gd name=\"sx12\" fmla=\"+- hc sdx1 0\" />")
					  _T("<gd name=\"sy1\" fmla=\"+- vc 0 sdy1\" />")
					  _T("<gd name=\"sy2\" fmla=\"+- vc 0 sdy2\" />")
					  _T("<gd name=\"sy3\" fmla=\"+- vc 0 sdy3\" />")
					  _T("<gd name=\"sy4\" fmla=\"+- vc 0 sdy4\" />")
					  _T("<gd name=\"sy5\" fmla=\"+- vc 0 sdy5\" />")
					  _T("<gd name=\"sy6\" fmla=\"+- vc 0 sdy6\" />")
					  _T("<gd name=\"sy7\" fmla=\"+- vc sdy6 0\" />")
					  _T("<gd name=\"sy8\" fmla=\"+- vc sdy5 0\" />")
					  _T("<gd name=\"sy9\" fmla=\"+- vc sdy4 0\" />")
					  _T("<gd name=\"sy10\" fmla=\"+- vc sdy3 0\" />")
					  _T("<gd name=\"sy11\" fmla=\"+- vc sdy2 0\" />")
					  _T("<gd name=\"sy12\" fmla=\"+- vc sdy1 0\" />")
					  _T("<gd name=\"idx\" fmla=\"cos iwd2 2700000\" />")
					  _T("<gd name=\"idy\" fmla=\"sin ihd2 2700000\" />")
					  _T("<gd name=\"il\" fmla=\"+- hc 0 idx\" />")
					  _T("<gd name=\"it\" fmla=\"+- vc 0 idy\" />")
					  _T("<gd name=\"ir\" fmla=\"+- hc idx 0\" />")
					  _T("<gd name=\"ib\" fmla=\"+- vc idy 0\" />")
					  _T("<gd name=\"yAdj\" fmla=\"+- vc 0 ihd2\" />")
					_T("</gdLst>")
					_T("<ahLst xmlns=\"http://schemas.openxmlformats.org/drawingml/2006/main\">")
					  _T("<ahXY gdRefY=\"adj\" minY=\"0\" maxY=\"ssd2\">")
						_T("<pos x=\"hc\" y=\"yAdj\" />")
					  _T("</ahXY>")
					_T("</ahLst>")
					_T("<cxnLst xmlns=\"http://schemas.openxmlformats.org/drawingml/2006/main\">")
					  _T("<cxn ang=\"3cd4\">")
						_T("<pos x=\"hc\" y=\"t\" />")
					  _T("</cxn>")
					  _T("<cxn ang=\"cd2\">")
						_T("<pos x=\"l\" y=\"vc\" />")
					  _T("</cxn>")
					  _T("<cxn ang=\"cd4\">")
						_T("<pos x=\"hc\" y=\"b\" />")
					  _T("</cxn>")
					  _T("<cxn ang=\"0\">")
						_T("<pos x=\"r\" y=\"vc\" />")
					  _T("</cxn>")
					_T("</cxnLst>")
					_T("<rect l=\"il\" t=\"it\" r=\"ir\" b=\"ib\" xmlns=\"http://schemas.openxmlformats.org/drawingml/2006/main\" />")
					_T("<pathLst xmlns=\"http://schemas.openxmlformats.org/drawingml/2006/main\">")
					  _T("<path>")
						_T("<moveTo>")
						  _T("<pt x=\"l\" y=\"vc\" />")
						_T("</moveTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx1\" y=\"sy6\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x1\" y=\"y5\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx2\" y=\"sy5\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x2\" y=\"y4\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx3\" y=\"sy4\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x3\" y=\"y3\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx4\" y=\"sy3\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x4\" y=\"y2\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx5\" y=\"sy2\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x5\" y=\"y1\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx6\" y=\"sy1\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"hc\" y=\"t\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx7\" y=\"sy1\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x6\" y=\"y1\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx8\" y=\"sy2\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x7\" y=\"y2\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx9\" y=\"sy3\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x8\" y=\"y3\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx10\" y=\"sy4\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x9\" y=\"y4\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx11\" y=\"sy5\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x10\" y=\"y5\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx12\" y=\"sy6\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"r\" y=\"vc\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx12\" y=\"sy7\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x10\" y=\"y6\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx11\" y=\"sy8\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x9\" y=\"y7\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx10\" y=\"sy9\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x8\" y=\"y8\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx9\" y=\"sy10\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x7\" y=\"y9\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx8\" y=\"sy11\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x6\" y=\"y10\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx7\" y=\"sy12\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"hc\" y=\"b\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx6\" y=\"sy12\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x5\" y=\"y10\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx5\" y=\"sy11\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x4\" y=\"y9\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx4\" y=\"sy10\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x3\" y=\"y8\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx3\" y=\"sy9\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x2\" y=\"y7\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx2\" y=\"sy8\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"x1\" y=\"y6\" />")
						_T("</lnTo>")
						_T("<lnTo>")
						  _T("<pt x=\"sx1\" y=\"sy7\" />")
						_T("</lnTo>")
						_T("<close />")
					  _T("</path>")
					_T("</pathLst>")
					_T("</ooxml-shape>")
				);
			}
	};
}