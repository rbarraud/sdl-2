#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED
#include <SDL2/SDL.h>

class CInput
{
    public:
        CInput();
        virtual             ~CInput();
        virtual void        UpdateEvent();
        virtual bool        terminer() const;
        virtual bool        GetTouche(const SDL_Scancode touche) const;
        virtual bool        GetBoutonSouris(const Uint8 bouton) const;
        virtual bool        MotionMouse() const;
        virtual int         GetX() const;
        virtual int         GetY() const;
        virtual int         GetXRel() const;
        virtual int         GetYRel() const;
        virtual void        ShowCursor(bool reponse) const;
        virtual void        GrabCursor(bool reponse) const;

    protected:
        SDL_Event       m_event;
        bool            m_touches[SDL_NUM_SCANCODES];
        bool            m_boutonSouris[8];

        int             m_x;
        int             m_y;
        int             m_xRel;
        int             m_yRel;

        bool            m_terminer;

};


#endif // INPUT_H_INCLUDED
