#pragma once

class Manager
{
public:
    Manager() = default;
    Manager(const Manager&) = default;
    Manager(Manager&&) noexcept = default;
    Manager& operator=(const Manager&) = default;
    Manager& operator=(Manager&&) noexcept = default;
    virtual ~Manager() = default;

    virtual void Menu() = 0;
};