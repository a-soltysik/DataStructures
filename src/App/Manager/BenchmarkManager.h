#pragma once

#include "App/Manager/Manager.h"

class BenchmarkManager : public Manager
{
public:
    using Manager::Manager;

    void Menu() override;

protected:
    static void Menu(std::ostream& os);

private:
    static void PrepareFileToSave();
};