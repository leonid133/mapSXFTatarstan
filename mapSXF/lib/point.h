#ifndef POINT_H
#define POINT_H

namespace sxf
{
    class vektor
    {
        public:

        double x, y, z;

        vektor();
        vektor(const vektor & v);
        vektor(const double t_x, const double t_y, const double t_z);

        const vektor & operator=(const vektor & v);
        double operator[](const unsigned ind) const;
        double & operator[](const unsigned ind);
        const vektor operator+(const vektor & v);
        const vektor & operator+=(const vektor & v);
        const vektor operator-(const vektor & v);
        double euclidean_distance_to(const vektor & op) const;
    };
};
extern const double Rz;
class svektor
{
    double lat, lon, h;
    svektor();
    svektor(const double t_lat, const double t_lon, const double t_h = Rz);
    svektor(const svektor & s);
    virtual ~svektor(){};
    const svektor & operator=(const svektor & v);
};

#endif // POINT_H
