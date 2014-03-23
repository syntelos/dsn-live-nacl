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

    const static float GlyphVertices_1[30]; // '!'
    const static float GlyphVertices_2[12]; // '"'
    const static float GlyphVertices_3[24]; // '#'
    const static float GlyphVertices_4[126]; // '$'
    const static float GlyphVertices_5[156]; // '%'
    const static float GlyphVertices_6[198]; // '&'
    const static float GlyphVertices_7[36]; // '''
    const static float GlyphVertices_8[54]; // '('
    const static float GlyphVertices_9[54]; // ')'
    const static float GlyphVertices_10[18]; // '*'
    const static float GlyphVertices_11[12]; // '+'
    const static float GlyphVertices_12[36]; // ','
    const static float GlyphVertices_13[6]; // '-'
    const static float GlyphVertices_14[24]; // '.'
    const static float GlyphVertices_15[6]; // '/'
    const static float GlyphVertices_16[96]; // '0'
    const static float GlyphVertices_17[18]; // '1'
    const static float GlyphVertices_18[78]; // '2'
    const static float GlyphVertices_19[84]; // '3'
    const static float GlyphVertices_20[18]; // '4'
    const static float GlyphVertices_21[96]; // '5'
    const static float GlyphVertices_22[132]; // '6'
    const static float GlyphVertices_23[12]; // '7'
    const static float GlyphVertices_24[168]; // '8'
    const static float GlyphVertices_25[132]; // '9'
    const static float GlyphVertices_26[48]; // ':'
    const static float GlyphVertices_27[60]; // ';'
    const static float GlyphVertices_28[12]; // '<'
    const static float GlyphVertices_29[12]; // '='
    const static float GlyphVertices_30[12]; // '>'
    const static float GlyphVertices_31[102]; // '?'
    const static float GlyphVertices_32[288]; // '@'
    const static float GlyphVertices_33[18]; // 'A'
    const static float GlyphVertices_34[108]; // 'B'
    const static float GlyphVertices_35[102]; // 'C'
    const static float GlyphVertices_36[72]; // 'D'
    const static float GlyphVertices_37[24]; // 'E'
    const static float GlyphVertices_38[18]; // 'F'
    const static float GlyphVertices_39[114]; // 'G'
    const static float GlyphVertices_40[18]; // 'H'
    const static float GlyphVertices_41[6]; // 'I'
    const static float GlyphVertices_42[54]; // 'J'
    const static float GlyphVertices_43[18]; // 'K'
    const static float GlyphVertices_44[12]; // 'L'
    const static float GlyphVertices_45[24]; // 'M'
    const static float GlyphVertices_46[18]; // 'N'
    const static float GlyphVertices_47[120]; // 'O'
    const static float GlyphVertices_48[60]; // 'P'
    const static float GlyphVertices_49[126]; // 'Q'
    const static float GlyphVertices_50[66]; // 'R'
    const static float GlyphVertices_51[114]; // 'S'
    const static float GlyphVertices_52[12]; // 'T'
    const static float GlyphVertices_53[54]; // 'U'
    const static float GlyphVertices_54[12]; // 'V'
    const static float GlyphVertices_55[24]; // 'W'
    const static float GlyphVertices_56[12]; // 'X'
    const static float GlyphVertices_57[18]; // 'Y'
    const static float GlyphVertices_58[18]; // 'Z'
    const static float GlyphVertices_59[24]; // '['
    const static float GlyphVertices_60[6]; // '\'
    const static float GlyphVertices_61[24]; // ']'
    const static float GlyphVertices_62[12]; // '^'
    const static float GlyphVertices_63[6]; // '_'
    const static float GlyphVertices_64[36]; // '`'
    const static float GlyphVertices_65[84]; // 'a'
    const static float GlyphVertices_66[84]; // 'b'
    const static float GlyphVertices_67[78]; // 'c'
    const static float GlyphVertices_68[84]; // 'd'
    const static float GlyphVertices_69[96]; // 'e'
    const static float GlyphVertices_70[30]; // 'f'
    const static float GlyphVertices_71[114]; // 'g'
    const static float GlyphVertices_72[42]; // 'h'
    const static float GlyphVertices_73[30]; // 'i'
    const static float GlyphVertices_74[48]; // 'j'
    const static float GlyphVertices_75[18]; // 'k'
    const static float GlyphVertices_76[6]; // 'l'
    const static float GlyphVertices_77[78]; // 'm'
    const static float GlyphVertices_78[42]; // 'n'
    const static float GlyphVertices_79[96]; // 'o'
    const static float GlyphVertices_80[84]; // 'p'
    const static float GlyphVertices_81[84]; // 'q'
    const static float GlyphVertices_82[30]; // 'r'
    const static float GlyphVertices_83[96]; // 's'
    const static float GlyphVertices_84[30]; // 't'
    const static float GlyphVertices_85[42]; // 'u'
    const static float GlyphVertices_86[12]; // 'v'
    const static float GlyphVertices_87[24]; // 'w'
    const static float GlyphVertices_88[12]; // 'x'
    const static float GlyphVertices_89[36]; // 'y'
    const static float GlyphVertices_90[18]; // 'z'
    const static float GlyphVertices_91[204]; // '{'
    const static float GlyphVertices_92[6]; // '|'
    const static float GlyphVertices_93[204]; // '}'
    const static float GlyphVertices_94[120]; // '~'
    const static float GlyphVertices_95[198]; // ''

    const static FontGlyph GlyphSet[];

    FontFutural();
    virtual ~FontFutural();

    virtual const FontGlyph* get(char) const;

};

#endif
