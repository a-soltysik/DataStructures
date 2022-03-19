#include "App/App.h"

#include "Benchmark/DynamicArray/Benchmark.h"
#include "Benchmark/List/Benchmark.h"
#include "Benchmark/RedBlackTree/Benchmark.h"
#include "Benchmark/Heap/Benchmark.h"

#include "Container/DynamicArray/DynamicArray.h"
#include "Container/List/List.h"
#include "Container/RedBlackTree/RedBlackTree.h"
#include "Container/Heap/Heap.h"

#include "App/Manager/LinearContainerManager.h"
#include "App/Manager/TreeContainerManager.h"
#include "App/Manager/BenchmarkManager.h"

namespace App
{
    std::unique_ptr<Manager> manager;

    void MainMenu();

    void ContainerMenu();

    void Run()
    {
        MainMenu();
    }

    void ContainerMenu()
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

    void MainMenu()
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
}