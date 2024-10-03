#pragma once
#include <iostream>
#include <cmath>



using namespace std;
/*
    Поля x и y сделаны приватными
    Конкретно для этого класса их можно было сделать публичными
    Так как пользователь всё-равно будет иметь доступ без ограничений к этим полям через геттеры и сеттеры
    Но они сделаны приватными для образовательных целей
*/

class Point
{
private:
    float mx, my;

public:

    Point(float x, float y);
    Point();

    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);

    void normalize();
    float distance(const Point& p) const;
    float norm() const;
    Point operator+(const Point& right) const;
    Point operator*(float a) const;

    friend ostream& operator<<(ostream& left, const Point& right);
};