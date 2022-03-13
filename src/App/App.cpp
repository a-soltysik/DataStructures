#include "App/App.h"

#include "Benchmark/DynamicArray/Benchmark.h"
#include "Benchmark/List/Benchmark.h"
#include "Benchmark/RedBlackTree/Benchmark.h"
#include "Benchmark/Heap/Benchmark.h"

#include "App/Manager/DynamicArrayManager.h"

#include <memory>

namespace App
{
    std::unique_ptr<Manager> manager;

    constexpr char MAIN_MENU[] =      "Wybierz tryb:\n"
                                      "1. Test kontenerów\n"
                                      "2. Benchmark\n"
                                      "> ";

    constexpr char CONTAINER_MENU[] = "Wybierz kontener:\n"
                                      "1. Tablica dynamiczna\n"
                                      "2. Lista dwukierunkowa\n"
                                      "3. Kopiec binarny\n"
                                      "4. Drzewo czerwono-czarne\n"
                                      "> ";
    void MainMenu();
    void RunAllBenchmarks();

    void Run()
    {
        manager = std::make_unique<DynamicArrayManager>();
        manager->Menu();
    }

    void MainMenu()
    {
        std::cout << MAIN_MENU;
    }

    void RunAllBenchmarks()
    {
        std::cout << DynamicArrayBenchmark::RunBenchmark() << "\n";
        std::cout << ListBenchmark::RunBenchmark() << "\n";
        std::cout << RedBlackTreeBenchmark::RunBenchmark() << "\n";
        std::cout << HeapBenchmark::RunBenchmark() << "\n";
    }
}