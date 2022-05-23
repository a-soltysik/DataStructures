#pragma once

#include "App/Managers/Manager.h"
#include "Algorithms/Graphs/GraphGenerator.h"

#include <iostream>

template<typename T, Graph::isGraph<T> = true>
class GraphManager : public Manager
{
public:
    void AddVertexMenu();
    void SaveToFileMenu();
    void CreateFromFileMenu();
    void GenerateMenu();
    void PrintMenu();

protected:
    T graph;
};

template<typename T, Graph::isGraph<T> isGraph>
void GraphManager<T, isGraph>::AddVertexMenu()
{
    std::cout << "Dodawanie nowego wierzchołka...\n";
    if (!graph.AddVertex())
    {
        std::cout << "Nie udało się dodać wierzchołka\n";
    }
}

template<typename T, Graph::isGraph<T> isGraph>
void GraphManager<T, isGraph>::SaveToFileMenu()
{
    std::cout << "Podaj nazwę pliku: ";
    auto filename = Utils::GetInput<std::string>(std::cin);

    if (!filename.has_value())
    {
        std::cout << "Błąd odczytu nazwy\n";
        return;
    }

    std::ofstream fout(filename.value());
    fout << graph << "\n";

    if (!fout.fail())
    {
        std::cout << "Zapisano graf do pliku\n";
    }
    else
    {
        std::cout << "Nie udało się zapisać grafu do pliku\n";
    }
}

template<typename T, Graph::isGraph<T> isGraph>
void GraphManager<T, isGraph>::CreateFromFileMenu()
{
    std::cout << "Podaj nazwę pliku: ";
    auto filename = Utils::GetInput<std::string>(std::cin);

    if (!filename.has_value())
    {
        std::cout << "Błąd odczytu nazwy\n";
        return;
    }

    std::ifstream fin(filename.value());
    auto newContainer = Utils::GetInput<T>(fin);

    if (newContainer.has_value())
    {
        std::cout << "Odczytano kontener z pliku\n";
        graph = newContainer.value();
    }
    else
    {
        std::cout << "Nie udało się odczytać kontenera z pliku\n";
    }
}

template<typename T, Graph::isGraph<T> isGraph>
void GraphManager<T, isGraph>::PrintMenu()
{
    std::cout << graph.ToString() << "\n";
}

template<typename T, Graph::isGraph<T> isGraph>
void GraphManager<T, isGraph>::GenerateMenu()
{
    std::cout << "Podaj liczbę wierzchołków: ";
    auto order = Utils::GetInput<Graph::Vertex>(std::cin);
    if (!order.has_value())
    {
        std::cout << "Nieprawidłowa liczba wierzchołków\n";
        return;
    }

    std::cout << "Podaj gęstość (ułamek dziesiętny): ";
    auto density = Utils::GetInput<float>(std::cin);
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

    Generator::GraphConfiguration config = {*order, *density, *minWeight, *maxWeight};
    if (!Generator::ValidateGraphConfiguration<T>(config))
    {
        std::cout << "Nieprawidłowe dane\n";
        return;
    }
    graph = *Generator::GenerateConnectedGraph<T>(config);
}