#pragma once

#include "App/Managers/Manager.h"

template<typename T>
class ContainerManager : public Manager
{
public:
    using Manager::Manager;

    void FindMenu();
    void SaveToFileMenu();
    void CreateFromFileMenu();
    void PrintMenu();

protected:
    T container;
};

template<typename T>
void ContainerManager<T>::SaveToFileMenu()
{
    std::cout << "Podaj nazwę pliku: ";
    auto filename = Utils::GetInput<std::string>(std::cin);

    if (!filename.has_value())
    {
        std::cout << "Błąd odczytu nazwy\n";
        return;
    }

    std::ofstream fout(filename.value());
    fout << container << "\n";

    if (!fout.fail())
    {
        std::cout << "Zapisano kontener do pliku\n";
    }
    else
    {
        std::cout << "Nie udało się zapisać kontenera do pliku\n";
    }
}

template<typename T>
void ContainerManager<T>::CreateFromFileMenu()
{
    std::cout << "Podaj nazwę pliku: ";
    auto filename = Utils::GetInput<std::string>(std::cin);

    if (!filename.has_value())
    {
        std::cout << "Błąd odczytu nazwy\n";
        return;
    }

    std::ifstream fin(filename.value());
    auto newContainer = Utils::GetInput<T>(fin);

    if (newContainer.has_value())
    {
        std::cout << "Odczytano kontener z pliku\n";
        container = newContainer.value();
    }
    else
    {
        std::cout << "Nie udało się odczytać kontenera z pliku\n";
    }
}

template<typename T>
void ContainerManager<T>::PrintMenu()
{
    std::cout << container.ToString() << "\n";
}

template<typename T>
void ContainerManager<T>::FindMenu()
{
    std::cout << "Podaj liczbę, którą chcesz wyszukać: ";
    auto number = Utils::GetInput<typename T::DataType>(std::cin);

    if (!number.has_value())
    {
        std::cout << "Nieprawidłowa liczba\n";
        return;
    }

    auto position = container.Find(number.value());

    if (position != container.end())
    {
        std::cout << "Znaleziono liczbę " << number.value() << "\n";
    }
    else
    {
        std::cout << "Nie znaleziono podanej liczby\n";
    }
}