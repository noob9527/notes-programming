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
 * 例如："(1+(3+4)*2)"匹配正确输出“the match brackes is 2”，不匹配输出： “Cancel”;
*/

#ifndef STACK_H
#define STACK_H

#define MAXSTACK 100
#define STACK_IS_EMPTY 1001
#define STACK_IS_FULL 1002

#include <string.h>  // For string operations

typedef const char* ElemType;

typedef struct
{
    ElemType Data[MAXSTACK];
    int top; // 记录栈顶位置
} SqStack;

void InitStack(SqStack* stack);

void Push(SqStack* stack, ElemType item);
ElemType Pop(SqStack* stack);

char* matching(SqStack* stack, const char* str);

int OverBrim(const SqStack* stack);

void PrintStack(const SqStack* stack);

#endif //STACK_H
