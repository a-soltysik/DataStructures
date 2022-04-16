#include "App/App.h"

#include "Containers/DynamicArray.h"
#include "Containers/List.h"
#include "Containers/RedBlackTree.h"
#include "Containers/Heap.h"
#include "Containers/AvlTree.h"

#include "App/Managers/ContainerManagers/LinearContainerManager.h"
#include "App/Managers/ContainerManagers/TreeContainerManager.h"
#include "App/Managers/ContainerManagers/ContainerBenchmarkManager.h"

#include "Utils/Timer.h"

#include <iostream>

int32_t App::Run()
{
    AvlTree tree;
    for (auto a : tree) {
        std::cout << a;
    }
    Utils::SetUtf8();

    try
    {
        MainMenu();
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
    }
    catch (...)
    {
        std::cerr << "Nieznany błąd\n";
    }
    return -1;
}

void App::ContainerMenu()
{
    constexpr char CONTAINER_MENU[] = "Wybierz kontener:\n"
                                      "1. Tablica dynamiczna\n"
                                      "2. Lista dwukierunkowa\n"
                                      "3. Kopiec binarny\n"
                                      "4. Drzewo czerwono-czarne\n"
                                      "5. Drzewo AVL\n"
                                      "6. Powrót\n"
                                      "> ";

    auto choice = Utils::GetChoiceFromMenu(CONTAINER_MENU, 1, 6);

    switch (choice)
    {
    case 1:
        manager = std::make_unique<LinearContainerManager<DynamicArray>>();
        break;
    case 2:
        manager = std::make_unique<LinearContainerManager<List>>();
        break;
    case 3:
        manager = std::make_unique<TreeContainerManager<Heap>>();
        break;
    case 4:
        manager = std::make_unique<TreeContainerManager<RedBlackTree>>();
        break;
    case 5:
        manager = std::make_unique<TreeContainerManager<AvlTree>>();
        break;
    default:
        return;
    }
    manager->Menu();
}

void App::MainMenu()
{
    constexpr char MAIN_MENU[] = "Wybierz tryb:\n"
                                 "1. Test kontenerów\n"
                                 "2. Benchmark\n"
                                 "3. Wyjście\n"
                                 "> ";

    while (true)
    {
        auto choice = Utils::GetChoiceFromMenu(MAIN_MENU, 1, 3);

        switch (choice)
        {
        case 1:
            ContainerMenu();
            break;
        case 2:
            manager = std::make_unique<ContainerBenchmarkManager>();
            manager->Menu();
            break;
        default:
            return;
        }
    }
}