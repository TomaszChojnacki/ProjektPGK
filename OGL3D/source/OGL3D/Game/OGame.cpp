#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Math/OMat4.h>
#include <OGL3D/Math/OVec3.h>
#include <OGL3D/Math/OVec2.h>
#include <OGL3D/Entity/OEntitySystem.h>


/// Struktura przechowujaca dane jednorodne dla shadera
struct UniformData
{
	OMat4 world;
	OMat4 projection;
};

/// Struktura reprezentujaca wierzcholek
struct Vertex
{
	OVec3 position;
	OVec2 texcoord;
};

/// Konstruktor klasy OGame
OGame::OGame()
{
	/// Inicjalizacja elementow gry
	m_graphicsEngine = std::make_unique<OGraphicsEngine>();
	m_display = std::make_unique<OWindow>();
	m_entitySystem = std::make_unique<OEntitySystem>();

	/// Ustawienie biezacego kontekstu okna
	m_display->makeCurrentContext();

	/// Ustawienie widoku renderingu na rozmiar okna
	m_graphicsEngine->setViewport(m_display->getInnerSize());
}

/// Destruktor klasy OGame
OGame::~OGame()
{
}

/// Metoda wywolywana przy inicjalizacji gry
void OGame::onCreate()
{
	/// Definicja pozycji wierzcholkow i tekstur
	OVec3 positionsList[] =
	{
		/// Widok od przodu 
		OVec3(-0.5f,-0.5f,-0.5f),
		OVec3(-0.5f,0.5f,-0.5f),
		OVec3(0.5f,0.5f,-0.5f),
		OVec3(0.5f,-0.5f,-0.5f),

		/// Widok od tylu
		OVec3(0.5f,-0.5f,0.5f),
		OVec3(0.5f,0.5f,0.5f),
		OVec3(-0.5f,0.5f,0.5f),
		OVec3(-0.5f,-0.5f,0.5f)
	};

	/// Lista wspolrzednych 
	OVec2 texcoordsList[] =
	{
		OVec2(0,0),
		OVec2(0,1),
		OVec2(1,0),
		OVec2(1,1)
	};

	/// Definicja wierzcholkow
	Vertex verticesList[] =
	{
		/// Przednia strona
		{ positionsList[0],texcoordsList[1] },
		{ positionsList[1],texcoordsList[0] },
		{ positionsList[2],texcoordsList[2] },
		{ positionsList[3],texcoordsList[3] },

		/// Tyln strona
		{ positionsList[4],texcoordsList[1] },
		{ positionsList[5],texcoordsList[0] },
		{ positionsList[6],texcoordsList[2] },
		{ positionsList[7],texcoordsList[3] },

		/// Gorna strona
		{ positionsList[1],texcoordsList[1] },
		{ positionsList[6],texcoordsList[0] },
		{ positionsList[5],texcoordsList[2] },
		{ positionsList[2],texcoordsList[3] },

		/// Dolna strona
		{ positionsList[7],texcoordsList[1] },
		{ positionsList[0],texcoordsList[0] },
		{ positionsList[3],texcoordsList[2] },
		{ positionsList[4],texcoordsList[3] },

		/// Prawa strona
		{ positionsList[3],texcoordsList[1] },
		{ positionsList[2],texcoordsList[0] },
		{ positionsList[5],texcoordsList[2] },
		{ positionsList[4],texcoordsList[3] },

		/// Lewa strona
		{ positionsList[7],texcoordsList[1] },
		{ positionsList[6],texcoordsList[0] },
		{ positionsList[1],texcoordsList[2] },
		{ positionsList[0],texcoordsList[3] }
	};

	/// Definicja indeksow
	ui32 indicesList[] =
	{
		/// Przednia
		0,1,2,
		2,3,0,

		/// Tylna
		4,5,6,
		6,7,4,

		/// Gorna
		8,9,10,
		10,11,8,

		/// Dolna
		12,13,14,
		14,15,12,

		/// Prawa
		16,17,18,
		18,19,16,

		/// Lewa
		20,21,22,
		22,23,20
	};

	/// Definicja atrybutow wierzcholkow
	OVertexAttribute attribsList[] = {
		sizeof(OVec3) / sizeof(f32), /// Pozycja wektora
		sizeof(OVec2) / sizeof(f32) /// Pozycja wektora
	};

	// Tworzenie obiektu VertexArrayObject
	m_polygonVAO = m_graphicsEngine->createVertexArrayObject(
		{
			(void*)verticesList,							/// Wskaznik do danych wierzcholkow
			sizeof(Vertex),									/// Rozmiar pojedynczego wierzcholka
			sizeof(verticesList) / sizeof(Vertex),			/// Ilosc wierzcholkow

			attribsList,									/// Lista atrybutow wierzcholka
			sizeof(attribsList) / sizeof(OVertexAttribute)	/// Ilosc atrybutow
		},
		{
		(void*)indicesList,									/// Wskaznik do danych indeksow
		sizeof(indicesList)									/// Rozmiar indeksow
		}
	);


	/// Tworzenie bufora jednorodnego dla shadera
	m_uniform = m_graphicsEngine->createUniformBuffer({
		sizeof(UniformData)
		});

	/// Tworzenie programu shaderowego
	m_shader = m_graphicsEngine->createShaderProgram(
		{
			L"Assets/Shaders/BasicShader.vert",
			L"Assets/Shaders/BasicShader.frag"
		});										/// Odwolanie do plikow shaderowych

	/// Ustawienie slotu bufora jednorodnego w programie shaderowym
	m_shader->setUniformBufferSlot("UniformData", 0);
}

/// Metoda wywolywana w kazdej klatce gry
void OGame::onUpdateInternal()
{
	/// Obliczanie czasu delta
	auto currentTime = std::chrono::system_clock::now();
	auto elapsedSeconds = std::chrono::duration<double>();
	if (m_previousTime.time_since_epoch().count())
		elapsedSeconds = currentTime - m_previousTime;
	m_previousTime = currentTime;

	auto deltaTime = (f32)elapsedSeconds.count();

	/// Aktualizacja logiki gry i systemu encji
	onUpdate(deltaTime);				/// Wywolanie metody onUpdate z dostosowanym czasem delta
	m_entitySystem->update(deltaTime);	/// Aktualizacja systemu encji

	/// Animacja obrotu i skali obiektu
	m_scale += 1.14f * deltaTime;
	auto currentScale = abs(sin(m_scale));

	/// Inicjalizacja macierzy transformacji obiektu
	OMat4 world, projection, temp;

	/// Transformacje obiektu
	temp.setIdentity();
	temp.setScale(OVec3(1, 1, 1)); /// Skala
	world *= temp;

	temp.setIdentity();
	temp.setRotationZ(m_scale); /// Zmiana kierunku Z
	world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_scale);  /// Zmiana kierunku y
	world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_scale);  /// Zmiana kierunku x
	world *= temp;

	temp.setIdentity();
	temp.setTranslation(OVec3(0, 0, 0)); /// Pozostawienie obiektu bez zadnej translacji 
	world *= temp;

	/// Ustawienia wyswietlanego obszaru "kamera"
	auto displaySize = m_display->getInnerSize();
	projection.setOrthoLH(displaySize.width * 0.004f, displaySize.height * 0.004f, 0.01f, 100.0f);

	/// Dane jednorodne do przekazania do shadera
	UniformData data = { world, projection };
	m_uniform->setData(&data);

	/// Czyszczenie bufora kolorow
	m_graphicsEngine->clear(OVec4(0, 0, 0, 1));

	/// Ustawienia renderingu
	m_graphicsEngine->setFaceCulling(OCullType::BackFace);
	m_graphicsEngine->setWindingOrder(OWindingOrder::ClockWise);
	m_graphicsEngine->setVertexArrayObject(m_polygonVAO);
	m_graphicsEngine->setUniformBuffer(m_uniform, 0);
	m_graphicsEngine->setShaderProgram(m_shader);

	/// Rysowanie obiektu
	m_graphicsEngine->drawIndexedTriangles(OTriangleType::TriangleList, 36);

	/// Wyswietlanie renderingu
	m_display->present(false);
}


/// Metoda wywolywana przy zakonczeniu gry
void OGame::onQuit()
{
}

/// Metoda konczaca gre
void OGame::quit()
{
	m_isRunning = false;
}

/// Pobieranie wskaznika do systemu encji
OEntitySystem* OGame::getEntitySystem()
{
	return m_entitySystem.get();
}
