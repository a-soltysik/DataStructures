#include "DynamicArray/DynamicArray.h"

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

DynamicArray::Iterator DynamicArray::Insert(size_t position, DataType value)
{
	if (position > size)
	{
		throw std::out_of_range("Position is beyond the size of list");
	}
	if (position == size)
	{
		PushBack(value);
		return Iterator(data + size - 1u);
	}
	if (position == 0u)
	{
		PushFront(value);
		return Iterator(data);
	}

	DataType* newData = new DataType[size + 1];

	std::memcpy(newData, data, position * sizeof(DataType));
	std::memcpy(newData + position + 1, data + position, (size - position) * sizeof(DataType));
	newData[position] = value;

	delete[] data;
	data = newData;

	size++;
	return Iterator(data + position);
}

DynamicArray::Iterator DynamicArray::Insert(ConstIterator iterator, DataType value)
{
	return Insert(iterator - cbegin(), value);
}

bool DynamicArray::Remove(DataType value)
{
	auto positionToRemove = Find(value);

	if (positionToRemove == end())
	{
		return false;
	}

	RemoveAt(positionToRemove);
	return true;
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

void DynamicArray::RemoveAt(ConstIterator iterator)
{
	RemoveAt(iterator - cbegin());
}

void DynamicArray::Clear()
{
	delete[] data;
	data = nullptr;
	size = 0u;
}

DynamicArray::ConstIterator DynamicArray::Find(DataType value) const noexcept
{
	for (auto it = cbegin(); it != cend(); it++)
	{
		if (value == *it)
		{
			return it;
		}
	}
	return cend();
}

DynamicArray::Iterator DynamicArray::Find(DataType value) noexcept
{
	for (auto it = begin(); it != end(); it++)
	{
		if (value == *it)
		{
			return it;
		}
	}
	return end();
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

DynamicArray::ConstIterator DynamicArray::cbegin() const noexcept
{
	return ConstIterator(data);
}

DynamicArray::ConstIterator DynamicArray::cend() const noexcept
{
	return ConstIterator(data + size);
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

DynamicArrayConstIterator::DynamicArrayConstIterator(pointer ptr) noexcept
	: ptr(ptr)
{}

DynamicArrayConstIterator::reference DynamicArrayConstIterator::operator*() const noexcept
{
	return *ptr;
}

DynamicArrayConstIterator::pointer DynamicArrayConstIterator::operator->() const noexcept
{
	return ptr;
}

DynamicArrayConstIterator& DynamicArrayConstIterator::operator++() noexcept
{
	ptr++;
	return *this;
}

DynamicArrayConstIterator DynamicArrayConstIterator::operator++(int) noexcept
{
	DynamicArrayConstIterator tmp = *this;
	++(*this);
	return tmp;
}

DynamicArrayConstIterator& DynamicArrayConstIterator::operator--() noexcept
{
	ptr--;
	return *this;
}

DynamicArrayConstIterator DynamicArrayConstIterator::operator--(int) noexcept
{
	DynamicArrayConstIterator tmp = *this;
	--(*this);
	return tmp;
}

DynamicArrayConstIterator& DynamicArrayConstIterator::operator+=(const difference_type offset) noexcept
{
	ptr += offset;
	return *this;
}

DynamicArrayConstIterator DynamicArrayConstIterator::operator+(const difference_type offset) const noexcept
{
	DynamicArrayConstIterator tmp = *this;
	tmp += offset;
	return tmp;
}

DynamicArrayConstIterator& DynamicArrayConstIterator::operator-=(const difference_type offset) noexcept
{
	return *this += -offset;
}

DynamicArrayConstIterator DynamicArrayConstIterator::operator-(const difference_type offset) const noexcept
{
	DynamicArrayConstIterator tmp = *this;
	tmp -= offset;
	return tmp;
}

DynamicArrayConstIterator::difference_type DynamicArrayConstIterator::operator-(const DynamicArrayConstIterator rhs) const noexcept
{
	return ptr - rhs.ptr;
}

DynamicArrayConstIterator::reference DynamicArrayConstIterator::operator[](const difference_type offset) const noexcept
{
	return *(*this + offset);
}

bool DynamicArrayConstIterator::operator==(const DynamicArrayConstIterator& rhs) const noexcept
{
	return ptr == rhs.ptr;
}

bool DynamicArrayConstIterator::operator!=(const DynamicArrayConstIterator& rhs) const noexcept
{
	return !(*this == rhs);
}

bool DynamicArrayConstIterator::operator<(const DynamicArrayConstIterator& rhs) const noexcept
{
	return ptr < rhs.ptr;
}

bool DynamicArrayConstIterator::operator>(const DynamicArrayConstIterator& rhs) const noexcept
{
	return rhs < *this;
}

bool DynamicArrayConstIterator::operator<=(const DynamicArrayConstIterator& rhs) const noexcept
{
	return !(rhs < *this);
}
bool DynamicArrayConstIterator::operator>=(const DynamicArrayConstIterator& rhs) const noexcept
{
	return !(*this < rhs);
}


DynamicArrayIterator::reference DynamicArrayIterator::operator*() const noexcept
{
	return const_cast<reference>(*ptr);
}

DynamicArrayIterator::pointer DynamicArrayIterator::operator->() const noexcept
{
	return const_cast<pointer>(ptr);
}

DynamicArrayIterator& DynamicArrayIterator::operator++() noexcept
{
	ptr++;
	return *this;
}

DynamicArrayIterator DynamicArrayIterator::operator++(int) noexcept
{
	DynamicArrayIterator tmp = *this;
	++(*this);
	return tmp;
}

DynamicArrayIterator& DynamicArrayIterator::operator--() noexcept
{
	ptr--;
	return *this;
}

DynamicArrayIterator DynamicArrayIterator::operator--(int) noexcept
{
	DynamicArrayIterator tmp = *this;
	--(*this);
	return tmp;
}

DynamicArrayIterator& DynamicArrayIterator::operator+=(const difference_type offset) noexcept
{
	ptr += offset;
	return *this;
}

DynamicArrayIterator DynamicArrayIterator::operator+(const difference_type offset) const noexcept
{
	DynamicArrayIterator tmp = *this;
	tmp += offset;
	return tmp;
}

DynamicArrayIterator& DynamicArrayIterator::operator-=(const difference_type offset) noexcept
{
	return *this += -offset;
}

DynamicArrayIterator DynamicArrayIterator::operator-(const difference_type offset) const noexcept
{
	DynamicArrayIterator tmp = *this;
	tmp -= offset;
	return tmp;
}

DynamicArrayIterator::difference_type DynamicArrayIterator::operator-(const DynamicArrayIterator rhs) const noexcept
{
	return ptr - rhs.ptr;
}

DynamicArrayIterator::reference DynamicArrayIterator::operator[](const difference_type offset) const noexcept
{
	return *(*this + offset);
}

bool DynamicArrayIterator::operator==(const DynamicArrayIterator& rhs) const noexcept
{
	return ptr == rhs.ptr;
}

bool DynamicArrayIterator::operator!=(const DynamicArrayIterator& rhs) const noexcept
{
	return !(*this == rhs);
}

bool DynamicArrayIterator::operator<(const DynamicArrayIterator& rhs) const noexcept
{
	return ptr < rhs.ptr;
}

bool DynamicArrayIterator::operator>(const DynamicArrayIterator& rhs) const noexcept
{
	return rhs < *this;
}

bool DynamicArrayIterator::operator<=(const DynamicArrayIterator& rhs) const noexcept
{
	return !(rhs < *this);
}
bool DynamicArrayIterator::operator>=(const DynamicArrayIterator& rhs) const noexcept
{
	return !(*this < rhs);
}