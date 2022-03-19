#pragma once

#include "App/Manager/Manager.h"

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