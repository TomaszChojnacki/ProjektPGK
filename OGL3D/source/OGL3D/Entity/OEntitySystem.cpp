#include <OGL3D/Entity/OEntitySystem.h>
#include <OGL3D/Entity/OEntity.h>

/// Konstruktor klasy OEntitySystem
OEntitySystem::OEntitySystem()
{
}

/// Destruktor klasy OEntitySystem
OEntitySystem::~OEntitySystem()
{
}

/// Metoda tworzaca nowy obiekt encji i dodajaca go do systemu
bool OEntitySystem::createEntityInternal(OEntity* entity, size_t id)
{
	/// Tworzymy unikalny wskaznik dla obiektu encji
	auto ptr = std::unique_ptr<OEntity>(entity);

	/// Dodajemy obiekt encji do kontenera m_entities
	m_entities[id].emplace(entity, std::move(ptr));

	/// Ustawiamy identyfikator i wskaznik do systemu encji w obiekcie encji
	entity->m_id = id;
	entity->m_entitySystem = this;

	/// Wywolujemy metode onCreate obiektu encji
	entity->onCreate();

	/// Zwracamy true aby oznaczyc powodzenie operacji
	return true;
}

/// Metoda usuwajaca obiekt encji z systemu
void OEntitySystem::removeEntity(OEntity* entity)
{
	/// Dodajemy obiekt encji do listy do zniszczenia
	m_entitiesToDestroy.emplace(entity);
}

/// Metoda aktualizujaca obiekty encji w systemie
void OEntitySystem::update(f32 deltaTime)
{
	/// Usuwamy obiekty encji oznaczone do zniszczenia
	for (auto e : m_entitiesToDestroy)
	{
		m_entities[e->m_id].erase(e);
	}
	m_entitiesToDestroy.clear();

	/// Iterujemy po wszystkich kontenerach obiektow encji i wywolujemy onUpdate dla kazdego z nich
	for (auto&& [id, entities] : m_entities)
	{
		for (auto&& [ptr, entity] : entities)
		{
			entity->onUpdate(deltaTime);
		}
	}
}
