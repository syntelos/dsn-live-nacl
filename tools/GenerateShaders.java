
import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;

/**
 * Generate shaders text target C++ header file.
 */
public class GenerateShaders {

    public final static String CamelCase(String in){
        StringBuilder string = new StringBuilder();
        final char[] cary = in.toCharArray();
        final int len = cary.length;
        boolean upcase = true;
        for (int cc = 0; cc < len; cc++){
            char ch = cary[cc];
            if ('.' == ch || Character.isIdentifierIgnorable(ch)){
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
    public final static String Basename(String in, String tail){
        if (in.endsWith(tail)){
            return in.substring(0,in.length()-tail.length());
        }
        else
            return in;
    }
    public final static void main(String[] argv){
        if (2 == argv.length){
            final File tgt_h = new File(argv[0]);
            final File src_d = new File(argv[1]);
            try {
                PrintStream out;

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


                    for (File src : src_d.listFiles()){
                        String fn = Basename(src.getName(),".glsl");
                        String an = CamelCase(fn);

                        out.println();
                        out.printf ("const char* %s = %n",an);

                        BufferedReader in = new BufferedReader(new FileReader(src));
                        try {
                            String lin;
                            while (null != (lin = in.readLine())){
                                out.printf ("    \"%s\\n\"%n",lin);
                            }
                        }
                        finally {
                            in.close();
                        }
                        out.printf (";%n");
                    }
                }
                finally {
                    out.close();
                }
            }
            catch (IOException exc){
                exc.printStackTrace();

                System.err.printf("Error, unable to write file '%s'.%n",tgt_h.getPath());
                System.exit(1);
            }
        }
        else {
            System.err.printf("Usage%n\tGenerateShaders <tgt>.h <src_dir>%nDescription%n\tGenerate header file for shaders.");
            System.exit(1);
        }
    }
}
