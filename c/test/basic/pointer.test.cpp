#include "gtest/gtest.h"

TEST(pointer, print_1)
{
    int number = 42;
    int* ptr = &number;
    // Method 1: Print memory address in hexadecimal (most common)
    printf("Memory address (hex): %p\n", (void*)ptr);
    // Method 2: Print as unsigned integer
    printf("Memory address (decimal): %lu\n", (unsigned long)ptr);
    // Method 4: Print both address and what it points to
    printf("Pointer %p points to value %d\n", (void*)ptr, *ptr);
}

TEST(pointer, print_2)
{
    char* str = "Hello";
    // For string pointers, print content
    printf("Pointer %p points to value %s\n", (void*)str, str);
    printf("Pointer %p points to value %d\n", (void*)str, *str);
}


/**
 * In C, when you use 0 in a pointer context, it's automatically converted to a null pointer constant. This is actually guaranteed by the C standard. The integer constant 0 has a special status - it's the only integer that can be implicitly converted to a null pointer.
 * Here's what happens under the hood:
 * When you write node != 0, the 0 is not treated as an integer but as a null pointer constant
 * Similarly, when you write while(node), the pointer is evaluated as "false" if it's a null pointer and "true" otherwise
 *
 * If you tried to compare a pointer with any other integer (like node != 1), you would get a warning/error because that's not allowed.
 *
 */
TEST(pointer, NULL_AND_0)
{
    int* ptr = NULL;

    printf("ptr: %p\n", (void*)ptr);

    EXPECT_TRUE(ptr == nullptr);
    EXPECT_TRUE(ptr == 0);
    EXPECT_FALSE(ptr);
}
