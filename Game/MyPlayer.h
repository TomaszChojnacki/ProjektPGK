#pragma once

/// Includujemy wszystkie niezbedne naglowki z include OGL3D
#include <OGL3D/All.h>

/// Klasa MyPlayer dziedziczy publicznie po klasie OEntity
class MyPlayer : public OEntity
{
public:
    /// Konstruktor klasy MyPlayer
    MyPlayer();

    /// Destruktor klasy MyPlayer
    ~MyPlayer();

    /// Metoda wywolywana podczas tworzenia instancji gracza
    virtual void onCreate();

    /// Metoda wywolywana podczas aktualizacji stanu gracza
    virtual void onUpdate(f32 deltaTime);

private:
    /// Zmienna przechowujaca uplywajacy czas od ostatniej aktualizacji
    f32 m_elapsedSeconds = 0.0f;

    /// Wskaznik na obiekt encji (OEntity) zwiazany z graczem.
    OEntity* m_entity = nullptr;
};
