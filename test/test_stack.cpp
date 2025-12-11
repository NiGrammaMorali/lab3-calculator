#include <gtest.h>
#include "stack.h"

TEST(DynamicStack, CanMakeStack) {
	ASSERT_NO_THROW(DynamicStack<int> S);
}
TEST(DynamicStack, CantPeekIntoEmptyStack) {
	DynamicStack<int> S;
	ASSERT_ANY_THROW(S.Peek(0));
}
TEST(DynamicStack, CantReturnTheTopOfAnEmptyStack) {
	DynamicStack<int> S;
	ASSERT_ANY_THROW(S.Top());
}
TEST(DynamicStack, CanAddAnElementAndReturnTheTop) {
	DynamicStack<int> S(2);
	S.Push(3);
	ASSERT_EQ(3, S.Top());
}
TEST(DynamicStack, CanPopTheElement) {
	DynamicStack<int> S(3);
	S.Push(3);
	S.Push(6);
	S.Push(4);
	S.Pop();
	ASSERT_EQ(6, S.Top());
}
TEST(DynamicStack, StackCanDynamicallyIncreaseItsSize) {
	DynamicStack<int> S(2);
	S.Push(3);
	S.Push(3);
	S.Push(3);
	ASSERT_EQ(4, S.Size());
}
TEST(DynamicStack, CantPopTheEmptyStack) {
	DynamicStack<int> S;
	ASSERT_ANY_THROW(S.Pop());
}
TEST(DynamicStack, CanPeekIntoTheGivenPoint) {
	DynamicStack<int> S(4);
	S.Push(3);
	S.Push(4);
	S.Push(5);
	S.Push(6);
	ASSERT_EQ(4, S.Peek(1));
}