#pragma once

/// Includujemy naglowki zwiazane z obsluga wskaznikow
#include <memory>

/// Includujemy naglowki zwiazane z operacjami strumieniowymi
#include <sstream>

/// Includujemy naglowki zwiazane z operacjami wejscia/wyjscia
#include <iostream>

/// Includujemy naglowki zwiazane z obsluga bledow i wyjatkow
#include <stdexcept>

/// Deklarujemy klasy aby mozna bylo uzywac ich wskaznikow
class OVertexArrayObject;
class OUniformBuffer;
class OShaderProgram;

/// Deklarujemy wskazniki dla klas
typedef std::shared_ptr<OVertexArrayObject> OVertexArrayObjectPtr;
typedef std::shared_ptr<OUniformBuffer> OUniformBufferPtr;
typedef std::shared_ptr<OShaderProgram> OShaderProgramPtr;

/// Deklarujemy typy danych liczbowych
typedef float f32;
typedef int i32;
typedef unsigned int ui32;

/// Struktura reprezentujaca atrybut wierzcholka
struct OVertexAttribute
{
	ui32 numElements = 0;
};

/// Struktura opisujaca bufor wierzcholkow
struct OVertexBufferDesc
{
	void* verticesList = nullptr;
	ui32 vertexSize = 0;
	ui32 listSize = 0;

	OVertexAttribute* attributesList = nullptr;
	ui32 attributesListSize = 0;
};

/// Struktura opisujaca bufor indeksow
struct OIndexBufferDesc
{
	void* indicesList = nullptr;
	ui32 listSize = 0;
};

/// Struktura opisujaca program shaderowy
struct OShaderProgramDesc
{
	const wchar_t* vertexShaderFilePath;
	const wchar_t* fragmentShaderFilePath;
};

/// Struktura opisujaca bufor jednorodny
struct OUniformBufferDesc
{
	ui32 size = 0;
};

/// Enumeracja okreslajaca typ trojkatow
enum class OTriangleType
{
	TriangleList = 0,
	TriangleStrip
};

/// Enumeracja okreslajaca typ eliminacji scian
enum class OCullType
{
	BackFace = 0,
	FrontFace,
	Both
};

/// Enumeracja okreslajaca kierunek zwijania trojkatow
enum class OWindingOrder
{
	ClockWise = 0,
	CounterClockWise
};

/// Enumeracja okreslajaca typ shadera
enum class OShaderType
{
	VertexShader = 0,
	FragmentShader
};

/// Makro generujace blad z okreslona wiadomoscia
#define OGL3D_ERROR(message)\
{\
std::stringstream m;\
m << "OGL3D Error: " << message << std::endl;\
throw std::runtime_error(m.str());\
}

// Makro generuj¹ce ostrze¿enie z okreœlon¹ wiadomoœci¹.
#define OGL3D_WARNING(message)\
std::wclog << "OGL3D Warning: " << message << std::endl;

// Makro generuj¹ce informacjê z okreœlon¹ wiadomoœci¹.
#define OGL3D_INFO(message)\
std::wclog << "OGL3D Info: " << message << std::endl;
