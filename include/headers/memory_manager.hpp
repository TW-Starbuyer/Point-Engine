
#include "defs.hpp"
#include "state.hpp"
#include "components.hpp"


class MemoryManager
{
public:
	MemoryManager();

	template <typename T>
	void PrealocVector(POINT::vector<T>& vector, int ammount)
	{
		vector.resize(ammount);
	}

	template <typename T>
	void PrealocHashmap(POINT::hashmap<EntityID, T>& hashmap, int ammount)
	{
		hashmap.reserve(ammount);
	}

	template <typename T>
	void PrealocComponentData(ComponentSets<T>& component, int ammount)
	{
		PrealocVector(component.dense, ammount);
		PrealocVector(component.sparse, ammount);
	}

	
};