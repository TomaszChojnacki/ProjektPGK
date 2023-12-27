#include "MyGame.h"

/// Konstruktor klasy MyGame
MyGame::MyGame()
{
}

/// Destruktor klasy MyGame
MyGame::~MyGame()
{
}

/// Metoda wywolywana podczas tworzenia gry
void MyGame::onCreate()
{
    /// Wywolujemy metode onCreate z klasy bazowej OGame
    OGame::onCreate();

    // Tworzymy obiekt gracza (MyPlayer) przy uzyciu systemu encji
    m_player = getEntitySystem()->createEntity<MyPlayer>();
}

/// Metoda wywolywana podczas aktualizacji gry
void MyGame::onUpdate(f32 deltaTime)
{
    /// Aktualizujemy logike gry w silniku
}
