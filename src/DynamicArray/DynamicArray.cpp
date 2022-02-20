#include "DynamicArray.h"
#include <cstring>
#include <stdexcept>


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

DynamicArray::DynamicArray(DynamicArray&& rhs)
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

		if (data != nullptr) {
			delete[] data;
		}

		data = newData;
		std::memcpy(data, rhs.data, rhs.size * sizeof(DataType));
	}
	size = rhs.size;

	return *this;
}

DynamicArray& DynamicArray::operator=(DynamicArray&& rhs)
{
	if (data != nullptr) {
		delete[] data;
	}
	data = rhs.data;
	size = rhs.size;

	rhs.data = nullptr;
	rhs.size = 0u;

	return *this;
}

DynamicArray::~DynamicArray()
{
	delete[] data;
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

	std::memcpy(newData, data, size * sizeof(DataType));
	newData[size] = value;

	delete[] data;
	data = newData;

	size++;
}

void DynamicArray::PushFront(DataType value)
{
	DataType* newData = new DataType[size + 1];

	std::memcpy(newData + 1, data, size * sizeof(DataType));
	newData[0] = value;

	delete[] data;
	data = newData;

	size++;
}

void DynamicArray::Insert(size_t position, DataType value)
{
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
