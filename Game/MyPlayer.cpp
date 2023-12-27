#include "MyPlayer.h"

// Konstruktor klasy MyPlayer
MyPlayer::MyPlayer()
{
}

// Destruktor klasy MyPlayer
MyPlayer::~MyPlayer()
{
}

/// Metoda wywolywana podczas tworzenia instancji gracza
void MyPlayer::onCreate()
{
    /// Tworzymy nowy obiekt encji (OEntity) za pomoc¹ systemu encji
    m_entity = getEntitySystem()->createEntity<OEntity>();
}

/// Metoda wywolywana podczas aktualizacji stanu gracza
void MyPlayer::onUpdate(f32 deltaTime)
{
    /// Zwiekszamy czas ktory uplynal od ostatniej aktualizacji
    m_elapsedSeconds += deltaTime;

    /// Sprawdzamy czy istnieje encja i czy uplynal okreslony czas (3 sekundy)
    if (m_entity && m_elapsedSeconds >= 3.0f)
    {
        /// Zwolniamy zasoby encji
        m_entity->release();

        /// Ustawiamy wskaznik encji na nullptr.
        m_entity = nullptr;
    }
}
