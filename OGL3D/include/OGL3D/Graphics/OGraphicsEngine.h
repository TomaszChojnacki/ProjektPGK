#pragma once

/// Includujemy niezbedne naglowki z biblioteki OGL3D.
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Math/OVec4.h>
#include <OGL3D/Math/ORect.h>

/// Klasa OGraphicsEngine odpowiada za zarzadzanie silnikiem graficznym
class OGraphicsEngine
{
public:
    /// Konstruktor klasy OGraphicsEngine
    OGraphicsEngine();

    /// Destruktor klasy OGraphicsEngine
    ~OGraphicsEngine();

public:
    /// Metoda tworzaca obiekt OVertexArrayObject na podstawie bufora wierzcholkow
    OVertexArrayObjectPtr createVertexArrayObject(const OVertexBufferDesc& vbDesc);

    /// Metoda tworzaca obiekt OVertexArrayObject na podstawie buforow wierzcholkow i indeksow
    OVertexArrayObjectPtr createVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc);

    /// Metoda tworzaca obiekt OUniformBuffer na podstawie bufora
    OUniformBufferPtr createUniformBuffer(const OUniformBufferDesc& desc);

    /// Metoda tworzaca obiekt OShaderProgram na podstawie programu shaderowego
    OShaderProgramPtr createShaderProgram(const OShaderProgramDesc& desc);

public:
    /// Metoda czyszczaca ekran danym kolorem
    void clear(const OVec4& color);

    /// Metoda ustawiajaca rodzaj odrzucania scian
    void setFaceCulling(const OCullType& type);

    /// Metoda ustawiajaca kolejnosc zwijania trojkatow
    void setWindingOrder(const OWindingOrder& order);

    /// Metoda ustawiajaca widokport
    void setViewport(const ORect& size);

    /// Metoda ustawiajaca aktualny obiekt OVertexArrayObject
    void setVertexArrayObject(const OVertexArrayObjectPtr& vao);

    /// Metoda ustawiajaca aktualny bufor jednorodny
    void setUniformBuffer(const OUniformBufferPtr& buffer, ui32 slot);

    /// Metoda ustawiajaca aktualny program shaderowy
    void setShaderProgram(const OShaderProgramPtr& program);

    /// Metoda rysujaca trojkaty na ekranie
    void drawTriangles(const OTriangleType& triangleType, ui32 vertexCount, ui32 offset);

    /// Metoda rysujaca trojkaty na ekranie z uzyciem indeksow
    void drawIndexedTriangles(const OTriangleType& triangleType, ui32 indicesCount);
};
