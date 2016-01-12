#include <lib/point.h>
#include <lib/all.h>

gvektor::gvektor() :
    x(0), y(0), z(0)
{
    ;
}

gvektor::gvektor(const gvektor & v) :
    x(v.x), y(v.y), z(v.z)
{
    ;
}

gvektor::gvektor(const double t_x, const double t_y, const double t_z)
{
    x = t_x;
    y = t_y;
    z = t_z;
}

const gvektor & gvektor::operator=(const gvektor & v)
{
    x = v.x;
    y = v.y;
    z = v.z;

    return * this;
}

double gvektor::operator[](const unsigned ind) const
{
    switch(ind)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }

    //throw_;
}

double & gvektor::operator[](const unsigned ind)
{
    switch(ind)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }

    //throw_;
}

const gvektor gvektor::operator+(const gvektor & v)
{
    gvektor ret;

    ret.x = x + v.x;
    ret.y = y + v.y;
    ret.z = z + v.z;

    return ret;
}

const gvektor & gvektor::operator+=(const gvektor & v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return * this;
}

const gvektor gvektor::operator-(const gvektor & v)
{
    return gvektor(x - v.x, y - v.y, z - v.z);
}

double gvektor::euclidean_distance_to(const gvektor & op) const
{
    return sqrt(pow(x - op.x, 2) + pow(y - op.y, 2) + pow(z - op.z, 2));
}

