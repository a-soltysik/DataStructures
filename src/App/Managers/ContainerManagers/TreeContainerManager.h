#pragma once

#include "App/Managers/ContainerManagers/ContainerManager.h"

template<typename T>
class TreeContainerManager : public ContainerManager<T>
{
public:
    using ContainerManager<T>::ContainerManager;

    void Menu() override;

protected:
    void AddMenu();
    void RemoveMenu();
    void GetTestContainerMenu();
};

template<typename T>
void TreeContainerManager<T>::Menu()
{
    constexpr char MENU[] = "Wybierz operację:\n"
                            "1. Dodaj element\n"
                            "2. Usuń element\n"
                            "3. Znajdź element\n"
                            "4. Wyświetl kontener\n"
                            "5. Zapisz kontener do pliku\n"
                            "6. Odczytaj kontener z pliku\n"
                            "7. Załaduj testowy kontener\n"
                            "8. Wróć\n"
                            "> ";

    while (true)
    {
        auto choice = Utils::GetChoiceFromMenu(MENU, 1, 8);
        switch (choice)
        {
        case 1:
            AddMenu();
            break;
        case 2:
            RemoveMenu();
            break;
        case 3:
            this->FindMenu();
            break;
        case 4:
            this->PrintMenu();
            break;
        case 5:
            this->SaveToFileMenu();
            break;
        case 6:
            this->CreateFromFileMenu();
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
    auto number = Utils::GetInput<typename T::DataType>(std::cin);

    if (!number.has_value())
    {
        std::cout << "Nieprawidłowa liczba\n";
        return;
    }
    this->container.Insert(number.value());
}

template<typename T>
void TreeContainerManager<T>::RemoveMenu()
{
    std::cout << "Podaj liczbę, którą chcesz usunąć z kontenera: ";
    auto number = Utils::GetInput<typename T::DataType>(std::cin);

    if (!number.has_value())
    {
        std::cout << "Nieprawidłowa liczba\n";
        return;
    }
    this->container.Remove(number.value());
}

template<typename T>
void TreeContainerManager<T>::GetTestContainerMenu()
{
    std::cout << "Podaj nazwę pliku: ";
    auto filename = Utils::GetInput<std::string>(std::cin);

    if (!filename.has_value())
    {
        std::cout << "Błąd odczytu nazwy\n";
        return;
    }

    std::ifstream fin(filename.value());

    auto sizeOpt = Utils::GetInput<size_t>(fin);

    if (sizeOpt.has_value())
    {
        T newContainer;

        size_t size = sizeOpt.value();

        for (size_t i = 0; i < size; i++)
        {
            auto value = Utils::GetInput<typename T::DataType>(fin);
            if (!value.has_value())
            {
                std::cout << "Błąd odczytu danych\n";
                return;
            }
            newContainer.Insert(value.value());
        }
        this->container = newContainer;
    }
    else
    {
        std::cout << "Błąd odczytu danych\n";
    }
}
