#include "App/Manager/BenchmarkManager.h"

#include "Benchmark/DynamicArray/Benchmark.h"
#include "Benchmark/List/Benchmark.h"
#include "Benchmark/RedBlackTree/Benchmark.h"
#include "Benchmark/Heap/Benchmark.h"

#include <fstream>
#include <iostream>

void BenchmarkManager::Menu()
{
    constexpr char LOCATION_MENU[] = "Wybierz miejsce zapisu wyników:\n"
                                     "1. Konsola\n"
                                     "2. Plik\n"
                                     "3. Powrót\n"
                                     "> ";

    auto choice = Manager::GetChoiceFromMenu(LOCATION_MENU);
    if (choice == 1)
    {
        Menu(std::cout);
    }
    else if (choice == 2)
    {
        PrepareFileToSave();
    }
}

void BenchmarkManager::Menu(std::ostream& os)
{
    constexpr char MENU[] = "Wybierz tryb:\n"
                            "1. Benchmark tablicy dynamicznej\n"
                            "2. Benchmark listy\n"
                            "3. Benchmark drzewa czerwono-czarnego\n"
                            "4. Benchmark kopca binarnego\n"
                            "5. Wszystkie benchmarki\n"
                            "6. Powrót\n"
                            "> ";

    switch (GetChoiceFromMenu(MENU))
    {
    case 1:
        os << DynamicArrayBenchmark::RunBenchmark() << "\n";
        break;
    case 2:
        os << ListBenchmark::RunBenchmark() << "\n";
        break;
    case 3:
        os << RedBlackTreeBenchmark::RunBenchmark() << "\n";
        break;
    case 4:
        os << HeapBenchmark::RunBenchmark() << "\n";
        break;
    case 5:
        os << DynamicArrayBenchmark::RunBenchmark() << "\n";
        os << ListBenchmark::RunBenchmark() << "\n";
        os << RedBlackTreeBenchmark::RunBenchmark() << "\n";
        os << HeapBenchmark::RunBenchmark() << "\n";
        break;
    default:
        return;
    }
}

void BenchmarkManager::PrepareFileToSave()
{
    std::filesystem::path path;
    uint8_t counter = 0;
    do
    {
        path = "Benchmark" + Utils::Parser::NumberToString(counter) + ".txt";
        counter++;
    } while (std::filesystem::exists(std::filesystem::current_path() / path));

    std::ofstream fout(path);
    if (fout.good())
    {
        fout << "Zapisywanie do pliku: " << path << "\n";
        Menu(fout);
    }
    else
    {
        std::cout << "Nie udało się otworzyć pliku\n";
    }
}