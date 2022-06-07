#include "AlgorithmBenchmarkManager.h"
#include "App/Benchmarks/AlgorithmBenchmarks/MSTBenchmarks/KruskalBenchmark.h"
#include "App/Benchmarks/AlgorithmBenchmarks/MSTBenchmarks/PrimBenchmark.h"
#include "App/Benchmarks/AlgorithmBenchmarks/ShortestPathBenchmarks/BellmanFordBenchmark.h"
#include "App/Benchmarks/AlgorithmBenchmarks/ShortestPathBenchmarks/DijkstraBenchmark.h"
#include "Utils/Timer.h"

#include <filesystem>
#include <iostream>

void AlgorithmBenchmarkManager::Menu()
{
    AlgorithmSettings::NUMBER_OF_TESTS = Utils::GetChoiceFromMenu("Podaj liczbę powtórzeń eksperymentów: ", 1, INT32_MAX);
    LocationMenu();
}

void AlgorithmBenchmarkManager::AlgorithmMenu(std::ostream& os)
{
    constexpr char MENU[] = "Wybierz algorytm:\n"
                            "1. Benchmark algorytmu Kruskala\n"
                            "2. Benchmark algorytmu Prima\n"
                            "3. Benchmark algorytmu Bellmana-Forda\n"
                            "4. Benchmark algorytmu Dijkstry\n"
                            "5. Wszystkie benchmarki\n"
                            "6. Powrót\n"
                            "> ";

    auto choice = Utils::GetChoiceFromMenu(MENU, 1, 6);

    Utils::Timer timer;
    switch (choice)
    {
    case 1:
        timer.Start();
        os << KruskalBenchmark::RunBenchmark() << "\n";
        break;
    case 2:
        timer.Start();
        os << PrimBenchmark::RunBenchmark() << "\n";
        break;
    case 3:
        timer.Start();
        os << BellmanFordBenchmark::RunBenchmark() << "\n";
        break;
    case 4:
        timer.Start();
        os << DijkstraBenchmark::RunBenchmark() << "\n";
        break;
    case 5:
        timer.Start();
        os << KruskalBenchmark::RunBenchmark() << "\n";
        os << PrimBenchmark::RunBenchmark() << "\n";
        os << BellmanFordBenchmark::RunBenchmark() << "\n";
        os << DijkstraBenchmark::RunBenchmark() << "\n";
        break;
    default:
        return;
    }
    timer.Stop();
    std::cout << "Czas trwania benchmarku: " << timer.GetTimeInSeconds() << "s\n";
}

void AlgorithmBenchmarkManager::PrepareFileToSave()
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
        AlgorithmMenu(fout);
    }
    else
    {
        std::cout << "Nie udało się otworzyć pliku\n";
    }
}

void AlgorithmBenchmarkManager::LocationMenu()
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
        AlgorithmMenu(std::cout);
        break;
    case 2:
        PrepareFileToSave();
        break;
    default:
        return;
    }
}
