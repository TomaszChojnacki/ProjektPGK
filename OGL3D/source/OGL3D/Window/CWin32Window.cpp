#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Game/OGame.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <Windows.h>
#include <assert.h>

/// Okreslenie procedury okna
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
    {
        OWindow* window = (OWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        /// Obsluga zdarzenia zniszczenia okna zamkniecie aplikacji
        break;
    }
    case WM_CLOSE:
    {
        PostQuitMessage(0);
        /// Obsluga zdarzenia zamkniecia okna nacisniecie przycisku zamkniecia
        break;
    }
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam); /// Obslugiwanie standardowych procedur okna 
    }
    return NULL;
}

/// Konstruktor okna
OWindow::OWindow()
{
    /// Inicjalizacja struktury WNDCLASSEX
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX); /// Rozmiar struktury w bajtach 
    wc.lpszClassName = L"OGL3DWindow"; /// Nazwa kalsy okna 
    wc.lpfnWndProc = &WndProc; /// Wskaznik na procedure obslugi okna 
    wc.style = CS_OWNDC; /// Styl rysowania okna, kazde okno w zaleznosci od systemu bedzie mialo wlasny wyglad 

    /// Rejestracja klasy okna
    auto classId = RegisterClassEx(&wc);
    assert(classId); /// Sprawdza czy rejestracja klasy zakonczyla sie pomyslnie

    /// Ustalenie rozmiaru okna
    RECT rc = { 0,0,1024,768 };
    AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

    /// Tworzenie okna
    m_handle = CreateWindowEx(NULL, MAKEINTATOM(classId), L"Tomasz Chojnacki | Maciej Bernatek | Przemyslaw Palka | OpenGL 3D Game 2ID11A",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, NULL, NULL); /// naglowek 

    assert(m_handle); /// Sprawdza czy rejestracja klasy zakonczyla sie pomyslnie

    /// Ustawienie wskaznika do biezacego obiektu okna jako dane uzytkownika
    SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

    /// Wyswietlenie i zaktualizowanie okna
    ShowWindow((HWND)m_handle, SW_SHOW);
    UpdateWindow((HWND)m_handle);

    /// Tworzenie kontekstu renderowania OpenGL
    auto hDC = GetDC(HWND(m_handle));

    /// Atrybuty formatu pikseli
    int pixelFormatAttributes[] = {
     WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,                   /// Rysowanie do okna
     WGL_SUPPORT_OPENGL_ARB, GL_TRUE,                   /// Obs³uga OpenGL
     WGL_DOUBLE_BUFFER_ARB, GL_TRUE,                    /// Podwójne buforowanie
     WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,   /// Pelna akceleracja sprzetowa
     WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,             /// Typ pikseli RGBA Red, Green, Blue, Alpha
     WGL_COLOR_BITS_ARB, 32,                            /// Liczba bitow na kolor
     WGL_DEPTH_BITS_ARB, 24,                            /// Liczba bitow na bufor glebokosci
     WGL_STENCIL_BITS_ARB, 8,                           /// Liczba bitow na bufor szablonowy
     0                                                  /// Koniec listy
    };

    int pixelFormat = 0;
    UINT numFormats = 0;

    /// Wybor formatu pikseli zgodnego z zdefiniowanymi atrybutami
    wglChoosePixelFormatARB(hDC, pixelFormatAttributes, nullptr, 1, &pixelFormat, &numFormats);
    assert(numFormats);

    PIXELFORMATDESCRIPTOR pixelFormatDesc = {};

    /// Pobranie informacji o wybranym formacie pikseli
    DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDesc);

    /// Ustawienie wybranego formatu pikseli
    SetPixelFormat(hDC, pixelFormat, &pixelFormatDesc);


    /// Atrybuty kontekstu OpenGL
    int openGLAttributes[] = 
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,     /// Ustawienie glownej wersji kontekstu OpenGL na 4
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,     /// Ustawienie mniejszej wersji kontekstu OpenGL na 6
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, /// Ustawienie profilu na rdzeniowy core
        0
    };

    m_context = wglCreateContextAttribsARB(hDC, 0, openGLAttributes); /// przeslanie kontekstu
    assert(m_context); /// Sprawdza czy rejestracja klasy zakonczyla sie pomyslnie
}

/// Destruktor okna
OWindow::~OWindow()
{
    /// Usuniecie kontekstu renderowania OpenGL
    wglDeleteContext(HGLRC(m_context));
    /// Usuniecie okna
    DestroyWindow(HWND(m_handle));
}

/// Pobieranie rozmiaru okna
ORect OWindow::getInnerSize()
{
    RECT rc = {};
    GetClientRect((HWND)m_handle, &rc); /// Uzyskanie wymiarow obszaru klienta okna
    return ORect(rc.right - rc.left, rc.bottom - rc.top); /// Zwrocenie rozmiaru w postaci struktury ORect
}


/// Ustawienie okna jako biezacego kontekstu renderowania
void OWindow::makeCurrentContext()
{
    wglMakeCurrent(GetDC(HWND(m_handle)), HGLRC(m_context));
}

/// Wysylanie biezacego bufora klatki do wyswietlenia
void OWindow::present(bool vsync)
{
    wglSwapIntervalEXT(vsync); /// Ustawianie wymiany VSync
    wglSwapLayerBuffers(GetDC(HWND(m_handle)), WGL_SWAP_MAIN_PLANE); /// Wymiana buforow i wyswietlenie
}

