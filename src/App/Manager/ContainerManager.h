#pragma once

#include "Utils/Utils.h"
#include "App/Manager/Manager.h"

#include <iostream>
#include <fstream>

template<typename T>
class ContainerManager : public Manager
{
public:
    using Manager::Manager;

    void FindMenu();
    void SaveToFileMenu();
    void CreateFromFileMenu();
    void PrintMenu();
    void GetTestContainerMenu();

protected:
    T container;
};

template<typename T>
void ContainerManager<T>::SaveToFileMenu()
{
    std::cout << "Podaj nazwę pliku: ";
    auto filename = Utils::getInput<std::string>(std::cin);
    if (!filename.has_value())
    {
        std::cout << "Błąd odczytu nazwy\n";
        return;
    }
    std::ofstream fout(filename.value());
    fout << container << "\n";
    if (fout.good())
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
    auto filename = Utils::getInput<std::string>(std::cin);
    if (!filename.has_value())
    {
        std::cout << "Błąd odczytu nazwy\n";
        return;
    }
    std::ifstream fin(filename.value());
    auto newContainer = Utils::getInput<T>(fin);

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
    auto number = Utils::getInput<typename T::DataType>(std::cin);
    if (!number.has_value())
    {
        std::cout << "Nieprawidłowa liczbaa\n";
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

template<typename T>
void ContainerManager<T>::GetTestContainerMenu()
{
    auto filename = T::ClassName() + ".txt";
    std::ifstream fin(Utils::GetPathFromResources(std::filesystem::path("TestContainers") / filename));
    auto newContainer = Utils::getInput<T>(fin);

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




