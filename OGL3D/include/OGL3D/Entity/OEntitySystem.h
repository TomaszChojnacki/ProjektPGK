#pragma once

/// Includujemy niezbedne naglowki z biblioteki OGL3D
#include <OGL3D/OPrerequisites.h>
#include <map>
#include <set>

/// Deklaracja klay z ktorymi klasa OEntitySystem wspolpracuje
class OEntity;

/// Klasa OEntitySystem zarzadza systemem encji w grze.
class OEntitySystem
{
public:
    /// Konstruktor klasy OEntitySystem.
    OEntitySystem();

    /// Destruktor klasy OEntitySystem.
    ~OEntitySystem();

public:
    /// Metoda do tworzenia nowych instancji encji
    template <typename T>
    T* createEntity()
    {
        // Sprawdzamy, czy T dziedziczy po klasie OEntity
        static_assert(std::is_base_of<OEntity, T>::value, "T musi dzieciczyc po klasie OEntity");

        /// Generujemy unikalny identyfikator na podstawie typu T
        auto id = typeid(T).hash_code();

        /// Tworzymy nowa instancje encji typu T
        auto e = new T();

        /// Dodajemy encje do systemu encji i sprawdzamy, czy operacja sie powiodla.
        if (createEntityInternal(e, id))
            return e;

        /// Jesli coc poszlo nie tak zwracamy nullptr.
        return nullptr;
    }

private:
    /// Metoda dodajaca encje do systemu encji
    bool createEntityInternal(OEntity* entity, size_t id);

    /// Metoda usuwajaca encje z systemu encji
    void removeEntity(OEntity* entity);

    /// Metoda aktualizuj¹ca system encji
    void update(f32 deltaTime);

private:
    /// Mapa przechowujaca encje pogrupowane wedlug ich typow
    std::map<size_t, std::map<OEntity*, std::unique_ptr<OEntity>>> m_entities;

    /// Zbior przechowujacy encje do zniszczenia.
    std::set<OEntity*> m_entitiesToDestroy;

    /// Umozliwia dostep do prywatnych skladowych klas OEntity oraz OGame.
    friend class OEntity;
    friend class OGame;
};
