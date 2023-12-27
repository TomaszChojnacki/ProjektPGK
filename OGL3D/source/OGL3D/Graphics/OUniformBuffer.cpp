#include <OGL3D/Graphics/OUniformBuffer.h>
#include <glad/glad.h>

/// Konstruktor tworzy i inicjalizuje bufor jednorodny
OUniformBuffer::OUniformBuffer(const OUniformBufferDesc& desc)
{
    /// Generuje jeden bufor i pobiera jego identyfikator
    glGenBuffers(1, &m_id);

    /// Ustawia bufor jako biezacy bufor jednorodny
    glBindBuffer(GL_UNIFORM_BUFFER, m_id);

    /// Alokuje pamiec dla bufora jednorodnego i inicjalizuje go zerami
    glBufferData(GL_UNIFORM_BUFFER, desc.size, nullptr, GL_STATIC_DRAW);

    /// Odlacza bufor jednorodny
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    /// Zapamietuje rozmiar bufora
    m_size = desc.size;
}

/// Destruktor zwalnia zasoby bufora jednorodnego
OUniformBuffer::~OUniformBuffer()
{
    /// Usuwa bufor jednorodny
    glDeleteBuffers(1, &m_id);
}

/// Ustawia dane bufora jednorodnego
void OUniformBuffer::setData(void* data)
{
    /// Ustawia bufor jednorodny jako biezacy
    glBindBuffer(GL_UNIFORM_BUFFER, m_id);

    /// Kopiuje dane do bufora jednorodnego
    glBufferSubData(GL_UNIFORM_BUFFER, 0, m_size, data);

    /// Odlacza bufor jednorodny
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

/// Pobiera identyfikator bufora jednorodnego
ui32 OUniformBuffer::getId()
{
    return m_id;
}
