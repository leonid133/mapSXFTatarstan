#include <common.h>
#include <typeinfo>

using namespace std;
using namespace sxf;

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

    #define my_iconv_t iconv_t
    #define my_iconv_open iconv_open
    #define my_iconv iconv

#else

    // МГК

    #define my_iconv_t libiconv_t
    #define my_iconv_open libiconv_open
    #define my_iconv libiconv

#endif

bool is_ansi_to_local_init = false;
bool is_utf8_to_utf16_init = false;

my_iconv_t desc_ansi_to_local;
my_iconv_t desc_utf8_to_utf16;

char *conv_charset(const char *from, const char *to, char *str, size_t *size)
{
    /*
    char *out;

    if (*size <= 0) {
        out = strdup("");
    } else {
        char *buf, *holder;
        int bufsize, r;
        size_t insize, outsize;
        iconv_t cd;

        cd = iconv_open(to, from);
        if (cd == (iconv_t) - 1)
            return NULL;

        insize = *size;
        outsize = bufsize = insize * 4;

        buf = (char *) malloc(bufsize);
        holder = buf;

        r = iconv(cd, &str, &insize, &buf, &outsize);
        if (r < 0 || insize != 0) {
            free(holder);
            iconv_close(cd);
            return NULL;
        }


        *size = bufsize - outsize;

        buf -= *size;
        out = (char *) malloc(*size);
        memcpy(out, buf, *size);
        free(holder);
        iconv_close(cd);
    }

    return out;*/
}


STRING codepage::ansi_to_utf8(const STRING ansi)
{
    return ansi.toUtf8();
    /*
    String result = ansi;

    shared_ptr<char> in_buf, out_buf;
    char *p_in_buf=0, *p_out_buf=0;
    size_t in_bytes = 4096, out_bytes = 4096;

    if(! is_ansi_to_local_init)
    {
        //throw_if((desc_ansi_to_local = my_iconv_open("UTF-8", "CP1251")) == (my_iconv_t) -1);
        desc_ansi_to_local = my_iconv_open("UTF-8", "CP1251");
        if(desc_ansi_to_local!=(my_iconv_t) -1)
            is_ansi_to_local_init = true;
    }

    in_buf.reset(new char[in_bytes], std::default_delete<char[]>());
    out_buf.reset(new char[out_bytes], std::default_delete<char[]>());

    //throw_null(p_in_buf = in_buf.get());
    if(!p_in_buf)p_in_buf = in_buf.get();
    //throw_null(p_out_buf = out_buf.get());
    if(!p_out_buf)p_out_buf = out_buf.get();

    strncpy(p_in_buf, ansi.c_str(), in_bytes);
    p_in_buf[in_bytes - 1] = '\0';
    in_bytes = strlen(p_in_buf) + 1;

    //throw_if(my_iconv(desc_ansi_to_local, & p_in_buf, & in_bytes, & p_out_buf, & out_bytes) == (size_t) -1);
    if(my_iconv(desc_ansi_to_local, & p_in_buf, & in_bytes, & p_out_buf, & out_bytes)!= (size_t) -1);
        result = String(out_buf.get());
    //p_out_buf = conv_charset("CP1251", "UTF-8", p_in_buf, & in_bytes);

    return result;
    */
}

wstring codepage::utf8_to_wstring(const std::string utf8)
{
    char ch;
    const unsigned size = utf8.size();
    unsigned v;
    wstring wstr;

    for(v = 0; v < size; v++)
    {
        ch = utf8[v];

        if((ch & 0xE0) == 0xC0)
        {
            // В данной программе - встречаются только 2-х байтовые символы

            const uint16_t high = ch & 0x1F, low = utf8[v + 1] & 0x3F;

            wstr += (wchar_t) ((high << 6) + low);
            v ++;
        }
        else if(! (ch & 0x80))
            wstr += (wchar_t) ch;
    }

    return wstr;
}

File::File(const STRING fname)
{
    fl = NULL;
    try{
        fl = fopen(fname.toStdString().c_str(), "rb");
        //fl = fopen(fname.c_str(), "rb");
    }
    catch(...){}
    //throw_null(fl = fopen(fname.c_str(), "rb"));
}
/*
CFile::CFile(const QString qfname)
{
    String fname = qfname.toStdString();
    fl = NULL;
    fl = fopen(fname.c_str(), "rb");
    //throw_null(fl = fopen(fname.c_str(), "rb"));
}
*/
File::~File()
{
    if(fl != NULL)
        fclose(fl);
}

void File::operator()(void * buf, const size_t size)
{
    fread(buf, 1, size, fl) != size;
    //throw_if(fread(buf, 1, size, fl) != size);
}

void File::seek(const uint32_t offset)
{
    fseek(fl, offset, SEEK_SET);
    //throw_if(fseek(fl, offset, SEEK_SET));
}

long File::offset()
{
    return ftell(fl);
}


GVektor::GVektor() :
    x(0), y(0), z(0)
{
    ;
}

GVektor::GVektor(const GVektor & v) :
    x(v.x), y(v.y), z(v.z)
{
    ;
}

GVektor::GVektor(const double t_x, const double t_y, const double t_z)
{
    x = t_x;
    y = t_y;
    z = t_z;
}

const GVektor & GVektor::operator=(const GVektor & v)
{
    x = v.x;
    y = v.y;
    z = v.z;

    return * this;
}

double GVektor::operator[](const unsigned ind) const
{
    switch(ind)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }

    //throw_;
}

double & GVektor::operator[](const unsigned ind)
{
    switch(ind)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }

    //throw_;
}

const GVektor GVektor::operator+(const GVektor & v)
{
    GVektor ret;

    ret.x = x + v.x;
    ret.y = y + v.y;
    ret.z = z + v.z;

    return ret;
}

const GVektor & GVektor::operator+=(const GVektor & v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return * this;
}

const GVektor GVektor::operator-(const GVektor & v)
{
    return GVektor(x - v.x, y - v.y, z - v.z);
}

double GVektor::euclidean_distance_to(const GVektor & op) const
{
    return sqrt(pow(x - op.x, 2) + pow(y - op.y, 2) + pow(z - op.z, 2));
}


