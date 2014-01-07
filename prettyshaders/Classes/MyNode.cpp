//
//  MyNode.cpp
//  prettyshaders
//
//  Created by chenliang on 14-1-7.
//
//

#include "MyNode.h"

MyNode::MyNode(float x, float y)
{
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_MyShader));
    
    p.setPoint(100, 80);
    
    CCPoint bl(x,y);
    CCPoint br(bl.x + p.x, bl.y);
    CCPoint tl(bl.x, bl.y + p.y);
    CCPoint tr(bl.x + p.x, bl.y + p.y);
    
    m_sQuad.bl.vertices = vertex3(bl.x, bl.y, 0);
    m_sQuad.br.vertices = vertex3(br.x, br.y, 0);
    m_sQuad.tl.vertices = vertex3(tl.x, tl.y, 0);
    m_sQuad.tr.vertices = vertex3(tr.x, tr.y, 0);
}

void MyNode::draw(void)
{
    CC_NODE_DRAW_SETUP();
    ccGLBlendFunc( CC_BLEND_SRC, CC_BLEND_DST );
    /*
    if (m_pobTexture != NULL)
    {
        ccGLBindTexture2D( m_pobTexture->getName() );
        ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
    }
    else
    {
        ccGLBindTexture2D(0);
        ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color );
    }
     */
    
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position  );
    
    //getShaderProgram();
    
    glUniform1f(glGetUniformLocation(m_pShaderProgram->getProgram(), "iGlobalTime"), clock());
    glUniform3f(glGetUniformLocation(m_pShaderProgram->getProgram(), "iResolution"), p.x, p.y, 0);
    
#define kQuadSize sizeof(m_sQuad.bl)
#ifdef EMSCRIPTEN
    long offset = 0;
    setGLBufferData(&m_sQuad, 4 * kQuadSize, 0);
#else
    long offset = (long)&m_sQuad;
#endif // EMSCRIPTEN
    
    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    
    /*
    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    */
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    
    CHECK_GL_ERROR_DEBUG();
}