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

    void SaveToFile();
    void CreateFromFile();
    void Print();

    static uint8_t GetChoiceFromMenu(const char* menu);
protected:
    T container;

    static constexpr char MENU[]        = "Wybierz operację:\n"
                                          "1. Dodaj element\n"
                                          "2. Usuń element\n"
                                          "3. Pobierz element\n"
                                          "4. Znajdź element\n"
                                          "5. Wyświetl kontener\n"
                                          "6. Zapisz kontener do pliku\n"
                                          "7. Odczytaj kontener z pliku\n"
                                          "8. Wróć\n"
                                          "> ";

    static constexpr char TREE_MENU[]   = "Wybierz operację:\n"
                                          "1. Dodaj element\n"
                                          "2. Usuń element\n"
                                          "3. Znajdź element\n"
                                          "4. Wyświetl kontener\n"
                                          "5. Zapisz kontener do pliku\n"
                                          "6. Odczytaj kontener z pliku\n"
                                          "7. Wróć\n"
                                          "> ";

    static constexpr char REMOVE_MENU[] = "Wybierz operację:\n"
                                          "1. Usuń element z początku\n"
                                          "2. Usuń element z wybranej pozycji\n"
                                          "3. Usuń elemnt z końca\n"
                                          "4. Wróć\n"
                                          "> ";

    static constexpr char ADD_MENU[]    = "Wybierz operację:\n"
                                          "1. Dodaj element na początek\n"
                                          "2. Dodaj element na wybraną pozycję\n"
                                          "3. Dodaj element na koniec\n"
                                          "4. Wróć\n"
                                          "> ";
};

template<typename T>
uint8_t ContainerManager<T>::GetChoiceFromMenu(const char* menu)
{
    bool goodChoice;
    uint8_t choiceValue;

    do
    {
        std::cout << menu;
        auto choice = Utils::getInput<uint8_t>(std::cin);
        goodChoice = choice.has_value();
        if (!choice.has_value())
        {
            std::cout << "Niepoprawny wybór!\n";
        }
        else
        {
            choiceValue = choice.value();
        }
    } while (!goodChoice);

    return choiceValue;
}

template<typename T>
void ContainerManager<T>::SaveToFile()
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
void ContainerManager<T>::CreateFromFile()
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
void ContainerManager<T>::Print()
{
    std::cout << container.ToString() << "\n";
}