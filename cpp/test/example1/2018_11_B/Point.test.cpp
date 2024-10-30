#include <gtest/gtest.h>

#include "example1/2018_11_B/Point.h"

using namespace Q_2018_11_B;

TEST(Point, friend_show)
{
    Point point(5);

    show(point);
}

TEST(Circle, Area)
{
    Circle circle(10, 20, 10);
    circle.Area();
}
