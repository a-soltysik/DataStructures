#pragma once

#include "App/Manager/ContainerManager.h"

template<typename T>
class TreeContainerManager : public ContainerManager<T>
{
public:
    using ContainerManager<T>::ContainerManager;

    void Menu() override;

protected:
    void AddMenu();
    void RemoveMenu();

    static constexpr char MENU[] = "Wybierz operację:\n"
                                   "1. Dodaj element\n"
                                   "2. Usuń element\n"
                                   "3. Znajdź element\n"
                                   "4. Wyświetl kontener\n"
                                   "5. Zapisz kontener do pliku\n"
                                   "6. Odczytaj kontener z pliku\n"
                                   "7. Załaduj testowy kontener\n"
                                   "8. Wróć\n"
                                   "> ";
};

template<typename T>
void TreeContainerManager<T>::Menu()
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
                FindMenu();
                break;
            case 4:
                PrintMenu();
                break;
            case 5:
                SaveToFileMenu();
                break;
            case 6:
                CreateFromFileMenu();
                break;
            case 7:
                GetTestContainerMenu();
                break;
            default:
                return;
        }
    }
}

template<typename T>
void TreeContainerManager<T>::AddMenu()
{
    std::cout << "Podaj liczbę, którą chcesz dodać do kontenera: ";
    auto number = Utils::getInput<typename T::DataType>(std::cin);
    if (!number.has_value())
    {
        std::cout << "Nieprawidłowa liczba\n";
        return;
    }
    container.Insert(number.value());
}

template<typename T>
void TreeContainerManager<T>::RemoveMenu()
{
    std::cout << "Podaj liczbę, którą chcesz usunąć z kontenera: ";
    auto number = Utils::getInput<T::DataType>(std::cin);
    if (!number.has_value())
    {
        std::cout << "Nieprawidłowa liczba\n";
        return;
    }
    container.Remove(number.value());
}