#include <lib/sxf.h>
//#include <lib/all.h>

#include <common.h>
#include <map.h>
#include <QTextCodec>

std::vector<Object> SXFMap::s_map::load(const QString fname)
{
    int num;

    File fl( fname.toStdString().c_str() );
    //File fl(fname.c_str());

    fl(& header, sizeof(header));
    unpack_header();

    frame_min = cmp_frame(true);
    scale = header.points_per_meter / (double) header.scale;

    fl(& data_desc, sizeof(data_desc));
    unpack_data_desc();

    check();

    objs.clear();

    for(num = data_desc.record_num; num > 0; num--)
        read_next_obj(fl);

    return objs;
}

void SXFMap::s_map::check()
{
    ; // TODO
}

void SXFMap::s_map::unpack_header()
{
    File::unpack<uint32_t>(& header.id);
    File::unpack<uint32_t>(& header.len);
    File::unpack<uint32_t>(& header.version);
    File::unpack<uint32_t>(& header.checksum);
    File::unpack<uint8_t>((uint8_t *) & header.date, 12);
    File::unpack<uint8_t>((uint8_t *) & header.nomenclature, 32);
    File::unpack<uint32_t>(& header.scale);
    File::unpack<uint8_t>((uint8_t *) & header.list_name, 32);
    File::unpack<uint32_t>((uint32_t *) & header.flags); // TODO Нужно ли?
    File::unpack<uint32_t>(& header.epsg);
    File::unpack<double>(& header.rectangle.south_west.x);
    File::unpack<double>(& header.rectangle.south_west.y);
    File::unpack<double>(& header.rectangle.north_west.x);
    File::unpack<double>(& header.rectangle.north_west.y);
    File::unpack<double>(& header.rectangle.north_east.x);
    File::unpack<double>(& header.rectangle.north_east.y);
    File::unpack<double>(& header.rectangle.south_east.x);
    File::unpack<double>(& header.rectangle.south_east.y);
    File::unpack<double>(& header.geodesy.south_west.x);
    File::unpack<double>(& header.geodesy.south_west.y);
    File::unpack<double>(& header.geodesy.north_west.x);
    File::unpack<double>(& header.geodesy.north_west.y);
    File::unpack<double>(& header.geodesy.north_east.x);
    File::unpack<double>(& header.geodesy.north_east.y);
    File::unpack<double>(& header.geodesy.south_east.x);
    File::unpack<double>(& header.geodesy.south_east.y);
    File::unpack<uint8_t>(& header.ellipsoid);
    File::unpack<uint8_t>(& header.h);
    File::unpack<uint8_t>(& header.proj);
    File::unpack<uint8_t>(& header.coord_system);
    File::unpack<uint8_t>(& header.plan_unit);
    File::unpack<uint8_t>(& header.h_unit);
    File::unpack<uint8_t>(& header.border_type);
    File::unpack<uint8_t>(& header.map_type);
    File::unpack<uint8_t>(header.not_used_1, 64);
    File::unpack<double>(& header.not_used_2);
    File::unpack<uint32_t>(& header.points_per_meter);
    File::unpack<uint32_t>(& header.frame.south_west.x);
    File::unpack<uint32_t>(& header.frame.south_west.y);
    File::unpack<uint32_t>(& header.frame.north_west.x);
    File::unpack<uint32_t>(& header.frame.north_west.y);
    File::unpack<uint32_t>(& header.frame.north_east.x);
    File::unpack<uint32_t>(& header.frame.north_east.y);
    File::unpack<uint32_t>(& header.frame.south_east.x);
    File::unpack<uint32_t>(& header.frame.south_east.y);
    File::unpack<uint32_t>(& header.frame_classification_code);
    File::unpack<double>(header.not_used_6, 6);
}

void SXFMap::s_map::unpack_data_desc()
{
    File::unpack<uint32_t>(& data_desc.id);
    File::unpack<uint32_t>(& data_desc.len);
    File::unpack<uint8_t>((uint8_t *) data_desc.nomenclature, 32);
    File::unpack<uint32_t>(& data_desc.record_num);
    File::unpack<uint32_t>((uint32_t *) & header.flags);
    File::unpack<uint32_t>(& data_desc.not_used);
}

void SXFMap::s_map::unpack_record(SRecord & record)
{
    File::unpack<uint32_t>(& record.id);
    File::unpack<uint32_t>(& record.len);
    File::unpack<uint32_t>(& record.metrics_len);
    File::unpack<uint32_t>(& record.classification_code);
    File::unpack<uint32_t>(& record.record_id.full);
    File::unpack<uint8_t>((uint8_t *) & record.gen_level);
    File::unpack<uint32_t>(& record.m_elem_num_big);
    File::unpack<uint16_t>(& record.sub_object_num);
    File::unpack<uint16_t>(& record.m_elem_num);
}

uint8_t * SXFMap::s_map::read_pnt(std::vector<GVektor> & pnt, const SRecord & desc, uint8_t * buf, const unsigned pnt_num, const unsigned dim, const bool is_float, const bool is_large)
{
    // TODO Векторное представление

    unsigned ind;
    GVektor t_pnt;

    #define SET_POINT(type, unpack_type) \
    for(ind = 0; ind < pnt_num; ind ++)\
    {\
        type * p_buf = (type *) buf;\
        \
        File::unpack<unpack_type>((unpack_type *) p_buf, dim);\
        buf += sizeof(type) * dim;\
        \
        t_pnt.x = p_buf[0] * scale + header.rectangle.north_west.x;\
        t_pnt.y = p_buf[1] * scale + header.rectangle.north_west.y;\
        t_pnt.z = desc.flags.dim ? p_buf[2] : 0;\
        \
        pnt.push_back(t_pnt);\
    }

    pnt.clear();

    if(is_float)
    {
        if(is_large)
            SET_POINT(double, double)
        else
            SET_POINT(float, float);
    }
    else
    {
        if(is_large)
            SET_POINT(int32_t, uint32_t)
        else
            SET_POINT(int16_t, uint16_t);
    }

    return buf;
}

uint8_t * SXFMap::s_map::read_label(QString & label, uint8_t * buf)
{

    char * p_buf = (char *) buf;
    const unsigned len = * p_buf;
    //unsigned len = * p_buf;
    unsigned v;
    if(len>50)
        return buf;
   p_buf++;
/*
    for(v = 0, label = ""; v < len; v++, p_buf++)
        label += (*p_buf);

    p_buf++;
*/


    QByteArray byteArray = p_buf;
    QTextCodec::ConverterState state;
    QTextCodec *codec = QTextCodec::codecForName("UTF-16");
    if(byteArray.size() < (len-3))
    {
        label=codec->toUnicode(byteArray.constData(), byteArray.size(), &state) ;

    }
    else
    {
        codec = QTextCodec::codecForName("UTF-8");

        label=codec->toUnicode(byteArray.constData(), byteArray.size(), &state) ;
        if (state.invalidChars > 0) {
            codec = QTextCodec::codecForName("CP1251");

            label=codec->toUnicode(byteArray.constData(), byteArray.size(), &state) ;

            if (state.invalidChars > 0) {

              qDebug() << "Invalid File Format\n" ;
            }
        }
    }
    return buf;

    /*label = codec->toUnicode(byteArray.constData(), byteArray.size(), &state);
      if (state.invalidChars > 0) {
        codec = QTextCodec::codecForLocale() ;
        label=codec->toUnicode(byteArray.constData(), byteArray.size(), &state) ;
        if (state.invalidChars > 0) {
          qDebug() << "Invalid File Format\n" ;
        }
      }
*/

    /*

*/

    //label = codepage::ansi_to_utf8(label);

   // return (uint8_t *) p_buf;

}

void SXFMap::s_map::read_next_obj(File & fl)
{
    std::shared_ptr<uint8_t> buf;
    uint8_t * p_buf=0;
    unsigned v;
    SRecord desc;
    EObjectType type;

    fl(& desc, sizeof(desc));
    unpack_record(desc);

    switch(desc.flags.localization)
    {
        case 0:
        case 4:
        {
            type = EOT_LINE;

            break;
        }
        case 1:
        {
            type = EOT_POLYGON;

            break;
        }
        case 2:
        {
            type = EOT_POINT;

            break;
        }
        case 3:
        {
            type = EOT_TEXT;

            break;
        }
        default:
        {
            type = EOT_NOT_DRAW;

            break;
        }
    }

    if(desc.classification_code == header.frame_classification_code)
        type = EOT_NOT_DRAW;

    objs.resize(objs.size() + 1);

    std::vector< Object >::iterator current_obj = objs.end() - 1;
    const unsigned buf_size = desc.len - sizeof(desc);
    const unsigned dim = desc.flags.dim ? 3 : 2;
    const bool is_float = desc.flags.m_elem_type;
    const bool is_large = desc.flags.m_elem_len;
    const unsigned pnt_num = (desc.m_elem_num == 0xFFFF) ? desc.m_elem_num_big : desc.m_elem_num;

    current_obj->init(type, desc.record_id.full, desc.classification_code, desc.flags.localization);

    buf.reset(new uint8_t[buf_size], std::default_delete<uint8_t[]>());
    try{
      if(!p_buf)p_buf = buf.get();
    }
    catch(...){}

    //throw_null(p_buf = buf.get());
    fl(p_buf, buf_size);

    p_buf = read_pnt(current_obj->pnts, desc, p_buf, pnt_num, dim, is_float, is_large);

    if(type == EOT_TEXT)
    {
        try{
            if(!p_buf)
                ;
            else
                p_buf = read_label(current_obj->label, p_buf);
        }
        catch(...){}

    }
    current_obj->sub_objs.resize(desc.sub_object_num);

    for(v = 0; v < desc.sub_object_num; v++)
    {
        QString label;
        std::vector<GVektor> t_pnt;

        File::unpack<uint16_t>((uint16_t *) p_buf, 2);

        const uint16_t t_pnt_num = * (((uint16_t *) p_buf) + 1);

        p_buf = read_pnt(t_pnt, desc, p_buf + 4, t_pnt_num, dim, is_float, is_large);

        if(type == EOT_TEXT)
        {
            p_buf = read_label(label, p_buf);
        }

        current_obj->sub_objs[v].init(t_pnt, type, desc.record_id.full, desc.classification_code, desc.flags.localization, label);
    }

    // ############################################################################
    // Семантика

    p_buf = buf.get() + desc.metrics_len;
    unsigned processing_byte = desc.metrics_len;

    while(processing_byte < buf_size)
    {
        // TODO unpack

        const unsigned code = * ((uint16_t *) p_buf);
        const unsigned type = p_buf[2];
        const int scale = p_buf[3];
        const unsigned scale_u = p_buf[3];
        p_buf += 4;

        switch(type)
        {
            case 0:		// ASCIIZ
            case 126:	// ANSI (Windows)
            case 127:	// Unicode
            {
                current_obj->add_semantics(code, Semantics<QString>((char *) p_buf, (ESemanticsType) type));
                p_buf += scale_u + 1;
                processing_byte += 4 + scale_u + 1;

                break;
            }

#define DIGIT(tp_code, tp)\
            case tp_code:\
            {\
                current_obj->add_semantics(code, Semantics<double>(* ((tp *) p_buf) * pow(10, scale), (ESemanticsType) type));\
                p_buf += tp_code;\
                processing_byte += 4 + tp_code;\
            \
                break;\
            }

            DIGIT(1, int8_t)
            DIGIT(2, int16_t)
            DIGIT(4, int32_t)
            DIGIT(8, double)
        }
    }
}

GVektor SXFMap::s_map::cmp_rectangle(const bool is_min) const
{
    std::vector<double>
        border_x =
        {
            header.rectangle.south_west.x,
            header.rectangle.north_west.x,
            header.rectangle.north_east.x,
            header.rectangle.south_east.x
        },
        border_y =
        {
            header.rectangle.south_west.y,
            header.rectangle.north_west.y,
            header.rectangle.north_east.y,
            header.rectangle.south_east.y
        };

    return GVektor(
        is_min ? (* min_element(border_x.begin(), border_x.end())) : (* max_element(border_x.begin(), border_x.end())),
        is_min ? (* min_element(border_y.begin(), border_y.end())) : (* max_element(border_y.begin(), border_y.end())),
        0
        );
}

GVektor SXFMap::s_map::cmp_frame(const bool is_min) const
{
    std::vector<uint32_t>
        border_x =
        {
            header.frame.south_west.x,
            header.frame.north_west.x,
            header.frame.north_east.x,
            header.frame.south_east.x
        },
        border_y =
        {
            header.frame.south_west.y,
            header.frame.north_west.y,
            header.frame.north_east.y,
            header.frame.south_east.y
        };

    return GVektor(
        is_min ? (* min_element(border_x.begin(), border_x.end())) : (* max_element(border_x.begin(), border_x.end())),
        is_min ? (* min_element(border_y.begin(), border_y.end())) : (* max_element(border_y.begin(), border_y.end())),
        0
        );
}



