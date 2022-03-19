#pragma once

#include "App/Manager/ContainerManager.h"

template<typename T>
class LinearContainerManager : public ContainerManager<T>
{
public:
    using ContainerManager<T>::ContainerManager;

    void Menu() override;

protected:
    void AddMenu();

    void PushFrontMenu();

    void InsertMenu();

    void PushBackMenu();

    void RemoveMenu();

    void RemoveFrontMenu();

    void RemoveAtMenu();

    void RemoveBackMenu();

    void AccessMenu();

    static constexpr char MENU[] = "Wybierz operację:\n"
                                   "1. Dodaj element\n"
                                   "2. Usuń element\n"
                                   "3. Pobierz element\n"
                                   "4. Znajdź element\n"
                                   "5. Wyświetl kontener\n"
                                   "6. Zapisz kontener do pliku\n"
                                   "7. Odczytaj kontener z pliku\n"
                                   "8. Załaduj testowy kontener\n"
                                   "9. Wróć\n"
                                   "> ";

    static constexpr char REMOVE_MENU[] = "Wybierz operację:\n"
                                          "1. Usuń element z początku\n"
                                          "2. Usuń element z wybranej pozycji\n"
                                          "3. Usuń elemnt z końca\n"
                                          "4. Wróć\n"
                                          "> ";

    static constexpr char ADD_MENU[] = "Wybierz operację:\n"
                                       "1. Dodaj element na początek\n"
                                       "2. Dodaj element na wybraną pozycję\n"
                                       "3. Dodaj element na koniec\n"
                                       "4. Wróć\n"
                                       "> ";
};

template<typename T>
void LinearContainerManager<T>::Menu()
{
    while (true)
    {
        switch (Manager::GetChoiceFromMenu(MENU))
        {
        case 1:
            AddMenu();
            break;
        case 2:
            RemoveMenu();
            break;
        case 3:
            AccessMenu();
            break;
        case 4:
            this->FindMenu();
            break;
        case 5:
            this->PrintMenu();
            break;
        case 6:
            this->SaveToFileMenu();
            break;
        case 7:
            this->CreateFromFileMenu();
            break;
        case 8:
            this->GetTestContainerMenu();
            break;
        default:
            return;
        }
    }
}

template<typename T>
void LinearContainerManager<T>::AddMenu()
{
    switch (Manager::GetChoiceFromMenu(ADD_MENU))
    {
    case 1:
        PushFrontMenu();
        break;
    case 2:
        InsertMenu();
        break;
    case 3:
        PushBackMenu();
        break;
    default:
        return;
    }
}

template<typename T>
void LinearContainerManager<T>::RemoveMenu()
{
    switch (Manager::GetChoiceFromMenu(REMOVE_MENU))
    {
    case 1:
        RemoveFrontMenu();
        break;
    case 2:
        RemoveAtMenu();
        break;
    case 3:
        RemoveBackMenu();
        break;
    default:
        return;
    }
}

template<typename T>
void LinearContainerManager<T>::PushFrontMenu()
{
    std::cout << "Podaj liczbę, którą chcesz dodać na początek: ";
    auto number = Utils::getInput<typename T::DataType>(std::cin);
    if (!number.has_value())
    {
        std::cout << "Nieprawidłowa liczba\n";
        return;
    }

    this->container.PushFront(number.value());
}

template<typename T>
void LinearContainerManager<T>::InsertMenu()
{
    std::cout << "Podaj pozycję na którą chcesz dodać liczbę: ";
    auto position = Utils::getInput<size_t>(std::cin);
    if (!position.has_value())
    {
        std::cout << "Nieprawidłowa pozycja\n";
        return;
    }

    std::cout << "Podaj liczbę, którą chcesz dodać: ";
    auto number = Utils::getInput<typename T::DataType>(std::cin);
    if (!number.has_value())
    {
        std::cout << "Nieprawidłowa liczba\n";
        return;
    }

    try
    {
        this->container.Insert(position.value(), number.value());
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Podana pozycja wykracza poza zasięg kontenera\n";
    }
}

template<typename T>
void LinearContainerManager<T>::PushBackMenu()
{
    std::cout << "Podaj liczbę, którą chcesz dodać na koniec: ";
    auto number = Utils::getInput<typename T::DataType>(std::cin);
    if (!number.has_value())
    {
        std::cout << "Nieprawidłowa liczba\n";
        return;
    }
    this->container.PushBack(number.value());
}

template<typename T>
void LinearContainerManager<T>::RemoveFrontMenu()
{
    std::cout << "Usuwanie liczby na pierwszej pozycji... \n";
    this->container.RemoveFront();
}

template<typename T>
void LinearContainerManager<T>::RemoveAtMenu()
{
    std::cout << "Podaj pozycję, z której chcesz usunąć liczbę: ";
    auto position = Utils::getInput<size_t>(std::cin);
    if (!position.has_value())
    {
        std::cout << "Nieprawidłowa pozycja\n";
        return;
    }

    std::cout << "Usuwanie liczby na ostatniej pozycji... \n";
    try
    {
        this->container.RemoveAt(position.value());
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Podana pozycja wykracza poza zasięg kontenera\n";
    }
}

template<typename T>
void LinearContainerManager<T>::RemoveBackMenu()
{
    std::cout << "Usuwanie liczby na ostatniej pozycji... \n";
    this->container.RemoveBack();
}

template<typename T>
void LinearContainerManager<T>::AccessMenu()
{
    std::cout << "Podaj pozycję, z której chcesz uzyskać liczbę: ";
    auto position = Utils::getInput<size_t>(std::cin);
    if (!position.has_value())
    {
        std::cout << "Nieprawidłowa pozycja\n";
        return;
    }

    try
    {
        auto value = this->container[position.value()];
        std::cout << "Liczba na pozycji " << position.value() << ".: " << value << "\n";
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Podana pozycja wykracza poza zasięg kontenera\n";
    }
}