#version 410 core

/// Definicja wejsciowych atrybutow wierzcholka pozycja i koordynaty tekstury
layout (location = 0) in vec3 aPos;			/// Pozycja wierzcholka
layout (location = 1) in vec2 aTexCoord;	/// Koordynaty tekstury

/// Wyjsciowe koordynaty tekstury ktore beda przekazywane do "fragment" shader_scpp
out vec2 TexCoord;

/// Zmienne jednolite dla macierzy transformacji
uniform mat4 model;			/// Macierz modelu
uniform mat4 view;			/// Macierz widoku
uniform mat4 projection;	/// Macierz projekcji

void main(void)
{
	/// Obliczanie koncowej pozycji wierzcholka na podstawie macierzy transformacji
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	
	/// Przekazywanie koordynatow tekstury do "fragment" shader_scpp
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}