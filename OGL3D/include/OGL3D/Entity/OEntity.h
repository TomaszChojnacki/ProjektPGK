#pragma once

/// Includujemy niezbedne naglowki z biblioteki OGL3D
#include <OGL3D/OPrerequisites.h>

/// Deklaracja klay z ktorymi klasa OEntity wspolpracuje
class OEntitySystem;

/// Klasa OEntity reprezentuje podstawowa jednostke w systemie encji
class OEntity
{
public:
    /// Konstruktor klasy OEntity
    OEntity();

    /// Wirtualny destruktor klasy OEntity
    virtual ~OEntity();

    /// Metoda do zwalniania zasobow zwiazanych z encja
    void release();

    /// Metoda zwracaj¹ca wskaznik do systemu encji do ktorego nalezy encja
    OEntitySystem* getEntitySystem();

protected:
    /// Metoda wywolywana podczas tworzenia instancji encji
    virtual void onCreate() {}

    /// Metoda wywolywana podczas aktualizacji stanu encji
    virtual void onUpdate(f32 deltaTime) {}

protected:
    /// Unikalny identyfikator encji
    size_t m_id = 0;

    /// Wskaznik do systemu encji do ktorego nalezy encja
    OEntitySystem* m_entitySystem = nullptr;

    /// Umozliwia dostep do prywatnych skladowych klasy OEntitySystem
    friend class OEntitySystem;
};
