#pragma once

#include "App/Managers/Manager.h"

#include <memory>

class App
{
public:
    int32_t Run();

private:
    void MainMenu();
    void ContainerMenu();

    std::unique_ptr<Manager> manager;
};