#pragma once

/// Includujemy niezbedne naglowki z biblioteki OGL3D
#include <OGL3D/OPrerequisites.h>

/// Klasa OUniformBuffer reprezentuje bufor jednorodny w silniku graficznym
class OUniformBuffer
{
public:
    /// Konstruktor klasy OUniformBuffer przyjmujacy opis bufora jednorodnego
    OUniformBuffer(const OUniformBufferDesc& desc);

    /// Destruktor klasy OUniformBuffer
    ~OUniformBuffer();

    /// Metoda ustawiaj¹ca dane w buforze jednorodnym
    void setData(void* data);

    /// Metoda zwracajaca identyfikator bufora jednorodnego
    ui32 getId();

private:
    /// Identyfikator bufora jednorodnego
    ui32 m_id = 0;

    /// Rozmiar bufora jednorodnego
    ui32 m_size = 0;
};
