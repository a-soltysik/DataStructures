#include "App/App.h"

#ifdef _WIN32
#include <windows.h>
#endif

void SetUtf8()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

int main()
{
    SetUtf8();
    App::Run();

    return 0;
}