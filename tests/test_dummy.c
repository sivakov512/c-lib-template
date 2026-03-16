#include "unity.h"
#include <tbd.h>

void setUp() {}

void tearDown() {}

static void test_dummy() {
    TEST_ASSERT_TRUE(DUMMY);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_dummy);

    return UNITY_END();
}
