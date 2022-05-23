#include "App/App.h"

#include "Containers/DynamicArray.h"
#include "Containers/List.h"
#include "Containers/RedBlackTree.h"
#include "Containers/Heap.h"
#include "Containers/AvlTree.h"

#include "App/Managers/ContainerManagers/LinearContainerManager.h"
#include "App/Managers/ContainerManagers/TreeContainerManager.h"
#include "App/Managers/ContainerManagers/ContainerBenchmarkManager.h"
#include "App/Managers/GraphManagers/AlgorithmBenchmarkManager.h"

#include "Algorithms/Graphs/UndirectedGraphs/ListGraph.h"
#include "Algorithms/Graphs/UndirectedGraphs/MatrixGraph.h"
#include "Algorithms/Graphs/DirectedGraphs/DirectedListGraph.h"
#include "Algorithms/Graphs/DirectedGraphs/DirectedMatrixGraph.h"

#include "App/Managers/GraphManagers/UndirectedGraphManager.h"
#include "App/Managers/GraphManagers/DirectedGraphManager.h"

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
    constexpr char CONTAINER_MENU[] = "Wybierz opcję:\n"
                                      "1. Tablica dynamiczna\n"
                                      "2. Lista dwukierunkowa\n"
                                      "3. Kopiec binarny\n"
                                      "4. Drzewo czerwono-czarne\n"
                                      "5. Drzewo AVL\n"
                                      "6. Benchmarki\n"
                                      "7. Powrót\n"
                                      "> ";

    auto choice = Utils::GetChoiceFromMenu(CONTAINER_MENU, 1, 7);

    switch (choice)
    {
    case 1:
        manager = std::make_unique<LinearContainerManager<DynamicArray<ContainerSettings::DataType>>>();
        break;
    case 2:
        manager = std::make_unique<LinearContainerManager<List<ContainerSettings::DataType>>>();
        break;
    case 3:
        manager = std::make_unique<TreeContainerManager<Heap<ContainerSettings::DataType>>>();
        break;
    case 4:
        manager = std::make_unique<TreeContainerManager<RedBlackTree<ContainerSettings::DataType>>>();
        break;
    case 5:
        manager = std::make_unique<TreeContainerManager<AvlTree<ContainerSettings::DataType>>>();
        break;
    case 6:
        manager = std::make_unique<ContainerBenchmarkManager>();
        break;
    default:
        return;
    }
    manager->Menu();
}

void App::GraphMenu()
{
    constexpr char CONTAINER_MENU[] = "Wybierz opcję:\n"
                                      "1. Graf nieskierowany (lista sąsiedztwa)\n"
                                      "2. Graf nieskierowany (macierz incydencji)\n"
                                      "3. Graf skierowany    (lista sąsiedztwa)\n"
                                      "4. Graf skierowany    (macierz incydencji)\n"
                                      "5. Benchmarki\n"
                                      "6. Powrót\n"
                                      "> ";

    auto choice = Utils::GetChoiceFromMenu(CONTAINER_MENU, 1, 6);

    switch (choice)
    {
    case 1:
        manager = std::make_unique<UndirectedGraphManager<ListGraph>>();
        break;
    case 2:
        manager = std::make_unique<UndirectedGraphManager<MatrixGraph>>();
        break;
    case 3:
        manager = std::make_unique<DirectedGraphManager<DirectedListGraph>>();
        break;
    case 4:
        manager = std::make_unique<DirectedGraphManager<DirectedMatrixGraph>>();
        break;
    case 5:
        manager = std::make_unique<AlgorithmBenchmarkManager>();
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
                                 "2. Test grafów\n"
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
            GraphMenu();
            break;
        default:
            return;
        }
    }
}