#include "Utils/Utils.h"

#include <iostream>

namespace Utils
{

void SetUtf8()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

uint32_t GetChoiceFromMenu(const std::string& menu, uint32_t min, uint32_t max)
{
    bool wrongChoice;
    uint32_t choiceValue;

    do
    {
        std::cout << menu;
        auto choice = Utils::GetInput<decltype(choiceValue)>(std::cin);
        wrongChoice = !choice.has_value() || (choice.has_value() && (choice.value() < min || choice.value() > max));
        if (wrongChoice)
        {
            std::cout << "Niepoprawny wybór!\n";
        }
        else
        {
            choiceValue = choice.value();
        }
    }
    while (wrongChoice);

    return choiceValue;
}

}