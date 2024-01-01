#version 410 core
out vec4 FragColor;  /// Wyjsciowy kolor fragmentu

in vec2 TexCoord;   /// Koordynaty tekstury przekazywane z vertex shadera

/// Samplery tekstur
uniform sampler2D texture1;  /// Sampler dla pierwszej tekstury
uniform sampler2D texture2;  /// Sampler dla drugiej tekstury

void main(void)
{
	/// laczenie miedzy dwiema teksturami 80% tekstury pierwszej 20% tekstury drugiej
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}