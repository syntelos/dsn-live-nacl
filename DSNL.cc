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

#include "Matrix.h"
#include "FontFutural.h"

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
        std::cerr << "NaCl: Instantiated module instance." << std::endl;
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

            std::cerr << "NaCl: init (" << n << ": " << v << ")" << std::endl;
        }
        SendMessage("NaCl: Initialized module instance.");

        return true;
    }
    virtual void DidChangeView(const pp::View& view) {
        pp::Rect rect = view.GetRect();
        int32_t new_width = rect.width();
        int32_t new_height = rect.height();

        if (context.is_null()) {
            if (InitGL(new_width, new_height)){
                InitShaders();
                InitBuffers();
                MainLoop(0);
            }
            else {
                std::cerr << "NaCl: Failed to initialize GL context in change view." << std::endl;
                return;
            }
        }
        else {
            int32_t result = context.ResizeBuffers(new_width, new_height);
            if (0 > result){
                std::cerr << "NaCl: Failed to resize buffers in change view." << std::endl;
                return;
            }
        }

        width = new_width;
        height = new_height;

        glViewport(0, 0, width, height);

        SendMessage("NaCl: Initialized graphics in change view.");
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
                std::cerr << "NaCl: Unable to bind GL context." << std::endl;

                context = pp::Graphics3D();
                glSetCurrentContextPPAPI(0);
                return false;
            }
        }
        else {
            std::cerr << "NaCl: Unable to initialize GL PPAPI." << std::endl;
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
