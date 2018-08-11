#pragma once
#include "Base.h"
#include <unordered_map>

template<typename KeyType>
class COpaqueBuffer : public CBase
{
public:
	COpaqueBuffer<KeyType>();
	~COpaqueBuffer<KeyType>();

	template<typename ItemType>
	void InsertOrReplace(KeyType aKey, const ItemType& aItem);

	template<typename ItemType>
	bool Insert(KeyType aKey, const ItemType& aItem);

	template<typename ReturnType>
	ReturnType* Get(KeyType aKey);

	void Remove(KeyType aKey);

private:

	struct SOpaqueDataPair
	{
		size_t myTypeID;
		void* myData;
	};

	std::unordered_map<KeyType, SOpaqueDataPair> myData;
};

// Function Definitions:

template<typename KeyType>
inline COpaqueBuffer<KeyType>::COpaqueBuffer()
{
}

template<typename KeyType>
inline COpaqueBuffer<KeyType>::~COpaqueBuffer()
{
}

template<typename KeyType>
template<typename ItemType>
inline void COpaqueBuffer<KeyType>::InsertOrReplace(KeyType aKey, const ItemType & aItem)
{
	ItemType* newItem = new ItemType(aItem);

	SOpaqueDataPair dataPair;
	dataPair.myTypeID = typeid(ItemType).hash_code();
	dataPair.myData = static_cast<void*>(newItem);

	myData.insert_or_assign(aKey, dataPair);
}

template<typename KeyType>
template<typename ItemType>
inline bool COpaqueBuffer<KeyType>::Insert(KeyType aKey, const ItemType & aItem)
{
	if (myData.find(aKey) != myData.end())
	{
		return false;
	}
	else
	{
		InsertOrReplace(aKey, aItem);
		return true;
	}
}

template<typename KeyType>
template<typename ReturnType>
inline ReturnType * COpaqueBuffer<KeyType>::Get(KeyType aKey)
{
	ReturnType* rv = nullptr;

	if (myData.find(aKey) != myData.end() && typeid(ReturnType).hash_code() == myData[aKey].myTypeID)
	{
		rv = static_cast<ReturnType*>((myData[aKey]).myData);
	}

	return rv;
}

template<typename KeyType>
inline void COpaqueBuffer<KeyType>::Remove(KeyType aKey)
{
	if (myData.find(aKey) != myData.end())
	{
		delete myData[aKey].myData;
		myData.erase(aKey);
	}
}
