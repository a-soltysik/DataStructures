#include "App/App.h"

#include "Container/DynamicArray/DynamicArray.h"
#include "Container/List/List.h"
#include "Container/RedBlackTree/RedBlackTree.h"
#include "Container/Heap/Heap.h"

#include "App/Manager/LinearContainerManager.h"
#include "App/Manager/TreeContainerManager.h"
#include "App/Manager/BenchmarkManager.h"

#ifdef _WIN32
#include <windows.h>
#endif

void SetUtf8()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

int32_t App::Run()
{
    SetUtf8();
    try
    {
        MainMenu();
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
    }
    catch(...)
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
                                      "5. Powrót\n"
                                      "> ";

    switch (Manager::GetChoiceFromMenu(CONTAINER_MENU))
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
        default:
            return;
    }
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
        switch (Manager::GetChoiceFromMenu(MAIN_MENU))
        {
            case 1:
                ContainerMenu();
                manager->Menu();
                break;
            case 2:
                manager = std::make_unique<BenchmarkManager>();
                manager->Menu();
                break;
            case 3:
                return;
            default:
                break;

        }
    }
}

