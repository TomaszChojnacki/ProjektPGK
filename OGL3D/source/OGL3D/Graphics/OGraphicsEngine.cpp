#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <glad/glad.h>

/// Tworzenie obiektu VertexArrayObject z opisem bufora wierzcholkow
OVertexArrayObjectPtr OGraphicsEngine::createVertexArrayObject(const OVertexBufferDesc& vbDesc)
{
    return std::make_shared<OVertexArrayObject>(vbDesc);
}

/// Tworzenie obiektu VertexArrayObject z opisem bufora wierzcholkow i bufora indeksow
OVertexArrayObjectPtr OGraphicsEngine::createVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc)
{
    return std::make_shared<OVertexArrayObject>(vbDesc, ibDesc);
}

/// Tworzenie obiektu UniformBuffer z opisem bufora jednorodnego
OUniformBufferPtr OGraphicsEngine::createUniformBuffer(const OUniformBufferDesc& desc)
{
    return std::make_shared<OUniformBuffer>(desc);
}

/// Tworzenie obiektu ShaderProgram z opisem sciezek do plikow shaderow
OShaderProgramPtr OGraphicsEngine::createShaderProgram(const OShaderProgramDesc& desc)
{
    return std::make_shared<OShaderProgram>(desc);
}

/// Czyszczenie bufora kolorow podanym kolorem
void OGraphicsEngine::clear(const OVec4& color)
{
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

/// Ustawienie trybu usuwania tylnych lub przednich lub obu scian trojkatow
void OGraphicsEngine::setFaceCulling(const OCullType& type)
{
    auto cullType = GL_BACK;

    if (type == OCullType::FrontFace) cullType = GL_FRONT;
    else if (type == OCullType::BackFace) cullType = GL_BACK;
    else if (type == OCullType::Both) cullType = GL_FRONT_AND_BACK;

    glEnable(GL_CULL_FACE);
    glCullFace(cullType);
}

/// Ustawienie kierunku zawijania trojkatow zgodnie z ruchem wskazowek zegara lub przeciwnie
void OGraphicsEngine::setWindingOrder(const OWindingOrder& order)
{
    auto orderType = GL_CW;

    if (order == OWindingOrder::ClockWise) orderType = GL_CW;
    else if (order == OWindingOrder::CounterClockWise) orderType = GL_CCW;

    glFrontFace(orderType);
}

/// Ustawienie obszaru widzenia viewport
void OGraphicsEngine::setViewport(const ORect& size)
{
    glViewport(size.left, size.top, size.width, size.height);
}

/// Ustawienie aktualnego obiektu VertexArrayObject
void OGraphicsEngine::setVertexArrayObject(const OVertexArrayObjectPtr& vao)
{
    glBindVertexArray(vao->getId());
}

/// Ustawienie bufora jednorodnego na danym slocie
void OGraphicsEngine::setUniformBuffer(const OUniformBufferPtr& buffer, ui32 slot)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer->getId());
}

/// Ustawienie aktualnego obiektu ShaderProgram
void OGraphicsEngine::setShaderProgram(const OShaderProgramPtr& program)
{
    glUseProgram(program->getId());
}

/// Rysowanie trojkatow na podstawie liczby wierzcholkow i przesuniecia
void OGraphicsEngine::drawTriangles(const OTriangleType& triangleType, ui32 vertexCount, ui32 offset)
{
    /// Okreslenie rodzaju rysowania trojkatow (List lub Strip)
    auto glTriType = GL_TRIANGLES;

    switch (triangleType)
    {
    case OTriangleType::TriangleList: { glTriType = GL_TRIANGLES; break; }  /// Jesli lista trojkatow, ustaw GL_TRIANGLES
    case OTriangleType::TriangleStrip: { glTriType = GL_TRIANGLE_STRIP; break; }  /// Jesli strip/pas trojkatow, ustaw GL_TRIANGLE_STRIP
    }

    /// Wywolanie funkcji rysujacej trojkaty z wybranym trybem i danymi parametrami
    glDrawArrays(glTriType, offset, vertexCount);
}


/// Rysowanie trojkatow na podstawie liczby indeksow
void OGraphicsEngine::drawIndexedTriangles(const OTriangleType& triangleType, ui32 indicesCount)
{
    /// Okreslenie rodzaju rysowania trojkatow List lub Strip
    auto glTriType = GL_TRIANGLES;

    switch (triangleType)
    {
    case OTriangleType::TriangleList: { glTriType = GL_TRIANGLES; break; }  /// Jesli lista trojkatow, ustaw GL_TRIANGLES
    case OTriangleType::TriangleStrip: { glTriType = GL_TRIANGLE_STRIP; break; }  /// Jeœli Strip/pas trojkatow, ustaw GL_TRIANGLE_STRIP
    }

    /// Wywolanie funkcji rysujacej trojkaty z indeksami i danymi parametrami
    glDrawElements(glTriType, indicesCount, GL_UNSIGNED_INT, nullptr);
}

