#pragma once

#include "App/Manager/Manager.h"
#include "Settings.h"

class BenchmarkManager : public Manager
{
public:
    using Manager::Manager;

    void Menu() override;

protected:
    static void LocationMenu();
    static void ContainerMenu(std::ostream& os);
    static void PrepareFileToSave();
};