#ifndef COMMON_H
#define COMMON_H

#include <cstdio>
#include <cstdint>
#include <typeinfo>
#include <string>
#include <cmath>
#include <algorithm>
#include <memory>
#include <vector>
#include <cstring>
#include <iconv.h>


//#include <lib/sxf.h>

using namespace std;
//using namespace sxf;

const double Rz=6300000; //m

//#define uint32_t int

#include <string>
#include <typeinfo>
#include <QString>
#include <QFile>

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


namespace sxf
{
    class CFile
    {
        FILE * fl;

        public:

            CFile(const std::string fname);
           // CFile(const QString fname);
            ~CFile();

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
                    CFile::pack<TYPE>(buf, num);
                }
    };
};

namespace codepage
{
    std::string ansi_to_utf8(const std::string ansi);
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
    class CSemantics
    {
        public:

            ESemanticsType type;
            sem_type value;

            CSemantics()
            {
                ;
            };

            CSemantics(const sem_type __value, const ESemanticsType __type) :
                type(__type), value(__value)
            {
                ;
            };

            CSemantics & operator=(const CSemantics & sem)
            {
                type = sem.type;
                value = sem.value;

                return * this;
            };

            int cmp(const CSemantics & sem) const
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

    class CObject
    {
        public:

            unsigned id, code, localization;
            std::vector<gvektor> pnts;
            std::vector<CObject> sub_objs;
            EObjectType type;
            std::string label;
            std::map<unsigned, CSemantics<std::string> > string_semantics;
            std::map<unsigned, CSemantics<double> > double_semantics;

            void init(const EObjectType __type, const unsigned __id, const unsigned __code, const unsigned __localization);
            void init(const std::vector<gvektor> __pnt, const EObjectType __type, const unsigned __id, const unsigned __code, const unsigned __localization, const std::string __label);
            CObject & operator=(const CObject & obj);
            void add_semantics(const unsigned code, const CSemantics<std::string> & sem);
            void add_semantics(const unsigned code, const CSemantics<double> & sem);
            std::string semantics_value(const unsigned code, const std::string default_value = "") const;
            double semantics_value(const unsigned code, const double default_value = 0) const;
            int cmp_double_semantics(const unsigned code, const uint64_t value, const uint64_t default_value) const;
    };

    class CMap
    {
        std::vector<unsigned> __codes;
        std::vector< std::vector<gvektor> > cnts;
        unsigned __pnts_num;

        void obj_prepare(CObject & obj, const double dx, const double dy);

        protected:

            struct
            {
                gvektor left_top;
                gvektor size_in_map_coord;
                unsigned height, width;
                std::vector< std::vector<gvektor> > matrix;
            } hm;

            virtual void __load(const std::string map_fname, const std::string height_map_fname) = 0;

        public:

            std::vector<CObject> objs;

            CMap();

            void load(const std::string map_fname, const std::string height_map_fname, const std::vector<unsigned> codes);
            std::vector< std::vector<gvektor> > contours(unsigned & pnts_num);
    };
};



#endif // COMMON_H
