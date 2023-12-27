#include <OGL3D/Entity/OEntity.h>
#include <OGL3D/Entity/OEntitySystem.h>

/// Konstruktor klasy OEntity
OEntity::OEntity()
{
}

/// Destruktor klasy OEntity
OEntity::~OEntity()
{
}

/// Metoda zwalniajaca obiekt OEntity
void OEntity::release()
{
	/// Wywolujemy metode removeEntity zwiazana z systemem encji
	m_entitySystem->removeEntity(this);
}

/// Metoda zwracajaca wskaznik do systemu encji do ktorego nalezy obiekt
OEntitySystem* OEntity::getEntitySystem()
{
	return m_entitySystem;
}
