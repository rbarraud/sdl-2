#include "Window.h"

Window::Window(const std::string &title, unsigned int width, unsigned int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::string ("error sdl init video");
	m_vsWindow.push_back(SingleWindow());
	m_vsWindow.back().title	=	title;
	m_vsWindow.back().width	=	width;
	m_vsWindow.back().height	=	height;
	m_vsWindow.back().pWindow =	fullscreen?
                            SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
							SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL) :
                            SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
							SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
}
SDL_GLContext   Window::CreateContext(unsigned int numWindow)
{
    if (numWindow >= m_vsWindow.size())
        throw GEST_ERROR("error unknow indice");
    return SDL_GL_CreateContext(m_vsWindow[numWindow].pWindow);
}
void            Window::SwapWindow(unsigned int numWindow)
{
    if (numWindow >= m_vsWindow.size())
        throw GEST_ERROR("error unknow indice");
    SDL_GL_SwapWindow(m_vsWindow[numWindow].pWindow);
}
Window::~Window()
{
    for (unsigned int i=0 ; i < m_vsWindow.size(); ++i)
        SDL_DestroyWindow(m_vsWindow[i].pWindow);
    m_vsWindow.clear();

}
