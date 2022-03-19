#pragma once

#include <memory>

class Manager;

class App
{
public:
    int32_t Run();

private:
    void MainMenu();
    void ContainerMenu();

    std::unique_ptr<Manager> manager;
};