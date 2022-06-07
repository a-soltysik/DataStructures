#pragma once

#include "App/Managers/GraphManagers/GraphManager.h"
#include "Algorithms/MST/Kruskal.h"
#include "Algorithms/MST/Prim.h"

template<typename T,
         typename U,
         UndirectedGraph::isUndirectedGraph<T> = true,
         UndirectedGraph::isUndirectedGraph<U> = true>
class UndirectedGraphManager : public GraphManager<T, U>
{
public:
    void Menu() override;
    void AddEdgeMenu();
    void KruskalMenu();
    void PrimMenu();
};

template<typename T,
         typename U,
         UndirectedGraph::isUndirectedGraph<T> isGraphT,
         UndirectedGraph::isUndirectedGraph<U> isGraphU>
void UndirectedGraphManager<T, U, isGraphT, isGraphU>::Menu()
{
    constexpr char MENU[] = "Wybierz operację:\n"
                            "1. Dodaj wierzchołek\n"
                            "2. Dodaj krawędź\n"
                            "3. Znajdź minimalne drzewo rozpinające algorytmem Kruskala\n"
                            "4. Znajdź minimalne drzewo rozpinające algorytmem Prima\n"
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
            AddEdgeMenu();
            break;
        case 3:
            KruskalMenu();
            break;
        case 4:
            PrimMenu();
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
         UndirectedGraph::isUndirectedGraph<T> isGraphT,
         UndirectedGraph::isUndirectedGraph<U> isGraphU>
void UndirectedGraphManager<T, U, isGraphT, isGraphU>::AddEdgeMenu()
{
    std::cout << "Podaj dwa wierzchołki i wagę krawędzi: ";
    auto vertex1 = Utils::GetInput<Graph::Vertex>(std::cin);
    auto vertex2 = Utils::GetInput<Graph::Vertex>(std::cin);
    auto weight = Utils::GetInput<Graph::Vertex>(std::cin);

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
    if (!this->listGraph.AddEdge({{*vertex1, *vertex2}, *weight}))
    {
        std::cout << "Nie udało się dodać krawędzi do listy sąsiedztwa. Cofanie zmian\n";
        return;
    }
    if (!this->matrixGraph.AddEdge({{*vertex1, *vertex2}, *weight}))
    {
        std::cout << "Nie udało się dodać krawędzi do macierzy incydencji. Cofanie zmian\n";
        this->listGraph.RemoveEdge({*vertex1, *vertex2});
    }
}

template<typename T,
         typename U,
         UndirectedGraph::isUndirectedGraph<T> isGraphT,
         UndirectedGraph::isUndirectedGraph<U> isGraphU>
void UndirectedGraphManager<T, U, isGraphT, isGraphU>::KruskalMenu()
{
    auto result = MST::Kruskal::FindMstOf(this->listGraph);

    if (result.edges.Size() == 0)
    {
        std::cout << "Minimalne drzewo rozpinające dla listy sąsiedztwa nie istnieje\n";
        return;
    }
    std::cout << "Minimalne drzewo rozpinające dla listy sąsiedztwa:\n" << result << "\n";

    result = MST::Kruskal::FindMstOf(this->matrixGraph);

    if (result.edges.Size() == 0)
    {
        std::cout << "Minimalne drzewo rozpinające dla macierzy incydencji nie istnieje\n";
        return;
    }
    std::cout << "Minimalne drzewo rozpinając dla macierzy incydencji:\n" << result << "\n";
}

template<typename T,
         typename U,
         UndirectedGraph::isUndirectedGraph<T> isGraphT,
         UndirectedGraph::isUndirectedGraph<U> isGraphU>
void UndirectedGraphManager<T, U, isGraphT, isGraphU>::PrimMenu()
{
    auto result = MST::Prim::FindMstOf(this->listGraph);

    if (result.edges.Size() == 0)
    {
        std::cout << "Minimalne drzewo rozpinające dla listy sąsiedztwa nie istnieje\n";
        return;
    }
    std::cout << "Minimalne drzewo rozpinające dla listy sąsiedztwa:\n" << result << "\n";

    result = MST::Prim::FindMstOf(this->matrixGraph);

    if (result.edges.Size() == 0)
    {
        std::cout << "Minimalne drzewo rozpinające dla macierzy incydencji nie istnieje\n";
        return;
    }
    std::cout << "Minimalne drzewo rozpinając dla macierzy incydencji:\n" << result << "\n";
}