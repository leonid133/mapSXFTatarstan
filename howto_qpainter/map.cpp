#include "map.h"

#include <QPainter>
#include <QWheelEvent>
#include <QFileDialog>
#include <qmath.h>

void Object::init(const EObjectType __type, const unsigned __id, const unsigned __code, const unsigned __localization)
{
    id = __id;
    code = __code;
    localization = __localization;
    type = __type;
}

void Object::init(const std::vector<GVektor> __pnts, const EObjectType __type, const unsigned __id, const unsigned __code, const unsigned __localization, const STRING __label)
{
    id = __id;
    code = __code;
    localization = __localization;
    type = __type;
    label = __label;
    pnts = __pnts;
}

Object & Object::operator=(const Object & obj)
{
    id = obj.id;
    pnts = obj.pnts;
    sub_objs = obj.sub_objs;
    type = obj.type;
    code = obj.code;
    localization = obj.localization;
    label = obj.label;

    return * this;
}

void Object::add_semantics(const unsigned code, const Semantics<STRING> & sem)
{
    string_semantics[code] = sem;
};

void Object::add_semantics(const unsigned code, const Semantics<double> & sem)
{
    double_semantics[code] = sem;
};

STRING Object::semantics_value(const unsigned code, const STRING default_value) const
{
    if(string_semantics.count(code))
        return string_semantics.at(code).value;

    return default_value;
}

double Object::semantics_value(const unsigned code, const double default_value) const
{
    if(double_semantics.count(code))
        return double_semantics.at(code).value;

    return default_value;
}

int Object::cmp_double_semantics(const unsigned code, const uint64_t value, const uint64_t default_value) const
{
    if(double_semantics.count(code))
    {
        const Semantics<double> & sem = double_semantics.at(code);
        const ESemanticsType type = sem.type;
        uint64_t __value = value;
        double value_d = * ((double *) & __value);

        return sem.cmp(Semantics<double>(value_d, type));
    }
    else if(string_semantics.count(code))
    {
        //throw_;
    }
    else
    {
        // TODO default_value
    }

    return 0;
}

// ############################################################################

BaseMap::BaseMap()
{

    ;
}

void BaseMap::load(const STRING map_fname, const STRING height_map_fname, const std::vector<unsigned> codes)
{

    __load(map_fname, height_map_fname);

    // ############################################################################

    const double dx = hm.size_in_map_coord.x / (double) hm.width;
    const double dy = hm.size_in_map_coord.y / (double) hm.height;

    for(auto & obj : objs)
        obj_prepare(obj, dx, dy);

    // ############################################################################

    __codes = codes;

    cnts.clear();
    __pnts_num = 0;

    auto add_obj = [ this ](const Object & obj)
    {
        std::vector<GVektor> cnt;

        __pnts_num += obj.pnts.size();

        for(auto & pnt : obj.pnts)
            cnt.push_back(pnt);

        cnts.push_back(cnt);

    };

    for(auto & obj : objs)
        if(find(codes.begin(), codes.end(), obj.code) != codes.end())
        {
            add_obj(obj);

            for(auto & sub_obj : obj.sub_objs)
                add_obj(sub_obj);

        }
}

void BaseMap::obj_prepare(Object & obj, const double dx, const double dy)
{
    for(auto & pnt : obj.pnts)
    {
        double __dy = (pnt.y - hm.left_top.y) / dy;
        double __dx = (pnt.x - hm.left_top.x) / dx;
        const unsigned from_v = __dy;
        const unsigned from_u = __dx;
        const unsigned to_v = from_v + 1;
        const unsigned to_u = from_u + 1;

        __dy -= from_v;
        __dx -= from_u;
/*
        pnt.z =
            __dx * __dy * hm.matrix[from_v][from_u].z
            +
            __dx * (1 - __dy) * hm.matrix[from_v][to_u].z
            +
            (1 - __dx) * __dy * hm.matrix[to_v][from_u].z
            +
            (1 - __dx) * (1 - __dy) * hm.matrix[to_v][to_u].z;*/
    }

    for(auto & __obj : obj.sub_objs)
        obj_prepare(__obj, dx, dy);

}

std::vector< std::vector<GVektor> > BaseMap::contours(unsigned & pnts_num)
{
    pnts_num = __pnts_num;

    return cnts;
}



void WMap::Pars()
{
    //

    std::vector<unsigned> codes;

    if(CheckBoxs & 0x0001)
        codes.push_back( 0x1DADA80 );  // ОЗЕРА (ПОСТОЯННЫЕ)  = НАБОР
    if(CheckBoxs & 0x0002)
        codes.push_back( 0x1DB0578 );  // ВОДОХРАНИЛИЩА ДЕЙСТВУЮЩИЕ = НАБОР
    if(CheckBoxs & 0x0004)
        codes.push_back( 0x1DF4750 );  // РЕКИ ПОСТОЯНЫЕ (от 20-120 м) = ЛИНИЯ
    if(CheckBoxs & 0x0008)
        codes.push_back( 0x1DF9958 );  // КАНАЛЫ = НАБОР (ЛИНИЯ)
    if(CheckBoxs & 0x0010)
        codes.push_back( 0x1E0CDF0 );  // УРЕЗЫ ВОДЫ = ТОЧКА
    if(CheckBoxs & 0x0020)
        codes.push_back( 0x44F5CF0 );  // БОЛОТА НЕПРОХОДИМЫЕ = ШТРИХОВАННАЯ ПЛОЩАДЬ

    if(CheckBoxs & 0x0040)
        codes.push_back( 0x3A7AB40 );  // ДОРОГИ ГРУНТОВЫЕ ПРОСЕЛОЧНЫЕ = ЛИНИЯ
    if(CheckBoxs & 0x0080)
        codes.push_back( 0x3A7D250 );  // ДОРОГИ ПОЛЕВЫЕ,ЛЕСНЫЕ = ПУНКТИРНАЯ ЛИНИЯ
    if(CheckBoxs & 0x0100)
        codes.push_back( 0x3A78430 );  // УЛУЧШЕННЫЕ ГРУНТ.ДОРОГИ ДЕЙСТВ = НАБОР
    if(CheckBoxs & 0x0200)
        codes.push_back( 0x3B12120 );  // ДОРОГИ ТРУДНОПРОЕЗЖИЕ(улуч.гр) = НАБОР
    if(CheckBoxs & 0x0400)
        codes.push_back( 0x3B6D9F8 );  // МОСТЫ ПРОЧИЕ = 149 (TODO)

    if(CheckBoxs & 0x0800)
        codes.push_back( 0x3A624A0 );  // ШОССЕ УСОВЕРШЕНСТВ.(ДЕЙСТВ.) = НАБОР
    if(CheckBoxs & 0x1000)
        codes.push_back( 0x3A64BB0 );  // ШОССЕ ДЕЙСТВУЮЩИЕ  = НАБОР
    if(CheckBoxs & 0x2000)
        codes.push_back( 0x3B6CE40 );  // МОСТЫ НА РАЗОБЩЕНН.ОСНОВАНИЯХ = 149 (TODO)
    codes.push_back( 0x56E1361 );  //Labels
    loadOk = false;

    if(file_map_sxf>0)
    {
       if(map != 0)
       {
           delete map;
           map = 0;
       }

       map = new SXFMap();
        //STRING filesxf = file_map_sxf.toStdString();
       STRING filesxf = file_map_sxf;
       STRING filersc =  ""; //D:\\sxf\\OSM.rsc";


       map->load(filesxf, filersc, codes);

       if(!cnts.empty())
       {
           //cnts.erase(cnts.begin(), cnts.end());
           cnts.clear();
       }

       unsigned int pnts_num;
       cnts = map->contours(pnts_num);

       loadOk = true;
    }

}

WMap::WMap(QWidget * parent) : QWidget(parent)
{
    CheckBoxs = 0x3FFF;
    cnts.reserve(100000);

    m_scale = 50;
    m_x=0;
    m_y=0;
    file_map_sxf = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("Открыть"), "", "DB File (*.sxf)");

    if(file_map_sxf>0)
    {
        Pars();
    }

    realpos_point_x = cnts[0][0].x;
    realpos_point_y = cnts[0][0].y;
    setMouseTracking(true);

}

void WMap::SetFileNameSlot()
{
    file_map_sxf = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("Открыть"),
                         "",
                         "DB File (*.sxf)");

    if(file_map_sxf>0)
    {
        Pars();
    }
}

void WMap::SlotSetBox1()
{
    CheckBoxs ^= 0x0001;
   // Pars();
    this->repaint();
}
void WMap::SlotSetBox2()
{
    CheckBoxs ^= 0x0002;
   // Pars();
    this->repaint();
}
void WMap::SlotSetBox3()
{
    CheckBoxs ^= 0x0004;
    //Pars();
    this->repaint();
}
void WMap::SlotSetBox4()
{
    CheckBoxs ^= 0x0008;
    //Pars();
    this->repaint();
}
void WMap::SlotSetBox5()
{
    CheckBoxs ^= 0x0010;
    //Pars();
    this->repaint();
}
void WMap::SlotSetBox6()
{
    CheckBoxs ^= 0x0020;
    //Pars();
    this->repaint();
}
void WMap::SlotSetBox7()
{
    CheckBoxs ^= 0x0040;
    //Pars();
    this->repaint();
}
void WMap::SlotSetBox8()
{
    CheckBoxs ^= 0x0080;
    //Pars();
    this->repaint();
}
void WMap::SlotSetBox9()
{
    CheckBoxs ^= 0x0100;
    //Pars();
    this->repaint();
}
void WMap::SlotSetBox10()
{
    CheckBoxs ^= 0x0200;
    //Pars();
    this->repaint();
}
void WMap::SlotSetBox11()
{
    CheckBoxs ^= 0x0400;
    //Pars();
    this->repaint();
}
void WMap::SlotSetBox12()
{
    CheckBoxs ^= 0x0800;
    //Pars();
    this->repaint();
}
void WMap::SlotSetBox13()
{
    CheckBoxs ^= 0x1000;
    //Pars();
    this->repaint();
}
void WMap::SlotSetBox14()
{
    CheckBoxs ^= 0x2000;
    //Pars();
    this->repaint();
}
void WMap::SlotSetBox15()
{
    CheckBoxs ^= 0x4000;
    this->repaint();
}
void WMap::SlotSetBox16()
{
    CheckBoxs ^= 0x8000;
    this->repaint();
}

QPointF WMap::GeoToMap(const GVektor &geocoord)
{
        QPointF result;
        double startx, starty;
        double scale=m_scale*10;
        startx = realpos_point_x + m_x/scale;
        starty = realpos_point_y + m_y/scale;

        result.setX((geocoord.x-startx )*scale);
        result.setY((geocoord.y-starty)*scale);

        return result;
}

void WMap::paintEvent(QPaintEvent *) {
    QPainter p_wind(this);

    p_wind.setPen(QPen(Qt::red,1,Qt::SolidLine)); //настройки рисования
    p_wind.setBrush(Qt::Dense7Pattern);
    p_wind.setFont(QFont("Arial", 15));

    if(loadOk && !cnts.empty())
    {

        int  i=0, i2=0, sizeX, sizeY;
        double x, y;
        double scale=m_scale*10;
        double startx, starty;
        bool new_obj_f;
        std::vector< Object >::iterator obj_it;

        startx = realpos_point_x + m_x/scale;
        starty = realpos_point_y + m_y/scale;
        sizeX = width()*0.5;
        sizeY = height()*0.5;
        QPoint pxx(sizeX,sizeY);
        p_wind.setBrush(Qt::NoBrush);
        QFont serifFont("Times", 15);
        p_wind.setFont(serifFont);
        p_wind.drawEllipse(mouse_coord, scale*0.1, scale*0.1);



        i=0;

        std::vector< std::vector<GVektor> >::iterator iterlvl2; // итератор для второго измерения.
        std::vector< GVektor >::iterator iterlvl1; // итератор для первого измерения
        QPoint p(100,100);
        sizeX = cnts.size();

        max_point_y = max_point_x = -999999999;
        min_point_y = min_point_x = 999999999;
        w = width();
        h = height();

        for (iterlvl2=cnts.begin();iterlvl2 != cnts.end();iterlvl2++)
        {
            for (iterlvl1=(*iterlvl2).begin();iterlvl1 != (*iterlvl2).end();iterlvl1++)
            {
                QPointF point( GeoToMap(cnts[i][i2]) );
                if(point.x()>0 && point.y()>0 && point.x()<width() && point.y()< height())
                {
                    p_wind.drawPoint(point);
                    if(cnts[i][i2].x>max_point_x)max_point_x=cnts[i][i2].x;
                    if(cnts[i][i2].y>max_point_y)max_point_y=cnts[i][i2].y;
                    if(cnts[i][i2].x<min_point_x)min_point_x=cnts[i][i2].x;
                    if(cnts[i][i2].y<min_point_y)min_point_y=cnts[i][i2].y;
                }
                i2++;
            }
            i++;
            i2=0;
        }

        std::vector<unsigned> codes;
        if(CheckBoxs & 0x0001)
            codes.push_back( 0x1DADA80 );  // ОЗЕРА (ПОСТОЯННЫЕ)  = НАБОР
        if(CheckBoxs & 0x0002)
            codes.push_back( 0x1DB0578 );  // ВОДОХРАНИЛИЩА ДЕЙСТВУЮЩИЕ = НАБОР
        if(CheckBoxs & 0x0004)
            codes.push_back( 0x1DF4750 );  // РЕКИ ПОСТОЯНЫЕ (от 20-120 м) = ЛИНИЯ
        if(CheckBoxs & 0x0008)
            codes.push_back( 0x1DF9958 );  // КАНАЛЫ = НАБОР (ЛИНИЯ)
        if(CheckBoxs & 0x0010)
            codes.push_back( 0x1E0CDF0 );  // УРЕЗЫ ВОДЫ = ТОЧКА
        if(CheckBoxs & 0x0020)
            codes.push_back( 0x44F5CF0 );  // БОЛОТА НЕПРОХОДИМЫЕ = ШТРИХОВАННАЯ ПЛОЩАДЬ

        if(CheckBoxs & 0x0040)
            codes.push_back( 0x3A7AB40 );  // ДОРОГИ ГРУНТОВЫЕ ПРОСЕЛОЧНЫЕ = ЛИНИЯ
        if(CheckBoxs & 0x0080)
            codes.push_back( 0x3A7D250 );  // ДОРОГИ ПОЛЕВЫЕ,ЛЕСНЫЕ = ПУНКТИРНАЯ ЛИНИЯ
        if(CheckBoxs & 0x0100)
            codes.push_back( 0x3A78430 );  // УЛУЧШЕННЫЕ ГРУНТ.ДОРОГИ ДЕЙСТВ = НАБОР
        if(CheckBoxs & 0x0200)
            codes.push_back( 0x3B12120 );  // ДОРОГИ ТРУДНОПРОЕЗЖИЕ(улуч.гр) = НАБОР
        if(CheckBoxs & 0x0400)
            codes.push_back( 0x3B6D9F8 );  // МОСТЫ ПРОЧИЕ = 149 (TODO)

        if(CheckBoxs & 0x0800)
            codes.push_back( 0x3A624A0 );  // ШОССЕ УСОВЕРШЕНСТВ.(ДЕЙСТВ.) = НАБОР
        if(CheckBoxs & 0x1000)
            codes.push_back( 0x3A64BB0 );  // ШОССЕ ДЕЙСТВУЮЩИЕ  = НАБОР
        if(CheckBoxs & 0x2000)
            codes.push_back( 0x3B6CE40 );  // МОСТЫ НА РАЗОБЩЕНН.ОСНОВАНИЯХ = 149 (TODO)
         codes.push_back( 0x56E1361 );  //Labels

        
        if(CheckBoxs & 0x4000 || CheckBoxs & 0x8000)
        for(obj_it=map->objs.begin();obj_it != map->objs.end(); obj_it++)
        {
            bool flag_obj=false;
            for(auto codes_it=codes.begin(); codes_it != codes.end(); codes_it++)
                if( (*codes_it) == (*obj_it).code ) flag_obj=true;
            if(!flag_obj)continue;
            std::vector<GVektor> pnts = (*obj_it).pnts;
            sxf::EObjectType type;
            type =(*obj_it).type; // EOT_NOT_DRAW, EOT_POINT, EOT_LINE, EOT_POLYGON, EOT_TEXT
            //QString label = QString( (*obj_it).label.c_str() );
            QString label = (*obj_it).label;
            //p_wind.drawText(mouse_coord, label);

            switch ((*obj_it).code) {
            case 0x1DF4750: //реки
                p_wind.setPen(QPen(Qt::blue,1,Qt::SolidLine));
                p_wind.setBrush(Qt::HorPattern);
                break;
            case 0x3A64BB0: //шоссе действующие
                p_wind.setPen(QPen(Qt::black,1,Qt::SolidLine));
                p_wind.setBrush(Qt::VerPattern);
                break;
            case 0x3B6D9F8: //мосты (прочее)
                p_wind.setPen(QPen(Qt::yellow,1,Qt::SolidLine));
                p_wind.setBrush(Qt::Dense2Pattern);
                break;
            case 4:
                p_wind.setPen(QPen(Qt::magenta,1,Qt::SolidLine));
                p_wind.setBrush(Qt::Dense3Pattern);
                break;
            case 5:
                p_wind.setPen(QPen(Qt::green,1,Qt::SolidLine));
                p_wind.setBrush(Qt::BDiagPattern);
                break;
            default:
                p_wind.setPen(QPen(Qt::green,1,Qt::SolidLine));
                p_wind.setBrush(Qt::BDiagPattern);
                break;
            }
             std::vector<GVektor>::iterator pnts_it;
            switch (type){
            case EOT_NOT_DRAW:
                break;
            case EOT_POINT:
                //if(CheckBoxs & 0x4000)
                for(pnts_it=pnts.begin();pnts_it != pnts.end(); pnts_it++)
                {

                    QPointF point( GeoToMap(*pnts_it) );
                    if(point.x()>0 && point.y()>0 && point.x()<width() && point.y()< height())
                    {
                        p_wind.drawPoint(point);
                    }

                }
                break;
            case EOT_LINE:
                new_obj_f = false;
                if(CheckBoxs & 0x4000)
                for(pnts_it=pnts.begin();pnts_it != pnts.end(); pnts_it++)
                {
                    QPointF point( GeoToMap(*pnts_it) );
                    if(point.x()>0 && point.y()>0 && point.x()<width() && point.y()< height())
                    {
                        p_wind.drawPoint(point);
                        if(new_obj_f) p_wind.drawLine(point, p);
                        new_obj_f = true;

                        if(abs(point.x() - m_coord_SelectObj.x())<20 && abs(point.y() - m_coord_SelectObj.y())<20){
                            QString txt = "Label = ";
                            txt +=(*obj_it).label;
                            txt += "; info=";
                            txt += sxf::EObjectType(type);
                            txt += ";";
                            txt += pnts.size();
                            //txt += (*obj_it).string_semantics;
                            p_wind.setPen(QPen(Qt::red,1,Qt::SolidLine));
                            p_wind.setBrush(Qt::Dense7Pattern);
                            p_wind.setFont(QFont("Arial", 15));
                            //p_wind.drawText(m_coord_SelectObj, txt);
                        }
                    }
                    p.setX(point.x());
                    p.setY(point.y());
                }
                break;
            case EOT_POLYGON:
                QPoint *poligon;
                poligon = new QPoint[int(pnts.size())];
                i = 0;
                new_obj_f = false;
                if(CheckBoxs & 0x8000)
                for(pnts_it=pnts.begin();pnts_it != pnts.end(); pnts_it++)
                {
                    QPointF point( GeoToMap(*pnts_it) );

                    if(point.x()>0 && point.y()>0 && point.x()<width() && point.y()< height())
                    {
                        pxx.setX(point.x());
                        pxx.setY(point.y());
                        if(new_obj_f)poligon[i++] = pxx;
                        new_obj_f = true;
                        if(abs(point.x() - m_coord_SelectObj.x())<20 && abs(point.y() - m_coord_SelectObj.y())<20){
                            QString txt = "Label = ";
                            txt +=(*obj_it).label;
                            txt += "; info=";
                            txt += sxf::EObjectType(type);
                            txt += ";";
                            txt += pnts.size();
                            //txt += (*obj_it).string_semantics;
                            p_wind.setPen(QPen(Qt::black,1,Qt::SolidLine));
                            p_wind.setBrush(Qt::Dense7Pattern);
                            p_wind.setFont(QFont("Arial", 15));
                            //p_wind.drawText(m_coord_SelectObj, txt);
                        }
                    }
                    else if(new_obj_f)
                    {
                        pxx.setX(point.x());
                        pxx.setY(point.y());
                        if(new_obj_f)poligon[i++] = pxx;
                            new_obj_f = true;
                    }
                }
                if(new_obj_f)p_wind.drawPolygon(poligon, i, Qt::WindingFill);
                if(poligon)delete [] poligon;
                break;

            case EOT_TEXT:
                //if(CheckBoxs & 0x8000)
                {
                new_obj_f = false;

                for(pnts_it=pnts.begin();pnts_it != pnts.end(); pnts_it++)
                    {
                        GVektor point = (*pnts_it);
                        x = (point.x-startx )*scale;
                        y = (point.y-starty)*scale;
                        if(x>0 && y>0 && x<width() && y<height())
                        {
                            if(abs(x - m_coord_SelectObj.x())<50 && abs(y - m_coord_SelectObj.y())<50){
                                p_wind.setPen(QPen(Qt::red,1,Qt::SolidLine));
                                p_wind.setBrush(Qt::Dense7Pattern);
                                p_wind.setFont(QFont("Arial", 15));
                            }
                            else
                            {
                                p_wind.setPen(QPen(Qt::green,1,Qt::SolidLine));
                                p_wind.setBrush(Qt::Dense7Pattern);
                                p_wind.setFont(QFont("Arial", 8));
                            }
                            pxx.setX(x);
                            pxx.setY(y);
                            if(!new_obj_f)
                            {
                                p_wind.drawText(pxx, label);
                                new_obj_f = true;
                            }
                        }
                    }
                }
                break;
            }
        }
    }
}
void WMap::mouseMoveEvent(QMouseEvent*pe)
{
    mouse_delta_x = (pe->globalX() - mouse_delta_x);
    mouse_delta_y = (pe->globalY() - mouse_delta_y);
    if(pe->buttons() & Qt::LeftButton)
    {
        m_x -= mouse_delta_x;
        m_y -= mouse_delta_y;
        if(loadOk)this->repaint();
    }
    mouse_delta_x = pe->globalX();
    mouse_delta_y = pe->globalY();
    mouse_coord = pe->pos();
    m_coord_SelectObj.setX(pe->localPos().x());
    m_coord_SelectObj.setY(pe->localPos().y());
}

void WMap::mousePressEvent(QMouseEvent *pe)
{
    m_coord_SelectObj.setX(pe->localPos().x());
    m_coord_SelectObj.setY(pe->localPos().y());
    if(loadOk)this->repaint();

}

void WMap::mouseDoubleClickEvent(QMouseEvent *pe)
{
    m_scale=50;
    m_x=0;
    m_y=0;
    realpos_point_x = min_point_x = max_point_x = cnts[0][0].x;
    realpos_point_y = min_point_y = max_point_y = cnts[0][0].y;
    mouse_delta_x = (pe->globalX());
    mouse_delta_y = (pe->globalY());
    this->repaint();
}
void WMap::wheelEvent(QWheelEvent *event)
{

    int numDegrees = event->delta() / 8;
         int numSteps = 5*numDegrees / 15;

         if (event->orientation() == Qt::Horizontal) {
             //scrollHorizontally(numSteps);
         } else {
             //scrollVertically(numSteps);
             realpos_point_x = min_point_x;
             realpos_point_y = min_point_y;
             m_x = 10*numSteps*(max_point_x-min_point_x)*(mouse_coord.x()/w);// -10*m_scale*(mouse_coord.x()/(w*1.0))*(max_point_x - min_point_x);
             m_y = 10*numSteps*(max_point_y-min_point_y)*(mouse_coord.y()/h);//-10*m_scale*(mouse_coord.y()/(h*1.0))*(max_point_y - min_point_y);
             m_scale += numSteps;

             this->repaint();
         }
         event->accept();
}
