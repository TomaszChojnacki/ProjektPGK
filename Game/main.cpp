#include "MyGame.h"
#include <iostream>

int main(void)
{
    try
    {
        /// Tworzymy obiekt klasy MyGame, ktory zarzadza silnikiem do gry 3D.
        MyGame game;

        /// Uruchamiamy petle glowna gry.
        game.run();
    }
    catch (const std::exception& e)
    {
        /// Obsluga wyjatkow: wypisze komunikat o bledzie, jesli wystapil.
        std::wclog << e.what() << std::endl;

        /// Zwracamy -1, aby sygnalizowac niepowodzenie.
        return -1;
    }

    /// Zwracamy kod sukcesu 0 po poprawnym zakonczeniu programu.
    return 0;
}
