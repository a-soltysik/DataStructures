#pragma once

#include "App/Manager/Manager.h"

#include <iostream>

class BenchmarkManager : public Manager
{
public:
    using Manager::Manager;

    void Menu() override;

protected:
    static void Menu(std::ostream& os);

    static constexpr char LOCATION_MENU[] = "Wybierz miejsce zapisu wyników:\n"
                                            "1. Konsola\n"
                                            "2. Plik\n"
                                            "3. Powrót\n"
                                            "> ";
    static constexpr char MENU[] =    "Wybierz tryb:\n"
                                      "1. Benchmark tablicy dynamicznej\n"
                                      "2. Benchmark listy\n"
                                      "3. Benchmark drzewa czerwono-czarnego\n"
                                      "4. Benchmark kopca binarnego\n"
                                      "5. Wszystkie benchmarki\n"
                                      "6. Powrót\n"
                                      "> ";
private:
    static void PrepareFileToSave();
};