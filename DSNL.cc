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

#include "matrix.h"

/*!
 * 
 */
class DSNLInstance : public pp::Instance {

    pp::CompletionCallbackFactory<DSNLInstance> callback_factory;
    pp::Graphics3D context;
    int32_t width;
    int32_t height;


public:

    explicit DSNLInstance(PP_Instance instance)
        : pp::Instance(instance),
          callback_factory(this),
          width(0),
          height(0)
    {
        std::fprintf(stderr,"NaCl: Instantiated module instance.\n");
    }
    virtual ~DSNLInstance()
    {}

    virtual void HandleMessage(const pp::Var& var_message) {

        std::cout << "Received message " << var_message.AsString() << std::endl;
    }
    virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]) {

        SendMessage("NaCl: Initialized module instance.");

        return true;
    }
    virtual void DidChangeView(const pp::View& view) {
        int32_t new_width = view.GetRect().width();
        int32_t new_height = view.GetRect().height();

        if (context.is_null()) {
            if (InitGL(new_width, new_height)){
                InitShaders();
                InitBuffers();
                MainLoop(0);

                SendMessage("NaCl: Initialized GL context.");
            }
            else {
                std::fprintf(stderr,"NaCl: Failed to initialize GL context.\n");
                return;
            }
        }
        else {
            int32_t result = context.ResizeBuffers(new_width, new_height);
            if (0 > result){
                std::fprintf(stderr, "NaCl: Failed to resize buffers to %d x %d.\n",new_width,new_height);
                return;
            }
            else {
                SendMessage("NaCl: Resized buffers.");
            }
        }

        width = new_width;
        height = new_height;

        glViewport(0, 0, width, height);
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
                fprintf(stderr, "NaCl: Unable to bind GL context.\n");
                context = pp::Graphics3D();
                glSetCurrentContextPPAPI(0);
                return false;
            }
        }
        else {
            std::fprintf(stderr, "NaCl: Unable to initialize GL PPAPI.\n");
            return false;
        }
    }
    void InitShaders(){
    }
    void InitBuffers(){
    }
    void Render() {
        glClearColor(0.0, 0.4, 0.7, 1);
        glClearDepthf(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
    }
    void MainLoop(int32_t) {

        Render();

        context.SwapBuffers(callback_factory.NewCallback(&DSNLInstance::MainLoop));
    }
    void SendMessage(const char* m){
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
