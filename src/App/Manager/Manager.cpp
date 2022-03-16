#include "App/Manager/Manager.h"

#include <iostream>

uint8_t Manager::GetChoiceFromMenu(const std::string& menu)
{
    bool goodChoice;
    uint8_t choiceValue;

    do
    {
        std::cout << menu;
        auto choice = Utils::getInput<uint8_t>(std::cin);
        goodChoice = choice.has_value();
        if (!choice.has_value())
        {
            std::cout << "Niepoprawny wybór!\n";
        }
        else
        {
            choiceValue = choice.value();
        }
    } while (!goodChoice);

    return choiceValue;
}
