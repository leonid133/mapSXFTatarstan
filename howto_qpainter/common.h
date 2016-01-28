#ifndef COMMON_H
#define COMMON_H


#include <cstdio>
#include <cstdint>
#include <typeinfo>
#include <QString>
#include <cmath>
#include <algorithm>
#include <memory>
#include <vector>
//#include <cString>
#include <iconv.h>


//#include <lib/sxf.h>

//using namespace std;
//using namespace sxf;

const double Rz=6300000; //m

//#define uint32_t int

#include <QString>
#include <typeinfo>
#include <QFile>



namespace sxf
{
    class GVektor
    {
        public:

        double x, y, z;

        GVektor();
        GVektor(const GVektor & v);
        GVektor(const double t_x, const double t_y, const double t_z);

        const GVektor & operator=(const GVektor & v);
        double operator[](const unsigned ind) const;
        double & operator[](const unsigned ind);
        const GVektor operator+(const GVektor & v);
        const GVektor & operator+=(const GVektor & v);
        const GVektor operator-(const GVektor & v);
        double euclidean_distance_to(const GVektor & op) const;
    };
/*
    class svektor
    {
        double lat, lon, h;
        svektor();
        svektor(const double t_lat, const double t_lon, const double t_h = Rz);
        svektor(const svektor & s);
        virtual ~svektor(){};
        const svektor & operator=(const svektor & v);
    };
    */
};


namespace sxf
{
    class File
    {
        FILE * fl;

        public:

            File(const QString fname);
           // CFile(const QString fname);
            ~File();

            void operator()(void * buf, const size_t size);
            void seek(const uint32_t offset);
            long offset();

            #define PACK(__TYPE, fun)\
            else if(typeid(TYPE) == typeid(__TYPE))\
            {\
                for(v = 0; v < num; v++)\
                    buf[v] = fun(buf[v]);\
            }

            #define PACK_REAL(__TYPE, __D_TYPE, fun)\
            else if(typeid(TYPE) == typeid(__TYPE))\
            {\
                __D_TYPE val;\
                \
                for(v = 0; v < num; v++)\
                {\
                    val = fun(* (__D_TYPE *) (buf + v));\
                    buf[v] = * (TYPE *) & val;\
                }\
            }

            template<typename TYPE>
                static void pack(TYPE * buf, const unsigned num = 1)
                {
                    #ifndef __MINGW32__

                        unsigned v;

                        if(typeid(TYPE) == typeid(uint8_t))
                        {
                            ;
                        }
                        PACK(uint16_t, htole16)
                        PACK(uint32_t, htole32)
                        PACK(uint64_t, htole64)
                        PACK_REAL(float, uint32_t, htole32)
                        PACK_REAL(double, uint64_t, htole64)
                        else
                        {
                            throw_;
                        }

                    #endif
                }

            template<typename TYPE>
                static void unpack(TYPE * buf, const unsigned num = 1)
                {
                    File::pack<TYPE>(buf, num);
                }
    };
};

namespace codepage
{
    QString ansi_to_utf8(const QString ansi);
    std::wstring utf8_to_wstring(const std::string utf8);
};

namespace sxf
{
    enum EObjectType
    {
        EOT_NOT_DRAW, EOT_POINT, EOT_LINE, EOT_POLYGON, EOT_TEXT
    };

    enum ESemanticsType
    {
        EST_ASCIIZ		= 0,
        EST_ANSI		= 126,
        EST_UNICODE		= 127,
        EST_INT8		= 1,
        EST_INT16		= 2,
        EST_INT32		= 4,
        EST_DOUBLE		= 8
    };

    template<typename sem_type>
    class Semantics
    {
        public:

            ESemanticsType type;
            sem_type value;

            Semantics()
            {
                ;
            };

            Semantics(const sem_type __value, const ESemanticsType __type) :
                type(__type), value(__value)
            {
                ;
            };

            Semantics & operator=(const Semantics & sem)
            {
                type = sem.type;
                value = sem.value;

                return * this;
            };

            int cmp(const Semantics & sem) const
            {
                const double sub = value - sem.value;
                const double threshold = 0.001;

                if(sub < threshold)
                    return -1;
                else if(sub > threshold)
                    return 1;

                return 0;
            };
    };

    class Object
    {
        public:

            unsigned id, code, localization;
            std::vector<GVektor> pnts;
            std::vector<Object> sub_objs;
            EObjectType type;
            QString label;
            std::map<unsigned, Semantics<QString> > string_semantics;
            std::map<unsigned, Semantics<double> > double_semantics;

            void init(const EObjectType __type, const unsigned __id, const unsigned __code, const unsigned __localization);
            void init(const std::vector<GVektor> __pnt, const EObjectType __type, const unsigned __id, const unsigned __code, const unsigned __localization, const QString __label);
            Object & operator=(const Object & obj);
            void add_semantics(const unsigned code, const Semantics<QString> & sem);
            void add_semantics(const unsigned code, const Semantics<double> & sem);
            QString semantics_value(const unsigned code, const QString default_value = "") const;
            double semantics_value(const unsigned code, const double default_value = 0) const;
            int cmp_double_semantics(const unsigned code, const uint64_t value, const uint64_t default_value) const;
    };

    class BaseMap
    {
        std::vector<unsigned> __codes;
        std::vector< std::vector<GVektor> > cnts;
        unsigned __pnts_num;

        void obj_prepare(Object & obj, const double dx, const double dy);

        protected:

            struct
            {
                GVektor left_top;
                GVektor size_in_map_coord;
                unsigned height, width;
                std::vector< std::vector<GVektor> > matrix;
            } hm;

            virtual void __load(const QString map_fname, const QString height_map_fname) = 0;

        public:

            std::vector<Object> objs;

            BaseMap();
            virtual ~BaseMap(){};
            void load(const QString map_fname, const QString height_map_fname, const std::vector<unsigned> codes);
            std::vector< std::vector<GVektor> > contours(unsigned & pnts_num);
    };
};



#endif // COMMON_H
