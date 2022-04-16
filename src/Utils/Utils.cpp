#include "Utils/Utils.h"

#include <random>
#include <iostream>

namespace Utils
{
    void SetUtf8()
    {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    }

    int32_t GetRandomInt(int32_t from, int32_t to)
    {
        static std::random_device device;
        static std::mt19937 rng(device());

        std::uniform_int_distribution<int32_t> distribution(from, to);
        return distribution(rng);
    }

    uint32_t GetChoiceFromMenu(const std::string& menu, uint32_t min, uint32_t max)
    {
        bool wrongChoice;
        uint32_t choiceValue;

        do
        {
            std::cout << menu;
            auto choice = Utils::getInput<decltype(choiceValue)>(std::cin);
            wrongChoice = !choice.has_value() || (choice.has_value() && (choice.value() < min || choice.value() > max));
            if (wrongChoice)
            {
                std::cout << "Niepoprawny wybór!\n";
            }
            else
            {
                choiceValue = choice.value();
            }
        } while (wrongChoice);

        return choiceValue;
    }
}