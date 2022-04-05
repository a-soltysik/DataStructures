#include "App/App.h"

#include "Container/DynamicArray/DynamicArray.h"
#include "Container/List/List.h"
#include "Container/RedBlackTree/RedBlackTree.h"
#include "Container/Heap/Heap.h"
#include "Container/AvlTree/AvlTree.h"

#include "App/Manager/LinearContainerManager.h"
#include "App/Manager/TreeContainerManager.h"
#include "App/Manager/BenchmarkManager.h"

#include "Utils/Timer.h"

int32_t App::Run()
{
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
            manager = std::make_unique<BenchmarkManager>();
            manager->Menu();
            break;
        default:
            return;
        }
    }
}