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
#include "Object.h"

IObject::IObject()
{

}
IObject::~IObject()
{

}
QuadObject::QuadObject()
{


    GLfloat     vertices[]  =   {   0,0,0,   0,1,0,    0,1,1,
                                    0,0,1
                                    };


    GLfloat     coordTex[]  = {  0,0 , 1,0,    1,1,
                                 0,1  };

    m_tailleCoordBytes      =   8 * sizeof(GLfloat);
    m_tailleVerticesBytes     =   12 * sizeof(GLfloat);


        glGenBuffers(1,&m_vbo);
        glGenVertexArrays(1,&m_vao);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, m_tailleVerticesBytes + m_tailleCoordBytes, 0, GL_DYNAMIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, m_tailleVerticesBytes,vertices);
            glBufferSubData(GL_ARRAY_BUFFER, m_tailleVerticesBytes, m_tailleCoordBytes, coordTex);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(2);

            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_tailleVerticesBytes));
        glBindVertexArray(0);




}
void    QuadObject::SetIDTexture(GLuint IDTexture)
{
    m_IDtexture     =   IDTexture;
}
QuadObject::~QuadObject()
{
    glDeleteBuffers(1,&m_vbo);

    glDeleteVertexArrays(1,&m_vao);
}
void        QuadObject::Show(ShaderUniformMatrix uniformMatrix, Uint32 fps)
{



    // � optimiser pour l'envoi des matrices
    glUniformMatrix4fv(uniformMatrix.modelviewLocation, 1, GL_FALSE, glm::value_ptr(uniformMatrix.modelview));
    glUniformMatrix4fv(uniformMatrix.projectionLocation, 1, GL_FALSE, glm::value_ptr(uniformMatrix.projection));

    glm::mat4 mvp = uniformMatrix.projection * uniformMatrix.modelview;
    glUniformMatrix4fv(uniformMatrix.mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));

        glBindVertexArray(m_vao);
            glBindTexture(GL_TEXTURE_2D, m_IDtexture);
                glDrawArrays(GL_TRIANGLE_FAN,0,4);

            glBindTexture(GL_TEXTURE_2D,0);
        glBindVertexArray(0);


}
MD2Object::MD2Object(CEntity *entityModel)
{
    m_entity            =   entityModel;
}
MD2Object::~MD2Object()
{

}
void    MD2Object::SetAnimation(int start, int fin, bool animated)
{
    m_start             =   start;
    m_end               =   fin;
    m_animated          =   animated;
}
void    MD2Object::Show(ShaderUniformMatrix uniformMatrix, Uint32 fps)
{
    // � optimiser pour l'envoi des matrices
    glUniformMatrix4fv(uniformMatrix.modelviewLocation, 1, GL_FALSE, glm::value_ptr(uniformMatrix.modelview));
    glUniformMatrix4fv(uniformMatrix.projectionLocation, 1, GL_FALSE, glm::value_ptr(uniformMatrix.projection));

    glm::mat4 mvp = uniformMatrix.projection * uniformMatrix.modelview;
    glUniformMatrix4fv(uniformMatrix.mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));

    m_entity->Animate(m_start,m_end,10.0/fps);
    m_entity->DrawEntity(-1, m_animated, false);
}
MirrorObject::MirrorObject(GLsizei taille)
{

}
MirrorObject::~MirrorObject()
{

}
void  	MirrorObject::Begin()
{

}
void    MirrorObject::End()
{


}
void    MirrorObject::Show(ShaderUniformMatrix m, Uint32 fps)
{

}
