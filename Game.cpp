#include "Game.h"
Game::Game()
{
    // plus tard on utilisera un fichier
    m_graphics  =   new CGraphics(1600,900,true,"game engine",32,2,
                                  3,2);
    m_input     =   new CInput;

}
int     Game::run()
{
    CubeObject  object;
    CMD2Model   model;
    CEntity     entity;
    CScene      scene;
    Texture     texture;
    texture.setFilename("./data/texture/512x512/tiles_ctf05r.jpg");
    texture.load();

    //
    model.LoadModel("./data/md2/cobra/cobra.md2");
    model.LoadTexture("./data/md2/cobra/cobra.jpg");
    model.LoadVBO();
    entity.SetModel(&model);
    entity.SetScale(0.1);
    MD2Object   md2Object(&entity);
    md2Object.SetAnimation(0,10,true);

    //m_input->GrabCursor(true);    // ne fonctionne pas bien
    m_input->ShowCursor(false);
    //scene.AttachObject(&object); // on ne s'occupe plus du cube
    object.SetIDTexture(texture.getID());
    scene.AttachObject(&md2Object);
    scene.AttachInput(m_input);
    Uint32 framerate = (1000/50);
    Uint32 debutBoucle(0), elapsed(0), finBoucle(0);
    while (!m_input->terminer())
    {

        debutBoucle =   SDL_GetTicks();
        m_input->UpdateEvent();

        glClearColor(200/255.0,200/255.0,200/255.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.Show(elapsed);

        m_graphics->SwapWindow();

        finBoucle   =   SDL_GetTicks();
        elapsed =   finBoucle - debutBoucle;
        if (elapsed < framerate)
            SDL_Delay(framerate - elapsed);
        if (m_input->GetTouche(SDL_SCANCODE_ESCAPE))
            break;
        elapsed =   SDL_GetTicks() - debutBoucle;
    }

    return 0;
}
Game::~Game()
{
    delete m_graphics;
    delete m_input;
    SDL_Quit();
}
