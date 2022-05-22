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
    void GraphMenu();

    std::unique_ptr<Manager> manager;
};