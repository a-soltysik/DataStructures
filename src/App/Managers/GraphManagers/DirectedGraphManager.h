#pragma once

#include "App/Managers/GraphManagers/GraphManager.h"
#include "Algorithms/ShortestPath/BellmanFord.h"
#include "Algorithms/ShortestPath/Dijkstra.h"

template<typename T,
         typename U,
         DirectedGraph::isDirectedGraph<T> = true,
         DirectedGraph::isDirectedGraph<U> = true>
class DirectedGraphManager : public GraphManager<T, U>
{
public:
    void Menu() override;
    void AddDirectedEdgeMenu();
    void BellmanFordMenu();
    void DijkstraMenu();
};

template<typename T,
         typename U,
         DirectedGraph::isDirectedGraph<T> isGraphT,
         DirectedGraph::isDirectedGraph<U> isGraphU>
void DirectedGraphManager<T, U, isGraphT, isGraphU>::Menu()
{
    constexpr char MENU[] = "Wybierz operację:\n"
                            "1. Dodaj wierzchołek\n"
                            "2. Dodaj krawędź\n"
                            "3. Znajdź najkrótszą ścieżkę algorytmem Bellmana-Forda\n"
                            "4. Znajdź najkrótszą ścieżkę algorytmem Dijkstry\n"
                            "5. Wyświetl graf\n"
                            "6. Wygeneruj losowy graf\n"
                            "7. Zapisz graf do pliku\n"
                            "8. Odczytaj kontener z pliku\n"
                            "9. Wróć\n"
                            "> ";
    while (true)
    {
        auto choice = Utils::GetChoiceFromMenu(MENU, 1, 9);
        switch (choice)
        {
        case 1:
            this->AddVertexMenu();
            break;
        case 2:
            AddDirectedEdgeMenu();
            break;
        case 3:
            BellmanFordMenu();
            break;
        case 4:
            DijkstraMenu();
            break;
        case 5:
            this->PrintMenu();
            break;
        case 6:
            this->GenerateMenu();
            break;
        case 7:
            this->SaveToFileMenu();
            break;
        case 8:
            this->CreateFromFileMenu();
            break;
        default:
            return;
        }
    }
}


template<typename T,
         typename U,
         DirectedGraph::isDirectedGraph<T> isGraphT,
         DirectedGraph::isDirectedGraph<U> isGraphU>
void DirectedGraphManager<T, U, isGraphT, isGraphU>::AddDirectedEdgeMenu()
{
    std::cout << "Podaj dwa wierzchołki i wagę krawędzi: ";
    auto vertex1 = Utils::GetInput<Graph::Vertex>(std::cin);
    auto vertex2 = Utils::GetInput<Graph::Vertex>(std::cin);
    auto weight  = Utils::GetInput<Graph::Vertex>(std::cin);

    if (!vertex1.has_value() || !vertex2.has_value() || !weight.has_value())
    {
        std::cout << "Niepoprawne dane\n";
        return;
    }
    if (*weight < 1 || *weight == Graph::INFINITY_WEIGHT)
    {
        std::cout << "Nieprawidłowa waga\n";
        return;
    }
    if (!this->listGraph.DoesExist(*vertex1)   || !this->listGraph.DoesExist(*vertex2) ||
        !this->matrixGraph.DoesExist(*vertex1) || !this->matrixGraph.DoesExist(*vertex2))
    {
        std::cout << "Co najmniej jeden z wierzchołków nie istnieje\n";
        return;
    }
    if (this->listGraph.DoesExist({*vertex1, *vertex2}) ||
        this->matrixGraph.DoesExist({*vertex1, *vertex2}))
    {
        std::cout << "Podana krawędź już istnieje\n";
        return;
    }
    if (!this->listGraph.AddDirectedEdge({{*vertex1, *vertex2}, *weight}))
    {
        std::cout << "Nie udało się dodać krawędzi do listy sąsiedztwa. Cofanie zmian\n";
        return;
    }
    if (!this->matrixGraph.AddDirectedEdge({{*vertex1, *vertex2}, *weight}))
    {
        std::cout << "Nie udało się dodać krawędzi do macierzy incydencji. Cofanie zmian\n";
        this->listGraph.RemoveDirectedEdge({*vertex1, *vertex2});
    }
}

template<typename T,
         typename U,
         DirectedGraph::isDirectedGraph<T> isGraphT,
         DirectedGraph::isDirectedGraph<U> isGraphU>
void DirectedGraphManager<T, U, isGraphT, isGraphU>::BellmanFordMenu()
{
    std::cout << "Podaj wierzhołek początkowy: ";
    auto from = Utils::GetInput<Graph::Vertex>(std::cin);
    std::cout << "Podaj wierzhołek końcowy: ";
    auto to = Utils::GetInput<Graph::Vertex>(std::cin);

    if (!from.has_value() || !to.has_value())
    {
        std::cout << "Nieprawidłowe dane\n";
        return;
    }

    auto result = ShortestPath::BellmanFord::FindShortestPath(this->listGraph, *from, *to);

    if (result.path.Size() == 0)
    {
        std::cout << "Najkrótsza ścieżka dla listy sąsiedztwa nie istnieje\n";
        return;
    }
    std::cout << "Najkrótsza ścieżka dla listy sąsiedztwa:\n" << result << "\n";

    result = ShortestPath::BellmanFord::FindShortestPath(this->matrixGraph, *from, *to);

    if (result.path.Size() == 0)
    {
        std::cout << "Najkrótsza ścieżka dla macierzy incydencji nie istnieje\n";
        return;
    }
    std::cout << "Najkrótsza ścieżka dla macierzy incydencji:\n" << result << "\n";
}

template<typename T,
         typename U,
         DirectedGraph::isDirectedGraph<T> isGraphT,
         DirectedGraph::isDirectedGraph<U> isGraphU>
void DirectedGraphManager<T, U, isGraphT, isGraphU>::DijkstraMenu()
{
    std::cout << "Podaj wierzhołek początkowy: ";
    auto from = Utils::GetInput<Graph::Vertex>(std::cin);
    std::cout << "Podaj wierzhołek końcowy: ";
    auto to = Utils::GetInput<Graph::Vertex>(std::cin);

    if (!from.has_value() || !to.has_value())
    {
        std::cout << "Nieprawidłowe dane\n";
        return;
    }

    auto result = ShortestPath::Dijkstra::FindShortestPath(this->listGraph, *from, *to);

    if (result.path.Size() == 0)
    {
        std::cout << "Najkrótsza ścieżka dla listy sąsiedztwa nie istnieje\n";
        return;
    }
    std::cout << "Najkrótsza ścieżka dla listy sąsiedztwa:\n" << result << "\n";

    result = ShortestPath::Dijkstra::FindShortestPath(this->matrixGraph, *from, *to);

    if (result.path.Size() == 0)
    {
        std::cout << "Najkrótsza ścieżka dla macierzy incydencji nie istnieje\n";
        return;
    }
    std::cout << "Najkrótsza ścieżka dla macierzy incydencji:\n" << result << "\n";
}
