#pragma once

#include "App/Manager/ContainerManager.h"
#include "Container/DynamicArray/DynamicArray.h"

class DynamicArrayManager : public ContainerManager<DynamicArray>
{
public:
    using ContainerManager<DynamicArray>::ContainerManager;

    void Menu() override;
private:
    void AddMenu();
    void RemoveMenu();

    void PushFront();
    void Insert();
    void PushBack();

    void RemoveFront();
    void RemoveAt();
    void RemoveBack();

    void Access();

    void Find();
};