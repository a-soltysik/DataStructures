#pragma once

#include "App/Managers/Manager.h"
#include "App/Settings.h"

class AlgorithmBenchmarkManager : public Manager
{
public:
    using Manager::Manager;

    void Menu() override;

protected:
    static void LocationMenu();
    static void AlgorithmMenu(std::ostream& os);
    static void PrepareFileToSave();
};