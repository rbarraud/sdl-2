/*
Copyright (C) 2014 Payet thibault

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer():m_id(0), m_largeur(0), m_hauteur(0), m_colorBuffers(0), m_depthBufferID(0)
{
    //ctor
}
FrameBuffer::FrameBuffer(int largeur, int hauteur):m_id(0), m_largeur(largeur), m_hauteur(hauteur),
                        m_colorBuffers(0), m_depthBufferID(0)
{

}
void FrameBuffer::CreerRenderBuffer(GLuint &id, GLenum formatInterne)
{
    if(GL_TRUE == glIsRenderbuffer(id))
        glDeleteRenderbuffers(1,&id);

    glGenRenderbuffers(1,&id);

    glBindRenderbuffer(GL_RENDERBUFFER,id);

        glRenderbufferStorage(GL_RENDERBUFFER, formatInterne, m_largeur, m_hauteur);

    glBindRenderbuffer(GL_RENDERBUFFER,0);

}
void    FrameBuffer::Load()
{
    if (GL_TRUE == glIsFramebuffer(m_id))
    {
        glDeleteFramebuffers(1,&m_id);

        m_colorBuffers.clear();
    }

    // génération de l'id
    glGenFramebuffers(1,&m_id);

    // vérouillage du fbo
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
        Texture colorBuffer(m_largeur, m_hauteur, GL_RGBA, GL_RGBA, true);
        colorBuffer.LoadEmptyTexture();

        // on l'ajoute au tableau
        m_colorBuffers.push_back(colorBuffer);

        this->CreerRenderBuffer(m_depthBufferID, GL_DEPTH24_STENCIL8);

        // association du Color Buffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorBuffers[0].getID(),0);
        // association du depth et stencil buffer
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferID);

        // vérification de l'intégrité du FBO
        if (GL_FRAMEBUFFER_COMPLETE != glCheckFramebufferStatus(GL_FRAMEBUFFER))
        {
            glDeleteFramebuffers(1,&m_id);
            glDeleteRenderbuffers(1,&m_depthBufferID);

            m_colorBuffers.clear();
            GEST_ERROR("erreur le fbo est mal construit");
        }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
GLuint  FrameBuffer::GetID() const
{
    return m_id;
}
GLuint FrameBuffer::GetColorBufferID(unsigned int index) const
{
    if (index >= m_colorBuffers.size())
        GEST_ERROR("index >= m_colorBuffers.size()");
    return m_colorBuffers[index].getID();
}
int     FrameBuffer::GetLargeur() const
{
    return m_largeur;
}
int     FrameBuffer::GetHauteur() const
{
    return m_hauteur;
}
FrameBuffer::~FrameBuffer()
{
    //dtor
    glDeleteFramebuffers(1,&m_id);
    glDeleteRenderbuffers(1,&m_depthBufferID);
    m_colorBuffers.clear();
}
