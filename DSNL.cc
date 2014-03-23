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

#include <GLES2/gl2.h>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "ppapi/cpp/graphics_3d.h"
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"
#include "ppapi/cpp/var_array.h"
#include "ppapi/lib/gl/gles2/gl2ext_ppapi.h"
#include "ppapi/utility/completion_callback_factory.h"

#include "glh.h"
#include "Fv3Color.h"
#include "Fv3Matrix.h"
#include "FontFutural.h"
#include "Shaders.h"

/*!
 * 
 */
class DSNLInstance : public pp::Instance {

    pp::CompletionCallbackFactory<DSNLInstance> callback_factory;
    pp::Graphics3D context;
    int32_t width;
    int32_t height;

    GLuint prog_vert;
    GLuint prog_frag;
    GLuint prog;
    GLuint prog_color;
    GLuint prog_camera;

    FontGlyphVector *string;


public:

    explicit DSNLInstance(PP_Instance instance)
        : pp::Instance(instance),
          callback_factory(this),
          width(500),
          height(500)
    {
        std::cerr << "DSNL: Instantiated module instance." << std::endl;
    }
    virtual ~DSNLInstance()
    {}

    virtual void HandleMessage(const pp::Var& var_message) {

        std::cerr << "Received message '" << var_message.AsString() << "'." << std::endl;
    }
    virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]) {

        uint32_t cc;
        for (cc = 0; cc < argc; cc++){
            const char* n = argn[cc];
            const char* v = argv[cc];

            std::cerr << "DSNL: init (" << n << ": " << v << ")" << std::endl;
        }
        SendMessage("DSNL: Initialized module instance.");

        return true;
    }
    virtual void DidChangeView(const pp::View& view) {
        pp::Rect rect = view.GetRect();
        int32_t new_width = rect.width();
        int32_t new_height = rect.height();

        if (context.is_null()) {
            if (InitGL(new_width, new_height)){
                InitProgram();
                InitBuffers();
                MainLoop(0);
            }
            else {
                std::cerr << "DSNL: Failed to initialize GL context in change view." << std::endl;
                return;
            }
        }
        else {
            int32_t result = context.ResizeBuffers(new_width, new_height);
            if (0 > result){
                std::cerr << "DSNL: Failed to resize buffers in change view." << std::endl;
                return;
            }
        }

        width = new_width;
        height = new_height;

        glViewport(0, 0, width, height);

        SendMessage("DSNL: Initialized graphics in change view.");
    }

private:

    bool InitGL(int32_t new_width, int32_t new_height) {

        if (glInitializePPAPI(pp::Module::Get()->get_browser_interface())){

            const int32_t attrib_list[] = {
                PP_GRAPHICS3DATTRIB_ALPHA_SIZE, 8,
                PP_GRAPHICS3DATTRIB_DEPTH_SIZE, 24,
                PP_GRAPHICS3DATTRIB_WIDTH, new_width,
                PP_GRAPHICS3DATTRIB_HEIGHT, new_height,
                PP_GRAPHICS3DATTRIB_NONE
            };

            context = pp::Graphics3D(this, attrib_list);

            if (BindGraphics(context)){

                glSetCurrentContextPPAPI(context.pp_resource());
                return true;
            }
            else {
                std::cerr << "DSNL: Unable to bind GL context." << std::endl;

                context = pp::Graphics3D();
                glSetCurrentContextPPAPI(0);
                return false;
            }
        }
        else {
            std::cerr << "DSNL: Unable to initialize GL PPAPI." << std::endl;
            return false;
        }
    }
    void Render() {

        std::cerr << "DSNL: Render() <begin>" << std::endl;

        glClearColor(0.0, 0.4, 0.7, 1);
        glClearDepthf(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        std::cerr << "DSNL: Render() <prog>" << std::endl;

        glUseProgram(prog);

        std::cerr << "DSNL: Render() <init camera>" << std::endl;

        Fv3Matrix camera(Fv3Matrix::ID);

        std::cerr << "DSNL: Render() <aspect = " << width << "/" << height << ">" << std::endl;

        const float aspect = (width/height);

        std::cerr << "DSNL: Render() <compute perspective>" << std::endl;

        glhPerspectivef2(camera,45.0,aspect,0.0,10.0);

        std::cerr << "DSNL: Render() <completed perspective computation, binding uniform 'u_camera'>" << std::endl;

        glUniformMatrix4fv(prog_camera,1,GL_FALSE,camera.array);

        std::cerr << "DSNL: Render() <binding uniform 'u_color'>" << std::endl;

        glUniform4fv(prog_color,1,Fv3Color::White.array);

        std::cerr << "DSNL: Render() <binding buffer 'string->vertex_buffer'>" << std::endl;

        glBindBuffer(GL_ARRAY_BUFFER, string->vertex_buffer);

        std::cerr << "DSNL: Render() <draw elements 'string->count/2'>" << std::endl;

        glDrawElements(GL_LINES, string->count/2, GL_UNSIGNED_BYTE, 0);

        std::cerr << "DSNL: Render() <end>" << std::endl;
    }
    void InitBuffers(){

        FontFutural font;

        string = new FontGlyphVector(font,"string");

        glGenBuffers(1,&(string->vertex_buffer));

        glBindBuffer(GL_ARRAY_BUFFER, string->vertex_buffer);

        glBufferData(GL_ARRAY_BUFFER, (string->array_length*sizeof(float)), string->array, GL_STATIC_DRAW);

        std::cerr << "DSNL: InitBuffers() <end>" << std::endl;
    }
    void InitProgram(){

        prog_frag = ShaderCompile(GL_FRAGMENT_SHADER,"LineFrag",LineFrag);
        if (0 != prog_frag){

            prog_vert = ShaderCompile(GL_VERTEX_SHADER,"LineVert",LineVert);
            if (0 != prog_vert){

                prog = ProgramLink(prog_frag,prog_vert,"Line");
                if (0 != prog){

                    prog_camera = glGetUniformLocation(prog,"u_camera");
                    prog_color = glGetUniformLocation(prog,"u_color");
                }
            }
        }
        std::cerr << "DSNL: InitProgram() <end>" << std::endl;
    }
    void MainLoop(int32_t) {

        Render();

        context.SwapBuffers(callback_factory.NewCallback(&DSNLInstance::MainLoop));
    }
    static GLuint ShaderCompile(GLenum type, const char* name, const char* text){
        GLuint shader = glCreateShader(type);
        {
            glShaderSource(shader,1,&text,0);
            glCompileShader(shader);
        }
        GLint status;
        glGetShaderiv(shader,GL_COMPILE_STATUS,&status);
        if (GL_TRUE == status){
            return shader;
        }
        else {
            char erbuf[1024];
            GLsizei output;
            glGetShaderInfoLog(shader,sizeof(erbuf),&output,erbuf);
            std::cerr << "Shader '" << name << "' failed to compile: " << erbuf << std::endl;
            return 0;
        }
    }
    static GLuint ProgramLink(GLuint frag, GLuint vert, const char* name){
        GLuint program = glCreateProgram();
        {
            glAttachShader(program,frag);
            glAttachShader(program,vert);
            glLinkProgram(program);
        }
        GLint status;
        glGetProgramiv(program,GL_LINK_STATUS,&status);
        if (GL_TRUE == status){
            return program;
        }
        else {
            char erbuf[1024];
            GLsizei output;
            glGetProgramInfoLog(program,sizeof(erbuf),&output,erbuf);
            std::cerr << "Program '" << name << "' failed to link: " << erbuf << std::endl;
            return 0;
        }
    }
    void SendMessage(const char* m){

        std::cerr << "SendMessage: '" << m << "'." << std::endl;

        pp::Var v(m);
        PostMessage(v);
    }
};
/*!
 * 
 */
class DSNLModule : public pp::Module {
public:

    DSNLModule()
        : pp::Module()
    {}
    virtual ~DSNLModule()
    {}
    virtual pp::Instance* CreateInstance(PP_Instance instance) {

        return new DSNLInstance(instance);
    }
};
/*!
 * 
 */
namespace pp {

    Module* CreateModule() {

        return new DSNLModule();
    }
}
