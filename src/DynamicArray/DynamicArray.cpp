#include "DynamicArray/DynamicArray.h"
#include <iostream>
#include "Utils/Timer.h"
#include <cstring>

DynamicArray::DynamicArray(size_t size) : size(size)
{
	data = new DataType[size];
}

DynamicArray::DynamicArray(const DynamicArray& rhs)
{
	if (rhs.size == 0u)
	{
		return;
	}
	data = new DataType[rhs.size];
	std::memcpy(data, rhs.data, rhs.size * sizeof(DataType));
	size = rhs.size;
}

DynamicArray::DynamicArray(DynamicArray&& rhs) noexcept
{
	if (rhs.size == 0u)
	{
		return;
	}
	data = rhs.data;
	size = rhs.size;

	rhs.data = nullptr;
	rhs.size = 0u;
}

DynamicArray& DynamicArray::operator=(const DynamicArray& rhs)
{
	if (rhs.size != 0u) {
		DataType* newData = new DataType[rhs.size];

		delete[] data;

		data = newData;
		std::memcpy(data, rhs.data, rhs.size * sizeof(DataType));
	}
	size = rhs.size;

	return *this;
}

DynamicArray& DynamicArray::operator=(DynamicArray&& rhs) noexcept
{
	delete[] data;

	data = rhs.data;
	size = rhs.size;

	rhs.data = nullptr;
	rhs.size = 0u;

	return *this;
}

DynamicArray::~DynamicArray()
{
	Clear();
}

DynamicArray::DataType& DynamicArray::operator[](size_t position)
{
	if (position >= size)
	{
		throw std::out_of_range("Index is out of range");
	}
	return data[position];
}

const DynamicArray::DataType& DynamicArray::operator[](size_t position) const
{
	if (position >= size)
	{
		throw std::out_of_range("Index is out of range");
	}
	return data[position];
}

void DynamicArray::PushBack(DataType value)
{
	DataType* newData = new DataType[size + 1];
	//DataType* newData = static_cast<DataType*>(::operator new((size + 1) * sizeof(DataType)));

	//std::memcpy(newData, data, size * sizeof(DataType));
	std::copy(data, data + size, newData);

	newData[size] = value;

	delete[] data;
	data = newData;

	/*size_t sizeInBytes = size * sizeof(DataType);
	size_t newSizeInBytes = (size + 1) * sizeof(DataType);

	DataType* newData = static_cast<DataType*>(std::realloc(data, newSizeInBytes));

	if (newData == nullptr)
	{
		free(data);
		newData = static_cast<DataType*>(std::malloc(newSizeInBytes));

		if (newData == nullptr)
		{
			throw std::bad_alloc();
		}
	}

	newData[size] = value;
	data = newData;*/

	size++;
}

void DynamicArray::PushFront(DataType value)
{
	DataType* newData = new DataType[size + 1];

	std::memcpy(newData + 1, data, size * sizeof(DataType));
	newData[0] = value;

	delete[] data;
	data = newData;
	/*size_t sizeInBytes = size * sizeof(DataType);
	size_t newSizeInBytes = (size + 1) * sizeof(DataType);

	DataType* newData = static_cast<DataType*>(std::realloc(data, newSizeInBytes));

	if (newData == nullptr)
	{
		free(data);
		newData = static_cast<DataType*>(std::malloc(newSizeInBytes));

		if (newData == nullptr)
		{
			throw std::bad_alloc();
		}
	}
	std::memmove(newData + 1, data, size * sizeof(DataType));
	newData[0] = value;
	data = newData;*/

	size++;
}

void DynamicArray::Insert(size_t position, DataType value)
{
	//DataType* newData = new DataType[size + 1];
	/*DataType* newData = (DataType*)std::malloc((size + 1) * sizeof(DataType));

	std::memcpy(newData, data, position * sizeof(DataType));
	std::memcpy(newData + position + 1, data + position, (size - position) * sizeof(DataType));
	newData[position] = value;

	delete[] data;
	data = newData;

	size++;*/

	if (position > size)
	{
		throw std::out_of_range("Position is beyond the size of list");
	}
	if (position == size)
	{
		PushBack(value);
		return;
	}
	if (position == 0u)
	{
		PushFront(value);
		return;
	}

	/*size_t sizeInBytes = size * sizeof(DataType);
	size_t newSizeInBytes = (size + 1) * sizeof(DataType);

	DataType* newData = static_cast<DataType*>(std::realloc(data, newSizeInBytes));

	if (newData == nullptr)
	{
		std::cout << "aa";
		free(data);
		newData = static_cast<DataType*>(std::malloc(newSizeInBytes));

		if (newData == nullptr)
		{
			throw std::bad_alloc();
		}

		std::memcpy(newData, data, position * sizeof(DataType));
	}

	
	
	std::memmove(newData + position + 1, data + position, (size - position) * sizeof(DataType));
	newData[position] = value;
	data = newData;*/

	DataType* newData = new DataType[size + 1];

	std::memcpy(newData, data, position * sizeof(DataType));
	std::memcpy(newData + position + 1, data + position, (size - position) * sizeof(DataType));
	newData[position] = value;

	delete[] data;
	data = newData;

	size++;
}

bool DynamicArray::Remove(DataType value)
{
	size_t positionToRemove = Find(value);

	if (positionToRemove == INVALID_INDEX)
	{
		return false;
	}

	RemoveAt(positionToRemove);
	return true;
}

bool DynamicArray::RemoveAll(DataType value)
{
	size_t numberOfValues = 0u;
	size_t currenPosition = 0u;
	size_t positionToRemove;

	while ((positionToRemove = Find(value, currenPosition)) != INVALID_INDEX)
	{
		numberOfValues++;
		std::memcpy(data + positionToRemove, data + positionToRemove + 1, (size - numberOfValues) * sizeof(DataType));
	}
	if (numberOfValues > 0u)
	{
		DataType* newData = new DataType[size - numberOfValues];
		std::memcpy(newData, data, (size - numberOfValues) * sizeof(DataType));

		delete[] data;
		data = newData;

		size -= numberOfValues;

		return true;
	}
	return false;
}

void DynamicArray::RemoveBack()
{
	DataType* newData = new DataType[size - 1];

	std::memcpy(newData, data, (size - 1) * sizeof(DataType));

	delete[] data;
	data = newData;

	size--;
}

void DynamicArray::RemoveFront()
{
	DataType* newData = new DataType[size - 1];

	std::memcpy(newData, data + 1, (size - 1) * sizeof(DataType));

	delete[] data;
	data = newData;

	size--;
}

void DynamicArray::RemoveAt(size_t positionToRemove)
{
	if (positionToRemove >= size)
	{
		throw std::out_of_range("Index is out of range");
	}

	DataType* newData = new DataType[size - 1];

	std::memcpy(newData, data, positionToRemove * sizeof(DataType));
	std::memcpy(newData + positionToRemove, data + positionToRemove + 1, (size - positionToRemove - 1) * sizeof(DataType));

	delete[] data;
	data = newData;

	size--;
}

void DynamicArray::Clear()
{
	delete[] data;
	data = nullptr;
	size = 0u;
}

size_t DynamicArray::Find(DataType value, size_t start) const noexcept
{
	for (size_t i = 0u; i < size; i++)
	{
		if (value == data[i])
		{
			return i;
		}
	}
	return INVALID_INDEX;
}

size_t DynamicArray::Size() const noexcept
{
	return size;
}

DynamicArray::Iterator DynamicArray::begin() noexcept
{
	return Iterator(data);
}

DynamicArray::Iterator DynamicArray::end() noexcept
{
	return Iterator(data + size);
}

bool DynamicArray::Serialize(std::ostream& os, const DynamicArray& array)
{
	os << array.Size() << "\n";
	for (size_t i = 0u; i < array.Size(); i++)
	{
		os << array[i] << " ";
	}
	if (os.good())
	{
		return true;
	}
	return false;
}

std::optional<DynamicArray> DynamicArray::Deserialize(std::istream& is)
{
	size_t size;
	is >> size;
	DynamicArray array(size);
	for (size_t i = 0u; i < size; i++)
	{
		is >> array[i];
	}

	if (is.good())
	{
		return array;
	}
	return {};
}

std::ostream& operator<<(std::ostream& os, const DynamicArray& array)
{
	os << "[";
	for (size_t i = 0u; i < array.Size(); i++)
	{
		os << array[i];
		if (i != array.Size() - 1u)
		{
			os << ", ";
		}
	}
	os << "]";
	return os;
}