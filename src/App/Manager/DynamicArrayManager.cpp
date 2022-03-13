#include <iostream>
#include "DynamicArrayManager.h"

void DynamicArrayManager::Menu()
{
    while (true)
    {
        switch (GetChoiceFromMenu(MENU))
        {
            case 1:
                AddMenu();
                break;
            case 2:
                RemoveMenu();
                break;
            case 3:
                Access();
                break;
            case 4:
                Find();
                break;
            case 5:
                Print();
                break;
            case 6:
                SaveToFile();
                break;
            case 7:
                CreateFromFile();
                break;
            default:
                return;
        }
    }
}

void DynamicArrayManager::AddMenu()
{
    switch (GetChoiceFromMenu(ADD_MENU))
    {
        case 1:
            PushFront();
            break;
        case 2:
            Insert();
            break;
        case 3:
            PushBack();
            break;
        default:
            return;
    }
}

void DynamicArrayManager::RemoveMenu()
{
    switch (GetChoiceFromMenu(REMOVE_MENU))
    {
        case 1:
            PushFront();
            break;
        case 2:
            Insert();
            break;
        case 3:
            PushBack();
            break;
        default:
            return;
    }
}

void DynamicArrayManager::PushFront()
{
    std::cout << "Podaj liczbę, którą chcesz dodać na początek ";
    auto number = Utils::getInput<DynamicArray::DataType>();
    if (!number.has_value())
    {
        std::cout << "Nieprawidłowa liczba\n";
        return;
    }
    container.PushFront(number.value());
}

void DynamicArrayManager::Insert()
{
    std::cout << "Podaj pozycję na którą chcesz dodać liczbę: ";
    auto position = Utils::getInput<size_t>();
    if (!position.has_value())
    {
        std::cout << "Nieprawidłowa pozycja\n";
        return;
    }

    std::cout << "Podaj liczbę, którą chcesz dodać: ";
    auto number = Utils::getInput<DynamicArray::DataType>();
    if (!number.has_value())
    {
        std::cout << "Nieprawidłowa liczba\n";
        return;
    }

    try
    {
        container.Insert(position.value(), number.value());
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Podana pozycja wykracza poza zasięg kontenera\n";
    }
}

void DynamicArrayManager::PushBack()
{
    std::cout << "Podaj liczbę, którą chcesz dodać na koniec: ";
    auto number = Utils::getInput<DynamicArray::DataType>();
    if (!number.has_value())
    {
        std::cout << "Nieprawidłowa liczba\n";
        return;
    }
    container.PushBack(number.value());
}

void DynamicArrayManager::RemoveFront()
{
    std::cout << "Usuwanie liczby na pierwszej pozycji... \n";
    container.RemoveFront();
}

void DynamicArrayManager::RemoveAt()
{
    std::cout << "Podaj pozycję, z której chcesz usunąć liczbę: ";
    auto position = Utils::getInput<size_t>();
    if (!position.has_value())
    {
        std::cout << "Nieprawidłowa pozycja\n";
        return;
    }

    std::cout << "Usuwanie liczby na ostatniej pozycji... \n";
    try
    {
        container.RemoveAt(position.value());
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Podana pozycja wykracza poza zasięg kontenera\n";
    }
}

void DynamicArrayManager::RemoveBack()
{
    std::cout << "Usuwanie liczby na ostatniej pozycji... \n";
    container.RemoveBack();
}

void DynamicArrayManager::Access()
{
    std::cout << "Podaj pozycję, z której chcesz uzyskać liczbę: ";
    auto position = Utils::getInput<size_t>();
    if (!position.has_value())
    {
        std::cout << "Nieprawidłowa pozycja\n";
        return;
    }

    try
    {
        auto value = container[position.value()];
        std::cout << "Liczba na pozycji " << position.value() << ".: " << value << "\n";
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Podana pozycja wykracza poza zasięg kontenera\n";
    }
}

void DynamicArrayManager::Find()
{
    std::cout << "Podaj liczbę, którą chcesz wyszukać: ";
    auto number = Utils::getInput<DynamicArray::DataType>();
    if (!number.has_value())
    {
        std::cout << "Nieprawidłowa liczbaa\n";
        return;
    }

    auto position = container.Find(number.value());
    if (position != container.end())
    {
        std::cout << "Znaleziono liczbę " << number.value() << " na pozycji " << std::distance(position, container.begin()) << "\n";
    }
    else
    {
        std::cout << "Nie znaleziono podanej liczby\n";
    }
}