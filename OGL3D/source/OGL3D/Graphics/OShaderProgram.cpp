#include <OGL3D/Graphics/OShaderProgram.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

/// Konstruktor tworzy program cieniowania shader program na podstawie sciezek do plikow vertex i fragment shader
OShaderProgram::OShaderProgram(const OShaderProgramDesc& desc)
{
	m_programId = glCreateProgram();
	attach(desc.vertexShaderFilePath, OShaderType::VertexShader);
	attach(desc.fragmentShaderFilePath, OShaderType::FragmentShader);
	link();
}

/// Destruktor usuwa program cieniowania, odlacza shadery i zwalnia zasoby
OShaderProgram::~OShaderProgram()
{
	for (ui32 i = 0; i < 2; i++)
	{
		glDetachShader(m_programId, m_attachedShaders[i]);
		glDeleteShader(m_attachedShaders[i]);
	}
	glDeleteProgram(m_programId);
}

/// Pobiera identyfikator programu cieniowania
ui32 OShaderProgram::getId()
{
	return m_programId;
}

/// Ustawia slot dla bloku jednorodnego uniform buffer w programie cieniowania
void OShaderProgram::setUniformBufferSlot(const char* name, ui32 slot)
{
	ui32 index = glGetUniformBlockIndex(m_programId, name);
	glUniformBlockBinding(m_programId, index, slot);
}

// Funkcja prywatna dolacza shader do programu cieniowania na podstawie sciezki do pliku
void OShaderProgram::attach(const wchar_t* shaderFilePath, const OShaderType& type)
{
    /// Inicjalizacja pustego stringa do ktorego zostanie wczytany kod shadera
    std::string shaderCode;

    /// Pobranie pelnej sciezki do pliku shadera
    auto path = std::filesystem::path(shaderFilePath);

    /// Otwarcie strumienia do pliku shadera
    std::ifstream shaderStream(path);
    if (shaderStream.is_open())
    {
        /// Utworzenie strumienia do zapisu kodu shadera
        std::stringstream sstr;
        /// Wczytanie zawartosci pliku shadera do strumienia
        sstr << shaderStream.rdbuf();
        /// Przypisanie wczytanego kodu do stringa shaderCode
        shaderCode = sstr.str();
        /// Zamkniecie strumienia pliku
        shaderStream.close();
    }
    else
    {
        /// Komunikat ostrzegawczy w przypadku braku pliku
        OGL3D_WARNING("OShaderProgram | " << shaderFilePath << " not found");
        return;
    }

    /// Utworzenie identyfikatora shadera vertex lub fragment
    ui32 shaderId = 0;
    if (type == OShaderType::VertexShader)
        shaderId = glCreateShader(GL_VERTEX_SHADER);
    else if (type == OShaderType::FragmentShader)
        shaderId = glCreateShader(GL_FRAGMENT_SHADER);

    /// Przypisanie zrodlowego kodu shadera do shadera OpenGL
    auto sourcePointer = shaderCode.c_str();
    glShaderSource(shaderId, 1, &sourcePointer, NULL);
    /// Kompilacja shadera
    glCompileShader(shaderId);

    /// Pobranie ewentualnych bledow kompilacji
    i32 logLength = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        /// Jesli wystapily bledy kompilacji pobierz komunikat i wyswietl ostrzezenie
        std::vector<char> errorMessage(logLength + 1);
        glGetShaderInfoLog(shaderId, logLength, NULL, &errorMessage[0]);
        OGL3D_WARNING("OShaderProgram | " << shaderFilePath << " compiled with errors:" << std::endl << &errorMessage[0]);
        return;
    }

    /// Dolaczenie shadera do programu cieniowania
    glAttachShader(m_programId, shaderId);
    m_attachedShaders[(ui32)type] = shaderId;

    /// Komunikat informacyjny o pomyslnej kompilacji shadera
    OGL3D_INFO("OShaderProgram | " << shaderFilePath << " compiled successfully");
}


/// Funkcja prywatna linkuje program cieniowania
void OShaderProgram::link()
{
    /// Wykonuje linkowanie programu cieniowania
    glLinkProgram(m_programId);

    /// Pobranie ewentualnych bledow podczas linkowania
    i32 logLength = 0;
    glGetShaderiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        /// Jesli wystapily bledy pobierz komunikat i wyswietl ostrzezenie
        std::vector<char> errorMessage(logLength + 1);
        glGetShaderInfoLog(m_programId, logLength, NULL, &errorMessage[0]);
        OGL3D_WARNING("OShaderProgram | " << &errorMessage[0]);
        return;
    }
}

