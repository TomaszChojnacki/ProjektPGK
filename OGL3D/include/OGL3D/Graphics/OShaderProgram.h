#pragma once

/// Includujemy niezbedne naglowki z biblioteki OGL3D
#include <OGL3D/OPrerequisites.h>

/// Klasa OShaderProgram reprezentuje program shaderowy w silniku graficznym
class OShaderProgram
{
public:
    /// Konstruktor klasy OShaderProgram przyjmujacy opis programu shaderowego
    OShaderProgram(const OShaderProgramDesc& desc);

    /// Destruktor klasy OShaderProgram
    ~OShaderProgram();

    /// Metoda zwracajaca identyfikator programu shaderowego
    ui32 getId();

    /// Metoda ustawiajaca slot bufora jednorodnego dla danej zmiennej w programie shaderowym
    void setUniformBufferSlot(const char* name, ui32 slot);

private:
    /// Metoda dolaczajaca shader do programu shaderowego na podstawie sciezki do pliku i typu shadera
    void attach(const wchar_t* shaderFilePath, const OShaderType& type);

    /// Metoda linkujaca program shaderowy po dolaczeniu wszystkich shaderow
    void link();

private:
    /// Identyfikator programu shaderowego
    ui32 m_programId = 0;

    /// Identyfikatory dolaczonych shaderow (vertex i fragment shader).
    ui32 m_attachedShaders[2] = {};
};
