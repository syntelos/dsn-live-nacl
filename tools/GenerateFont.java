
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;

import fv3.font.GlyphVector;
import fv3.font.HersheyFont;
import fv3.font.HersheyGlyph;
import fv3.math.VertexArray;

/**
 * Generate named font to target C++ header file.
 */
public class GenerateFont {

    public final static String CamelCase(String in){
        StringBuilder string = new StringBuilder();
        final char[] cary = in.toCharArray();
        final int len = cary.length;
        boolean upcase = true;
        for (int cc = 0; cc < len; cc++){
            char ch = cary[cc];
            if (Character.isIdentifierIgnorable(ch)){
                upcase = true;
            }
            else if (upcase){
                upcase = false;
                string.append(Character.toUpperCase(ch));
            }
            else {
                string.append(ch);
            }
        }
        return string.toString();
    }
    public final static void main(String[] argv){
        if (3 == argv.length){
            final String fn = argv[0];
            final String an = CamelCase(fn);
            final String cn = "Font" + an;
            final File tgt_h = new File(argv[1]);
            final File tgt_c = new File(argv[2]);
            try {
                HersheyFont font = new HersheyFont(fn);
                final int count = font.getLength();
                final int term = (count-1);
                PrintStream out;
                /*
                 * Generate header file
                 */
                out = new PrintStream(new FileOutputStream(tgt_h));
                try {
                    out.println("/*");
                    out.println(" * DSN Live NaCl");
                    out.println(" * Copyright (C) 2014, John Pritchard, Syntelos");
                    out.println(" *");
                    out.println(" * This program is free software: you can redistribute it and/or");
                    out.println(" * modify it under the terms of the GNU Lesser General Public License");
                    out.println(" * (LGPL and GPL) as published by the Free Software Foundation, either");
                    out.println(" * version 3 of the License, or (at your option) any later version.");
                    out.println(" *");
                    out.println(" * This program is distributed in the hope that it will be useful, but");
                    out.println(" * WITHOUT ANY WARRANTY; without even the implied warranty of");
                    out.println(" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LGPL");
                    out.println(" * and GPL for more details.");
                    out.println(" *");
                    out.println(" * You should have received a copy of the LGPL and GPL along with this");
                    out.println(" * program.  If not, see <http://www.gnu.org/licenses/>.");
                    out.println(" */");
                    out.printf ("#ifndef _DSNL_FONT_%s_H%n",an);
                    out.printf ("#define _DSNL_FONT_%s_H%n",an);
                    out.println();
                    out.println("#include \"Font.h\"");
                    out.println();
                    out.printf ("#define %s_EM %f%n",cn,font.getEm());
                    out.printf ("#define %s_ASCENT %f%n",cn,font.getAscent());
                    out.printf ("#define %s_DESCENT %f%n",cn,font.getDescent());
                    out.printf ("#define %s_LEADING %f%n",cn,font.getLeading());
                    out.printf ("#define %s_MODE %d%n",cn,font.getGlyphVectorType().ordinal());
                    out.printf ("#define %s_COUNT %d%n",cn,count);
                    out.println();
                    out.println();
                    out.printf ("class %s : public Font {%n",cn);
                    out.println(" public:");
                    out.println();
                    for (int cc = 0; cc < count; cc++){

                        HersheyGlyph glyph = font.get(cc);

                        final float[] vertices = glyph.array();

                        final int nv3 = vertices.length;

                        if (0 < nv3){

                            out.printf ("    const static float GlyphVertices_%d[%d]; // '%c'%n",cc,nv3,(char)(cc+' '));
                        }
                    }
                    out.println();
                    out.println("    const static FontGlyph GlyphSet[];");
                    out.println();
                    out.printf ("    %s();%n",cn);
                    out.printf ("    virtual ~%s();%n",cn);
                    out.println();
                    out.println("    virtual const FontGlyph* get(char) const;");
                    out.println();
                    out.println("};");
                    out.println();
                    out.println("#endif");
                }
                finally {
                    out.close();
                }
                /*
                 * Generate source file
                 */
                out = new PrintStream(new FileOutputStream(tgt_c));
                try {
                    out.println("/*");
                    out.println(" * DSN Live NaCl");
                    out.println(" * Copyright (C) 2014, John Pritchard, Syntelos");
                    out.println(" *");
                    out.println(" * This program is free software: you can redistribute it and/or");
                    out.println(" * modify it under the terms of the GNU Lesser General Public License");
                    out.println(" * (LGPL and GPL) as published by the Free Software Foundation, either");
                    out.println(" * version 3 of the License, or (at your option) any later version.");
                    out.println(" *");
                    out.println(" * This program is distributed in the hope that it will be useful, but");
                    out.println(" * WITHOUT ANY WARRANTY; without even the implied warranty of");
                    out.println(" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LGPL");
                    out.println(" * and GPL for more details.");
                    out.println(" *");
                    out.println(" * You should have received a copy of the LGPL and GPL along with this");
                    out.println(" * program.  If not, see <http://www.gnu.org/licenses/>.");
                    out.println(" */");
                    out.println();
                    out.printf ("#include \"%s\"%n",tgt_h.getName());
                    out.println();
                    out.println("/*");
                    out.println(" */");
                    /*
                     * char value = (' ' + cc)
                     */
                    for (int cc = 0; cc < count; cc++){

                        HersheyGlyph glyph = font.get(cc);

                        float[] vertices = glyph.array();

                        final int nv3 = vertices.length;

                        if (0 < nv3){
                            /*
                             * Translate glyph origin to (0,0)~
                             */
                            float minX = Float.MAX_VALUE;

                            for (int x = 0; (x+2) < nv3; x+=3){

                                minX = Math.min(minX,vertices[x]);
                            }

                            if (0.0 < minX){

                                for (int x = 0; (x+2) < nv3; x+=3){

                                    vertices[x] -= minX;
                                }
                            }
                            /*
                             * Emit vertices
                             */
                            out.printf ("const float %s::GlyphVertices_%d[%d] = { // '%c'%n",cn,cc,nv3,(char)(cc+' '));

                            for (int x = 0, y = 1, z = 2; z < nv3; x+=3,y+=3,z+=3){

                                out.printf ("    %f, %f, %f, %n",vertices[x],vertices[y],vertices[z]);
                            }

                            out.printf ("};%n");
                        }
                    }
                    out.println();
                    out.println("/*");
                    out.println(" */");
                    out.printf ("const FontGlyph %s::GlyphSet[%s_COUNT] = {%n",cn,cn);
                    /*
                     * char value = (' ' + cc)
                     */
                    for (int cc = 0; cc < count; cc++){

                        HersheyGlyph glyph = font.get(cc);

                        final float[] vertices = glyph.array();

                        final int nv3 = vertices.length;

                        float minX = Float.MAX_VALUE;
                        float maxX = Float.MIN_VALUE;
                        float minY = Float.MAX_VALUE;
                        float maxY = Float.MIN_VALUE;

                        float minZ = Float.MAX_VALUE;
                        float maxZ = Float.MIN_VALUE;

                        if (0 == nv3){
                            minX = 0f;
                            maxX = font.getEm();
                            minY = 0f;
                            maxY = 0f;
                            minZ = 0f;
                            maxZ = 0f;
                        }
                        else {
                            for (int x = 0, y = 1, z = 2; z < nv3; x+=3,y+=3,z+=3){

                                float fx = vertices[x];
                                float fy = vertices[y];
                                float fz = vertices[z];

                                minX = Math.min(minX,fx);
                                maxX = Math.max(maxX,fx);

                                minY = Math.min(minY,fy);
                                maxY = Math.max(maxY,fy);

                                minZ = Math.min(minZ,fz);
                                maxZ = Math.max(maxZ,fz);
                            }
                        }

                        float midX = (minX + maxX)/2f;
                        float midY = (minY + maxY)/2f;
                        float midZ = (minZ + maxZ)/2f;

                        out.printf ("    {%n");
                        out.printf ("        %f, %f, %f, %n",minX,midX,maxX);
                        out.printf ("        %f, %f, %f, %n",minY,midY,maxY);
                        out.printf ("        %f, %f, %f, %n",minZ,midZ,maxZ);
                        out.printf ("        %d,%n",nv3);

                        if (0 < nv3){

                            out.printf ("        GlyphVertices_%d  // '%c'%n",cc,(char)(cc+' '));
                        }
                        else {
                            out.printf ("        0%n");
                        }

                        if (cc < term){
                            out.printf ("    },%n");
                        }
                        else {
                            out.printf ("    }%n");
                        }
                    }
                    out.println("};");
                    out.println();
                    out.printf ("%s::%s()%n",cn,cn);
                    out.printf ("    : Font(%s_EM,%s_ASCENT,%s_DESCENT,%s_LEADING,%s_MODE)%n",cn,cn,cn,cn,cn);
                    out.println("{}");
                    out.printf ("%s::~%s()%n",cn,cn);
                    out.println("{}");
                    out.println();
                    out.printf ("const FontGlyph* %s::get(char ch) const {%n",cn);
                    out.println("    if (' ' >= ch){");
                    out.println("        return &(GlyphSet[0]);");
                    out.println("    }");
                    out.println("    else {");
                    out.println("        const unsigned int idx = (ch-' ');");
                    out.printf ("        if (idx < %s_COUNT){%n",cn);
                    out.println("            return &(GlyphSet[idx]);");
                    out.println("        }");
                    out.println("        else {");
                    out.println("            return 0;");
                    out.println("        }");
                    out.println("    }");
                    out.println("}");
                    out.println();
                }
                finally {
                    out.close();
                }
            }
            catch (IOException not_found){
                not_found.printStackTrace();

                System.err.printf("%nError: unrecognized font '%s', or unable to write file '%s' or '%s'.%n",fn,tgt_h.getPath(),tgt_c.getPath());

                System.exit(1);
            }
        }
        else {
            System.err.printf("Usage%n\tGenerateFont <fv3-jhf-name> <tgt>.h <tgt>.cc%nDescription%n\tGenerate header and source files for font.");
            System.exit(1);
        }
    }
}
