/**
 * 一、1.定义顺序表:↓
 *  typedef struct{
 *     ElemType Data[MAXSTACK];
 *     int top;
 *  }SqStack;
 *
 * （1）InitStack()；//初始化顺序表
 * （2）Push()；//push入栈
 * （3）Pop();//出栈
 * （4）StackEmpty()  //判断栈是否为空
 * （5）GetTop();//获取栈顶元素
 * （6）Overbrim();//判断栈是否已满
 * （7）Matching();//匹配表达式
 *
 * 二、 编写主函数匹配表达式：输入表达式，计算括号有多少对，
 * 例如：“（1+（3+4）*2）”匹配正确输出“the match brackes is 2”，不匹配输出： “Cancel”;
*/

#include "Stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


void InitStack(SqStack* stack)
{
    stack->top = 0;
}

void Push(SqStack* stack, ElemType item)
{
    stack->Data[stack->top] = item;
    stack->top++;
}

ElemType Pop(SqStack* stack)
{
    if (stack->top == 0)
    {
        return NULL;
    }
    stack->top--;
    // because we use 0-based index
    // so the top element is at array[array.length - 1]
    return stack->Data[stack->top];
}

// 判断栈空
int StackEmpty(SqStack* stack)
{
    return stack->top == 0;
}

int OverBrim(const SqStack* stack)
{
    return stack->top == MAXSTACK;
}

char* matching(SqStack* stack, const char* str)
{
    int matching = 0;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] == '(')
        {
            Push(stack, "1");
        }
        else if (str[i] == ')')
        {
            if (Pop(stack) == NULL)
            {
                return "CANCEL";
            }
            else
            {
                matching++;
            }
        }
    }
    if (!StackEmpty(stack))
    {
        return "CANCEL";
    }
    char* result = (char*)malloc(100);
    // char result[100];
    sprintf(result, "the match brackes is %d", matching);
    return result;
}

void PrintStack(const SqStack* stack)
{
    printf("stack.top: %d\n", stack->top);
    puts("stack.Data:");
    const int max = MIN(stack->top, MAXSTACK);

    for (int i = 0; i < max; ++i)
    {
        printf("%s,", stack->Data[i]);
    }
    puts("\n");
}
