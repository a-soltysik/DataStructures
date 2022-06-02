#pragma once

#include "App/Managers/Manager.h"
#include "Algorithms/Graphs/GraphGenerator.h"

template<typename T,
         typename U,
         Graph::isGraph<T> = true,
         Graph::isGraph<U> = true>
class GraphManager : public Manager
{
public:
    void AddVertexMenu();
    void SaveToFileMenu();
    void CreateFromFileMenu();
    void GenerateMenu();
    void PrintMenu();

protected:
    T listGraph;
    U matrixGraph;
};

template<typename T, typename U, Graph::isGraph<T> isGraphT, Graph::isGraph<U> isGraphU>
void GraphManager<T, U, isGraphT, isGraphU>::AddVertexMenu()
{
    std::cout << "Dodawanie nowego wierzchołka...\n";
    if (!listGraph.AddVertex() || !matrixGraph.AddVertex())
    {
        std::cout << "Nie udało się dodać wierzchołka\n";
    }
}

template<typename T, typename U, Graph::isGraph<T> isGraphT, Graph::isGraph<U> isGraphU>
void GraphManager<T, U, isGraphT, isGraphU>::SaveToFileMenu()
{
    std::cout << "Podaj nazwę pliku: ";
    auto filename = Utils::GetInput<std::string>(std::cin);

    if (!filename.has_value())
    {
        std::cout << "Błąd odczytu nazwy\n";
        return;
    }

    std::ofstream fout(filename.value());
    fout << listGraph << "\n";

    if (!fout.fail())
    {
        std::cout << "Zapisano graf do pliku\n";
    }
    else
    {
        std::cout << "Nie udało się zapisać grafu do pliku\n";
    }
}

template<typename T, typename U, Graph::isGraph<T> isGraphT, Graph::isGraph<U> isGraphU>
void GraphManager<T, U, isGraphT, isGraphU>::CreateFromFileMenu()
{
    std::cout << "Podaj nazwę pliku: ";
    auto filename = Utils::GetInput<std::string>(std::cin);

    if (!filename.has_value())
    {
        std::cout << "Błąd odczytu nazwy\n";
        return;
    }

    std::ifstream fin(filename.value());
    auto newListGraph = Utils::GetInput<T>(fin);
    fin.close();

    fin.open(filename.value());
    auto newMatrixGraph = Utils::GetInput<U>(fin);
    fin.close();

    if (newListGraph.has_value())
    {
        std::cout << "Odczytano listę sąsiedztwa z pliku\n";
    }
    else
    {
        std::cout << "Nie udało się odczytać listy sąsiedztwa z pliku. Cofanie zmian\n";
        return;
    }
    if (newMatrixGraph.has_value())
    {
        std::cout << "Odczytano macierz incydencji z pliku\n";
    }
    else
    {
        std::cout << "Nie udało się odczytać macierzy incydencji z pliku. Cofanie zmian\n";
        return;
    }

    listGraph   = *newListGraph;
    matrixGraph = *newMatrixGraph;
}

template<typename T, typename U, Graph::isGraph<T> isGraphT, Graph::isGraph<U> isGraphU>
void GraphManager<T, U, isGraphT, isGraphU>::PrintMenu()
{
    std::cout << "Lista sąsiedztwa:\n";
    std::cout << listGraph.ToString() << "\n";
    std::cout << "\nMacierz incydencji:\n";
    std::cout << matrixGraph.ToString() << "\n";
}

template<typename T, typename U, Graph::isGraph<T> isGraphT, Graph::isGraph<U> isGraphU>
void GraphManager<T, U, isGraphT, isGraphU>::GenerateMenu()
{
    std::cout << "Podaj liczbę wierzchołków: ";
    auto order = Utils::GetInput<Graph::Vertex>(std::cin);
    if (!order.has_value())
    {
        std::cout << "Nieprawidłowa liczba wierzchołków\n";
        return;
    }

    std::cout << "Podaj gęstość w procentach: ";
    auto density = Utils::GetInput<uint32_t>(std::cin);
    if (!density.has_value())
    {
        std::cout << "Nieprawidłowa gęstość\n";
        return;
    }

    std::cout << "Podaj minimalną wagę (dodatnia liczba całkowita): ";
    auto minWeight = Utils::GetInput<Graph::Weight>(std::cin);
    if (!minWeight.has_value())
    {
        std::cout << "Nieprawidłowa waga\n";
        return;
    }

    std::cout << "Podaj maksymalną wagę (dodatnia liczba całkowita): ";
    auto maxWeight = Utils::GetInput<Graph::Weight>(std::cin);
    if (!maxWeight.has_value())
    {
        std::cout << "Nieprawidłowa waga\n";
        return;
    }

    Generator::GraphConfiguration config = {*order, static_cast<float>(*density) / 100.0f, *minWeight, *maxWeight};
    if (!Generator::ValidateGraphConfiguration<T>(config))
    {
        std::cout << "Nieprawidłowe dane\n";
        return;
    }
    listGraph   = *Generator::GenerateConnectedGraph<T>(config);
    matrixGraph = listGraph;
}