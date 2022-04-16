#include <gtest/gtest.h>

#include "Utils/Utils.h"

int main(int argc, char** argv) {
    Utils::SetUtf8();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}