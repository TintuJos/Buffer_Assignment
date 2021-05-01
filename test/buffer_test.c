#include "unity.h"
#include "buffer.h"
#define BUFF_SIZE 30

uint8_t buf[BUFF_SIZE] = {
    0x0,
};

void setUp(void) {}

void tearDown(void) {}

//Testing insertion and extraction from the same index
void test_buffer_index(void)
{
    buffer_insert(buf, 8, 5, 31);
    TEST_ASSERT_EQUAL_UINT64(31, buffer_extract(buf, 8, 5));
    buffer_insert(buf, 24, 8, 176);
    TEST_ASSERT_EQUAL_UINT64(176, buffer_extract(buf, 24, 8));
    buffer_insert(buf, 4, 1, 1);
    TEST_ASSERT_EQUAL_UINT64(1, buffer_extract(buf, 4, 1));
}

//Testing buffer insert and extract
void test_buffer_functions(void)
{
    buffer_insert(buf, 12, 6, 24);
    buffer_insert(buf, 20, 13, 0x1234);
    TEST_ASSERT_EQUAL_UINT64(0x1234, buffer_extract(buf, 20, 13));
    TEST_ASSERT_EQUAL_UINT64(24, buffer_extract(buf, 12, 6));

    buffer_insert(buf, 42, 11, 0x2f4);
    TEST_ASSERT_EQUAL_UINT64(0x2f4, buffer_extract(buf, 42, 11));

    buffer_insert(buf, 10, 8, 235);
    TEST_ASSERT_EQUAL_UINT64(235, buffer_extract(buf, 10, 8));
}

//Testing buffer overwriting
void test_buffer_overwriting(void)
{
    buffer_insert(buf, 55, 9, 215);
    buffer_insert(buf, 60, 10, 188);
    TEST_ASSERT_EQUAL_UINT64(188, buffer_extract(buf, 60, 10));

    buffer_insert(buf, 65, 12, 315);
    buffer_insert(buf, 65, 6, 55);
    TEST_ASSERT_EQUAL_UINT64(55, buffer_extract(buf, 65, 6));
}

// Testing 64 bits
void test_buffer_64bits(void)
{
    buffer_insert(buf, 0, 64, 0x94f6767654789152);
    TEST_ASSERT_EQUAL_UINT64(0x94f6767654789152, buffer_extract(buf, 0, 64));

    buffer_insert(buf, 80, 64, 0x8756767654789151);
    TEST_ASSERT_EQUAL_UINT64(0x8756767654789151, buffer_extract(buf, 80, 64));
}

int main(void)
{
    RUN_TEST(test_buffer_functions);
    RUN_TEST(test_buffer_64bits);
    RUN_TEST(test_buffer_index);
    RUN_TEST(test_buffer_overwriting);
    return UNITY_END();
}
