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
 * There's only one instance of DSNL per module.
 */
class DSNLInstance : public pp::Instance {

    pp::CompletionCallbackFactory<DSNLInstance> callback_factory;
    pp::Graphics3D context;
    int32_t width;
    int32_t height;

    GLuint prog_vert;
    GLuint prog_frag;
    GLuint prog;
    int prog_position;
    int prog_color;
    int prog_camera;

    bool running;

    FontGlyphVector *string;

public:

    explicit DSNLInstance(PP_Instance instance)
        : pp::Instance(instance),
          callback_factory(this), context(),
          width(0),
          height(0),
          prog_vert(0), prog_frag(0), prog(0),
          prog_position(0), prog_color(0), prog_camera(0),
          running(true),
          string(0)
    {
        std::cerr << "DSNL: DSNL()" << std::endl;
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

            std::cerr << "DSNL: Init( " << n << ": '" << v << "')" << std::endl;
        }
        SendMessage("DSNL: Init()");

        return true;
    }
    virtual void DidChangeView(const pp::View& view) {

        std::cerr << "DSNL: DidChangeView()" << std::endl;

        pp::Rect rect = view.GetRect();
        int32_t new_width = rect.width();
        int32_t new_height = rect.height();

        if (context.is_null()) {
            std::cerr << "DSNL: DidChangeView() <init>" << std::endl;

            if (InitGL(new_width, new_height)){

                InitProgram();
                InitBuffers();
                MainLoop(0);
            }
            else {
                std::cerr << "DSNL: DidChangeView(): Failed to initialize GL context in change view." << std::endl;
                return;
            }
        }
        else {
            std::cerr << "DSNL: DidChangeView() <resize>" << std::endl;

            int32_t result = context.ResizeBuffers(new_width, new_height);
            if (0 > result){
                std::cerr << "DSNL: DidChangeView(): Failed to resize buffers in change view." << std::endl;
                return;
            }
            else {
                width = new_width;
                height = new_height;
            }
        }

        glViewport(0, 0, width, height);

        std::cerr << "DSNL: DidChangeView() <end> ( w: " << this->width << ", h: " << this->height << ")" << std::endl;
    }

private:

    bool InitGL(int32_t new_width, int32_t new_height) {

        std::cerr << "DSNL: InitGL()" << std::endl;

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

                width = new_width;

                height = new_height;

                return true;
            }
            else {
                std::cerr << "DSNL: InitGL(): Unable to bind GL context." << std::endl;

                context = pp::Graphics3D();
                glSetCurrentContextPPAPI(0);
                return false;
            }
        }
        else {
            std::cerr << "DSNL: InitGL(): Unable to initialize GL PPAPI." << std::endl;
            return false;
        }
    }
    void Render() {

        glClearColor(0.0, 0.4, 0.7, 1);
        glClearDepthf(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);


        glUseProgram(prog);


        Fv3Matrix camera(Fv3Matrix::ID);

        const float aspect = (width/height);

        glhPerspectivef2(camera,45.0,aspect,0.0,10.0);


        glUniformMatrix4fv(prog_camera,1,GL_FALSE,camera.array);

        glUniform4fv(prog_color,1,Fv3Color::White.array);

        if (erck("Uniform")){
            return;
        }

        glBindBuffer(GL_ARRAY_BUFFER, string->vertex_buffer);

        if (erck("BindBuffer")){
            return;
        }

        glVertexAttribPointer(prog_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

        if (erck("VertexAttribPointer")){

            fprintf(stderr,"DSNL VertexAttribPointer index: 0x%08x\n", prog_position);
            return;
        }

        glEnableVertexAttribArray(prog_position);

        if (erck("VertexAttribArray")){
            return;
        }

        glDrawElements(GL_LINES, string->elements, GL_FLOAT, 0);

        if (erck("DrawElements")){
            return;
        }
    }
    bool erck(const char* fn){
        switch(glGetError()){
        case GL_INVALID_ENUM:
            std::cerr << "DSNL Error: " << fn << ": INVALID_ENUM" << std::endl;
            running = false;
            return true;
        case GL_INVALID_VALUE:
            std::cerr << "DSNL Error: " << fn << ": INVALID_VALUE" << std::endl;
            running = false;
            return true;
        case GL_INVALID_OPERATION:
            std::cerr << "DSNL Error: " << fn << ": INVALID_OPERATION" << std::endl;
            running = false;
            return true;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cerr << "DSNL Error: " << fn << ": INVALID_FRAMEBUFFER_OPERATION" << std::endl;
            running = false;
            return true;
        case GL_OUT_OF_MEMORY:
            std::cerr << "DSNL Error: " << fn << ": OUT_OF_MEMORY" << std::endl;
            running = false;
            return true;
        case GL_CONTEXT_LOST:
            std::cerr << "DSNL Error: " << fn << ": CONTEXT_LOST" << std::endl;
            running = false;
            return true;
        default:
            return false;
        }
    }
    void InitBuffers(){

        std::cerr << "DSNL: InitBuffers()" << std::endl;

        FontFutural font;

        string = new FontGlyphVector(font,"string");

        glGenBuffers(1,&(string->vertex_buffer));

        glBindBuffer(GL_ARRAY_BUFFER, string->vertex_buffer);

        glBufferData(GL_ARRAY_BUFFER, (string->array_length*sizeof(float)), &(string->array), GL_STATIC_DRAW);

    }
    void InitProgram(){
        std::cerr << "DSNL: InitProgram()" << std::endl;

        prog_frag = ShaderCompile(GL_FRAGMENT_SHADER,"LineFrag",LineFrag);
        if (0 != prog_frag){

            prog_vert = ShaderCompile(GL_VERTEX_SHADER,"LineVert",LineVert);
            if (0 != prog_vert){

                prog = ProgramLink(prog_frag,prog_vert,"Line");
                if (0 != prog){

                    prog_position = glGetUniformLocation(prog,"a_position");

                    fprintf(stderr,"DSNL: InitProgram( 'a_position': %d)\n",prog_position);

                    prog_camera = glGetUniformLocation(prog,"u_camera");

                    fprintf(stderr,"DSNL: InitProgram( 'u_camera': %d)\n",prog_camera);

                    prog_color = glGetUniformLocation(prog,"u_color");

                    fprintf(stderr,"DSNL: InitProgram( 'u_camera': %d)\n",prog_color);
                }
            }
        }
    }
    void MainLoop(int32_t) {

        Render();

        if (running){

            context.SwapBuffers(callback_factory.NewCallback(&DSNLInstance::MainLoop));
        }
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
