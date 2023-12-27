#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <glad/glad.h>

/// Konstruktor Inicjalizuje obiekt tablicy wierzcholkow na podstawie opisu bufora wierzcholkow
OVertexArrayObject::OVertexArrayObject(const OVertexBufferDesc& vbDesc)
{
    /// Sprawdza czy opis bufora wierzcholkow zawiera wymagane dane
    if (!vbDesc.listSize) OGL3D_ERROR("OVertexArrayObject | listSize is NULL");
    if (!vbDesc.vertexSize) OGL3D_ERROR("OVertexArrayObject | vertexSize is NULL");
    if (!vbDesc.verticesList) OGL3D_ERROR("OVertexArrayObject | verticesList is NULL");

    /// Generuje identyfikator dla obiektu tablicy wierzcholkow
    glGenVertexArrays(1, &m_vertexArrayObjectId);
    glBindVertexArray(m_vertexArrayObjectId);

    /// Generuje identyfikator dla bufora wierzcholkow i ustawia go jako biezacy
    glGenBuffers(1, &m_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);

    /// Kopiuje dane do bufora wierzcholkow
    glBufferData(GL_ARRAY_BUFFER, vbDesc.vertexSize * vbDesc.listSize, vbDesc.verticesList, GL_STATIC_DRAW);

    /// Petla konfigurujaca atrybuty wierzcholkow
    for (ui32 i = 0; i < vbDesc.attributesListSize; i++)
    {
        /// Konfiguracja atrybutu wierzcholka
        glVertexAttribPointer(
            i,
            vbDesc.attributesList[i].numElements,  /// Liczba elementow w atrybucie dla wspolrzednych XYZ
            GL_FLOAT,  /// Typ danych atrybutu
            GL_FALSE,  /// w tym przypadku wartosci wierzcholkow nie sa normalizowane
            vbDesc.vertexSize,  /// Rozmiar pojedynczego wierzcholka w bajtach
            (void*)((i == 0) ? 0 : vbDesc.attributesList[i - 1].numElements * sizeof(f32))  /// Przesuniecie wierzcholka w bajtach
        );

        /// Wlaczenie atrybutu wierzcholka o numerze i
        glEnableVertexAttribArray(i);
    }


    /// Odlacza obiekt tablicy wierzcholkow
    glBindVertexArray(0);

    /// Zapamietuje informacje o buforze wierzcholkow
    m_vertexBufferData = vbDesc;
}

/// Konstruktor przeciazony inicjalizuje obiekt tablicy wierzcholkow na podstawie opisu bufora wierzcholkow i bufora indeksow
OVertexArrayObject::OVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc) : OVertexArrayObject(vbDesc)
{
    /// Sprawdza czy opis bufora indeksow zawiera wymagane dane
    if (!ibDesc.listSize) OGL3D_ERROR("OVertexArrayObject | listSize is NULL");
    if (!ibDesc.indicesList) OGL3D_ERROR("OVertexArrayObject | indicesList is NULL");

    /// Ustawia biezacy obiekt tablicy wierzcholkow
    glBindVertexArray(m_vertexArrayObjectId);

    /// Generuje identyfikator dla bufora indeksow i ustawia go jako biezacy
    glGenBuffers(1, &m_elementBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);

    /// Kopiuje dane do bufora indeksow
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibDesc.listSize, ibDesc.indicesList, GL_STATIC_DRAW);

    /// Odlacza obiekt tablicy wierzcholkow
    glBindVertexArray(0);
}

/// Destruktor Zwalnia zasoby buforow
OVertexArrayObject::~OVertexArrayObject()
{
    glDeleteBuffers(1, &m_elementBufferId);
    glDeleteBuffers(1, &m_vertexBufferId);
    glDeleteVertexArrays(1, &m_vertexArrayObjectId);
}

/// Pobiera identyfikator obiektu tablicy wierzcholkow
ui32 OVertexArrayObject::getId()
{
    return m_vertexArrayObjectId;
}

/// Pobiera rozmiar bufora wierzcholkow
ui32 OVertexArrayObject::getVertexBufferSize()
{
    return m_vertexBufferData.listSize;
}

/// Pobiera rozmiar pojedynczego wierzcholka
ui32 OVertexArrayObject::getVertexSize()
{
    return m_vertexBufferData.vertexSize;
}
