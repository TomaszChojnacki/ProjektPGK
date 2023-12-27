#pragma once

/// Includujemy niezbedne naglowki z biblioteki OGL3D
#include <OGL3D/OPrerequisites.h>
#include <memory>
#include <chrono>

/// Deklaracje przedwstepne klas z ktorymi klasa OGame wspolpracuje
class OGraphicsEngine;
class OEntitySystem;
class OWindow;

/// Klasa OGame zarzadza glowna logika gry
class OGame
{
public:
    /// Konstruktor klasy OGame
    OGame();

    /// Wirtualny destruktor klasy OGame
    virtual ~OGame();

    /// Metoda rozpoczynajaca dzialanie gry
    void run();

    /// Metoda konczaca dzialanie gry
    void quit();

    /// Metoda zwracaj¹ca wskaznik do systemu encji
    OEntitySystem* getEntitySystem();

protected:
    /// Metoda wywolywana podczas tworzenia gry
    virtual void onCreate();

    /// Metoda wywolywana podczas aktualizacji stanu gry
    virtual void onUpdate(f32 deltaTime) {}

    /// Metoda wywolywana podczas zakonczenia gry
    virtual void onQuit();

private:
    /// Metoda wewnetrzna do aktualizacji stanu gry
    void onUpdateInternal();

protected:
    // Flaga okreslajaca czy gra jest w trakcie dzialania
    bool m_isRunning = true;

    // Unikalne wskazniki do komponentow silnika graficznego okna i systemu encji
    std::unique_ptr<OGraphicsEngine> m_graphicsEngine;
    std::unique_ptr<OWindow> m_display;
    std::unique_ptr<OEntitySystem> m_entitySystem;

    // Dodatkowe komponenty silnika graficznego 
    OVertexArrayObjectPtr m_polygonVAO;
    OUniformBufferPtr m_uniform;
    OShaderProgramPtr m_shader;

    // Zmienne pomocnicze do pomiaru czasu i skali
    std::chrono::system_clock::time_point m_previousTime;
    f32 m_scale = -3;
};
