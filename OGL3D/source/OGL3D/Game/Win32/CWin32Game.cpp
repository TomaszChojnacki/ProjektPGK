#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <Windows.h>

/// Metoda uruchamiajaca glown¹ petle silnika
void OGame::run()
{
    /// Wywolujemy metode onCreate inicjalizujaca gre
    onCreate();

    /// Petla glowna gry
    while (m_isRunning)
    {
        MSG msg = {};

        /// Sprawdzamy czy sa dostepne komunikaty w kolejce
        if (PeekMessage(&msg, HWND(), NULL, NULL, PM_REMOVE))
        {
            /// Jesli komunikat to WM_QUIT konczymy petle
            if (msg.message == WM_QUIT)
            {
                m_isRunning = false;
                continue;
            }
            else
            {
                /// Przetwarzamy i tlumaczymy komunikat
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        /// Wywolujemy metode onUpdateInternal aktualizujaca stan gry
        onUpdateInternal();
    }

    /// Wywolujemy metode onQuit konczaca gre
    onQuit();
}
