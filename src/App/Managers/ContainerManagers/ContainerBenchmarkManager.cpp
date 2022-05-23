#include "App/Managers/ContainerManagers/ContainerBenchmarkManager.h"

#include "App/Benchmarks/ContainerBenchmarks/DynamicArrayBenchmark.h"
#include "App/Benchmarks/ContainerBenchmarks/ListBenchmark.h"
#include "App/Benchmarks/ContainerBenchmarks/RedBlackTreeBenchmark.h"
#include "App/Benchmarks/ContainerBenchmarks/HeapBenchmark.h"
#include "App/Benchmarks/ContainerBenchmarks/AvlTreeBenchmark.h"

#include "Utils/Timer.h"

#include <filesystem>

void ContainerBenchmarkManager::Menu()
{
    ContainerSettings::NUMBER_OF_TESTS = Utils::GetChoiceFromMenu("Podaj liczbę powtórzeń eksperymentów: ", 1, INT32_MAX);
    LocationMenu();
}

void ContainerBenchmarkManager::ContainerMenu(std::ostream& os)
{
    constexpr char MENU[] = "Wybierz tryb:\n"
                            "1. Benchmark tablicy dynamicznej\n"
                            "2. Benchmark listy\n"
                            "3. Benchmark drzewa czerwono-czarnego\n"
                            "4. Benchmark kopca binarnego\n"
                            "5. Benchmark drzewa AVL\n"
                            "6. Wszystkie benchmarki\n"
                            "7. Powrót\n"
                            "> ";

    auto choice = Utils::GetChoiceFromMenu(MENU, 1, 7);

    Utils::Timer timer;
    switch (choice)
    {
    case 1:
        timer.Start();
        os << DynamicArrayBenchmark::RunBenchmark() << "\n";
        break;
    case 2:
        timer.Start();
        os << ListBenchmark::RunBenchmark() << "\n";
        break;
    case 3:
        timer.Start();
        os << RedBlackTreeBenchmark::RunBenchmark() << "\n";
        break;
    case 4:
        timer.Start();
        os << HeapBenchmark::RunBenchmark() << "\n";
        break;
    case 5:
        timer.Start();
        os << AvlTreeBenchmark::RunBenchmark() << "\n";
        break;
    case 6:
        timer.Start();
        os << DynamicArrayBenchmark::RunBenchmark() << "\n";
        os << ListBenchmark::RunBenchmark() << "\n";
        os << HeapBenchmark::RunBenchmark() << "\n";
        os << RedBlackTreeBenchmark::RunBenchmark() << "\n";
        os << AvlTreeBenchmark::RunBenchmark() << "\n";
        break;
    default:
        return;
    }
    timer.Stop();
    std::cout << "Czas trwania benchmarku: " << timer.GetTimeInSeconds() << "s\n";
}

void ContainerBenchmarkManager::PrepareFileToSave()
{
    std::filesystem::path path;
    uint8_t counter = 0;
    do
    {
        path = "Benchmark" + Utils::Parser::NumberToString(counter) + ".txt";
        counter++;
    } while (std::filesystem::exists(std::filesystem::current_path() / path));

    std::ofstream fout(path);
    if (!fout.fail())
    {
        fout << "Zapisywanie do pliku: " << path << "\n";
        ContainerMenu(fout);
    }
    else
    {
        std::cout << "Nie udało się otworzyć pliku\n";
    }
}

void ContainerBenchmarkManager::LocationMenu()
{
    constexpr char LOCATION_MENU[] = "Wybierz miejsce zapisu wyników:\n"
                                     "1. Konsola\n"
                                     "2. Plik\n"
                                     "3. Powrót\n"
                                     "> ";

    auto choice = Utils::GetChoiceFromMenu(LOCATION_MENU, 1, 3);

    switch (choice)
    {
    case 1:
        ContainerMenu(std::cout);
        break;
    case 2:
        PrepareFileToSave();
        break;
    default:
        return;
    }
}
