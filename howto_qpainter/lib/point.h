#ifndef POINT_H
#define POINT_H

extern const double Rz;

namespace sxf
{
    class gvektor
    {
        public:

        double x, y, z;

        gvektor();
        gvektor(const gvektor & v);
        gvektor(const double t_x, const double t_y, const double t_z);

        const gvektor & operator=(const gvektor & v);
        double operator[](const unsigned ind) const;
        double & operator[](const unsigned ind);
        const gvektor operator+(const gvektor & v);
        const gvektor & operator+=(const gvektor & v);
        const gvektor operator-(const gvektor & v);
        double euclidean_distance_to(const gvektor & op) const;
    };

    class svektor
    {
        double lat, lon, h;
        svektor();
        svektor(const double t_lat, const double t_lon, const double t_h = Rz);
        svektor(const svektor & s);
        virtual ~svektor(){};
        const svektor & operator=(const svektor & v);
    };
};

#endif // POINT_H
