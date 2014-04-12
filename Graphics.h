#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include "Window.h"
// GLEW for all platform
#include <GL/glew.h>

#include <iostream>
#include "Error.h"
#include "DebugGL.h"


class CGraphics
{
    public:
        CGraphics(GLuint width=320, GLuint height=240, bool fullscreen=false, const std::string &title="default",
                  GLuint bpp=32, GLuint aa=2, GLuint major=4, GLuint minor=4 );

        virtual         ~CGraphics();
        virtual void    SwapWindow();

    protected:
        Window*         m_pWindow;
        SDL_GLContext   m_glContext;
        // param�tre opengl
        GLuint          m_bpp;
        GLuint          m_aa;

};

#endif // GRAPHICS_H_INCLUDED
