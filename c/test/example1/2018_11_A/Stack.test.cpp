#include <gtest/gtest.h>

#include "example1/2018_11_A/Stack.h"


TEST(Stack, InitStack)
{
    SqStack stack;
    PrintStack(&stack);
    InitStack(&stack);
    PrintStack(&stack);
}

TEST(Stack, Push)
{
    SqStack stack;
    InitStack(&stack);
    Push(&stack, "abc");
    Push(&stack, "def");
    PrintStack(&stack);
}

TEST(Stack, Pop)
{
    SqStack stack;
    InitStack(&stack);
    Push(&stack, "abc");
    Push(&stack, "def");
    ElemType item = Pop(&stack);
    puts(item);
    PrintStack(&stack);
}

TEST(Stack, Matching_case1)
{
    SqStack stack;
    InitStack(&stack);
    char* res = matching(&stack, "(1+(3+4)*2)");
    puts(res);

    EXPECT_STREQ(res, "the match brackes is 2");

    if (res != nullptr)
    {
        free(res);
    }
}

TEST(Stack, Matching_case2)
{
    SqStack stack;
    InitStack(&stack);
    char* res = matching(&stack, "(1+(3+4)*2");
    puts(res);
    EXPECT_STREQ(res, "CANCEL");

    if (res != nullptr && res != "CANCEL")
    {
        free(res);
    }
}

TEST(Stack, Matching_case3)
{
    SqStack stack;
    InitStack(&stack);
    char* res = matching(&stack, "(1+3+4)*2)");
    puts(res);
    EXPECT_STREQ(res, "CANCEL");

    if (res != nullptr && res != "CANCEL")
    {
        free(res);
    }
}

TEST(Stack, OverBrim)
{
    SqStack stack;
    InitStack(&stack);

    char str[20];
    for (int i = 0; i < 99; ++i)
    {
        sprintf(str, "%d", i);
        Push(&stack, str);
    }

    EXPECT_EQ(stack.top, 99);
    EXPECT_FALSE(OverBrim(&stack));

    printf("%d\n", OverBrim(&stack));

    sprintf(str, "%d", 99);
    Push(&stack, str);

    printf("%d\n", OverBrim(&stack));
    EXPECT_EQ(stack.top, 100);
    EXPECT_TRUE(OverBrim(&stack));
}
