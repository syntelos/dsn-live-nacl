/*
 * DSN Live NaCl
 * Copyright (C) 2014, John Pritchard, Syntelos
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * (LGPL and GPL) as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LGPL
 * and GPL for more details.
 *
 * You should have received a copy of the LGPL and GPL along with this
 * program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _DSNL_FONT_Futural_H
#define _DSNL_FONT_Futural_H

#include "Font.h"

#define FontFutural_EM 17.600000
#define FontFutural_ASCENT 22.400000
#define FontFutural_DESCENT 9.600000
#define FontFutural_LEADING 3.200000
#define FontFutural_MODE 1
#define FontFutural_COUNT 96


class FontFutural : public Font {
 public:

    const static float GlyphVertices_1[45];
    const static float GlyphVertices_2[18];
    const static float GlyphVertices_3[36];
    const static float GlyphVertices_4[189];
    const static float GlyphVertices_5[234];
    const static float GlyphVertices_6[297];
    const static float GlyphVertices_7[54];
    const static float GlyphVertices_8[81];
    const static float GlyphVertices_9[81];
    const static float GlyphVertices_10[27];
    const static float GlyphVertices_11[18];
    const static float GlyphVertices_12[54];
    const static float GlyphVertices_13[9];
    const static float GlyphVertices_14[36];
    const static float GlyphVertices_15[9];
    const static float GlyphVertices_16[144];
    const static float GlyphVertices_17[27];
    const static float GlyphVertices_18[117];
    const static float GlyphVertices_19[126];
    const static float GlyphVertices_20[27];
    const static float GlyphVertices_21[144];
    const static float GlyphVertices_22[198];
    const static float GlyphVertices_23[18];
    const static float GlyphVertices_24[252];
    const static float GlyphVertices_25[198];
    const static float GlyphVertices_26[72];
    const static float GlyphVertices_27[90];
    const static float GlyphVertices_28[18];
    const static float GlyphVertices_29[18];
    const static float GlyphVertices_30[18];
    const static float GlyphVertices_31[153];
    const static float GlyphVertices_32[432];
    const static float GlyphVertices_33[27];
    const static float GlyphVertices_34[162];
    const static float GlyphVertices_35[153];
    const static float GlyphVertices_36[108];
    const static float GlyphVertices_37[36];
    const static float GlyphVertices_38[27];
    const static float GlyphVertices_39[171];
    const static float GlyphVertices_40[27];
    const static float GlyphVertices_41[9];
    const static float GlyphVertices_42[81];
    const static float GlyphVertices_43[27];
    const static float GlyphVertices_44[18];
    const static float GlyphVertices_45[36];
    const static float GlyphVertices_46[27];
    const static float GlyphVertices_47[180];
    const static float GlyphVertices_48[90];
    const static float GlyphVertices_49[189];
    const static float GlyphVertices_50[99];
    const static float GlyphVertices_51[171];
    const static float GlyphVertices_52[18];
    const static float GlyphVertices_53[81];
    const static float GlyphVertices_54[18];
    const static float GlyphVertices_55[36];
    const static float GlyphVertices_56[18];
    const static float GlyphVertices_57[27];
    const static float GlyphVertices_58[27];
    const static float GlyphVertices_59[36];
    const static float GlyphVertices_60[9];
    const static float GlyphVertices_61[36];
    const static float GlyphVertices_62[18];
    const static float GlyphVertices_63[9];
    const static float GlyphVertices_64[54];
    const static float GlyphVertices_65[126];
    const static float GlyphVertices_66[126];
    const static float GlyphVertices_67[117];
    const static float GlyphVertices_68[126];
    const static float GlyphVertices_69[144];
    const static float GlyphVertices_70[45];
    const static float GlyphVertices_71[171];
    const static float GlyphVertices_72[63];
    const static float GlyphVertices_73[45];
    const static float GlyphVertices_74[72];
    const static float GlyphVertices_75[27];
    const static float GlyphVertices_76[9];
    const static float GlyphVertices_77[117];
    const static float GlyphVertices_78[63];
    const static float GlyphVertices_79[144];
    const static float GlyphVertices_80[126];
    const static float GlyphVertices_81[126];
    const static float GlyphVertices_82[45];
    const static float GlyphVertices_83[144];
    const static float GlyphVertices_84[45];
    const static float GlyphVertices_85[63];
    const static float GlyphVertices_86[18];
    const static float GlyphVertices_87[36];
    const static float GlyphVertices_88[18];
    const static float GlyphVertices_89[54];
    const static float GlyphVertices_90[27];
    const static float GlyphVertices_91[306];
    const static float GlyphVertices_92[9];
    const static float GlyphVertices_93[306];
    const static float GlyphVertices_94[180];
    const static float GlyphVertices_95[297];

    const static FontGlyph GlyphSet[];

    FontFutural();
    virtual ~FontFutural();

    virtual const FontGlyph* get(char) const;

};

#endif
