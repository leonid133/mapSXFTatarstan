#include <lib/point.h>
#include <lib/all.h>

vektor::vektor() :
    x(0), y(0), z(0)
{
    ;
}

vektor::vektor(const vektor & v) :
    x(v.x), y(v.y), z(v.z)
{
    ;
}

vektor::vektor(const double t_x, const double t_y, const double t_z)
{
    x = t_x;
    y = t_y;
    z = t_z;
}

const vektor & vektor::operator=(const vektor & v)
{
    x = v.x;
    y = v.y;
    z = v.z;

    return * this;
}

double vektor::operator[](const unsigned ind) const
{
    switch(ind)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }

    //throw_;
}

double & vektor::operator[](const unsigned ind)
{
    switch(ind)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }

    //throw_;
}

const vektor vektor::operator+(const vektor & v)
{
    vektor ret;

    ret.x = x + v.x;
    ret.y = y + v.y;
    ret.z = z + v.z;

    return ret;
}

const vektor & vektor::operator+=(const vektor & v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return * this;
}

const vektor vektor::operator-(const vektor & v)
{
    return vektor(x - v.x, y - v.y, z - v.z);
}

double vektor::euclidean_distance_to(const vektor & op) const
{
    return sqrt(pow(x - op.x, 2) + pow(y - op.y, 2) + pow(z - op.z, 2));
}

