#pragma once

/// Includujemy niezbedne naglowki z biblioteki OGL3D
#include <OGL3D/OPrerequisites.h>

/// Klasa OVertexArrayObject reprezentuje obiekt tablicy wierzcholkow w silniku graficznym
class OVertexArrayObject
{
public:
    /// Konstruktor klasy OVertexArrayObject przyjmujacy opis bufora wierzcholkow
    OVertexArrayObject(const OVertexBufferDesc& vbDesc);

    /// Konstruktor klasy OVertexArrayObject przyjmuj¹cy opis bufora wierzcholkow i bufora indeksow
    OVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc);

    /// Destruktor klasy OVertexArrayObject
    ~OVertexArrayObject();

    /// Metoda zwracajaca identyfikator bufora wierzcholkow
    ui32 getId();

    /// Metoda zwracajaca rozmiar bufora wierzcholkow
    ui32 getVertexBufferSize();

    /// Metoda zwracajaca rozmiar pojedynczego wierzcholka w buforze
    ui32 getVertexSize();

private:
    /// Identyfikatory buforow wierzcholkow i indeksow oraz tablicy wierzcholkow
    ui32 m_vertexBufferId = 0;
    ui32 m_elementBufferId = 0;
    ui32 m_vertexArrayObjectId = 0;

    /// Opis bufora wierzcholkow
    OVertexBufferDesc m_vertexBufferData;
};
