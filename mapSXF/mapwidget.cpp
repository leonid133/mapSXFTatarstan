#include "mapwidget.h"

#include <QPainter>
#include <QWheelEvent>
#include <QFileDialog>

void MapWidget::RePars()
{
    loadOk = false;
    if(file_map_sxf>0)
    {
       /*
        obj_river->LoadFromFile(file_map_sxf);
        obj_ozera->LoadFromFile(file_map_sxf);
        obj_vodohranil->LoadFromFile(file_map_sxf);
        */
        ob[0]->LoadFromFile(file_map_sxf);
        loadOk = true;
    }

/*
    CSXFMap map;
    unsigned pnts_num;
    vector<unsigned> codes;
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
    loadOk = false;
    if(file_map_sxf>0)
    {
       std::string filesxf = file_map_sxf.toStdString();
       std::string filersc =  ""; //D:\\sxf\\OSM.rsc";
       map.load(filesxf, filersc, codes);
       if(!cnts.empty())
       {
           //cnts.erase(cnts.begin(), cnts.end());
           cnts.clear();
       }

       cnts = map.contours(pnts_num);
       objs = map.objs;
       loadOk = true;
    }*/

}

MapWidget::MapWidget(QWidget * parent) : QWidget(parent), /*p_wind(new QPainter),*/
    obj_ozera(new ObjOzera), obj_vodohranil(new ObjVodohranil),
    obj_river(new ObjRiver)
{
    //obj_river = new ObjRiver();
  ob = new BaseObject *[24];
  ob[0] = new ObjRiver();
  CheckBoxs = 0x3FFF;

    m_scale = 50;
    m_x=0;
    m_y=0;
    file_map_sxf = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("Открыть"), "", "DB File (*.sxf)");

    if(file_map_sxf>0)
    {
        RePars();
    }
    /*
    realpos_point_x = cnts[0][0].x;
    realpos_point_y = cnts[0][0].y;
    */
    setMouseTracking(true);
}

void MapWidget::SetFileNameSlot()
{
    file_map_sxf = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("Открыть"),
                         "",
                         "DB File (*.sxf)");

    if(file_map_sxf>0)
    {
        RePars();
    }
}

void MapWidget::SlotSetBox1()
{
    CheckBoxs ^= 0x0001;
    //RePars();
    this->repaint();
}
void MapWidget::SlotSetBox2()
{
    CheckBoxs ^= 0x0002;
    //RePars();
    this->repaint();
}
void MapWidget::SlotSetBox3()
{
    CheckBoxs ^= 0x0004;
    //RePars();
    this->repaint();
}
void MapWidget::SlotSetBox4()
{
    CheckBoxs ^= 0x0008;
    //RePars();
    this->repaint();
}
void MapWidget::SlotSetBox5()
{
    CheckBoxs ^= 0x0010;
    //RePars();
    this->repaint();
}
void MapWidget::SlotSetBox6()
{
    CheckBoxs ^= 0x0020;
    //RePars();
    this->repaint();
}
void MapWidget::SlotSetBox7()
{
    CheckBoxs ^= 0x0040;
    //RePars();
    this->repaint();
}
void MapWidget::SlotSetBox8()
{
    CheckBoxs ^= 0x0080;
    //RePars();
    this->repaint();
}
void MapWidget::SlotSetBox9()
{
    CheckBoxs ^= 0x0100;
    //RePars();
    this->repaint();
}
void MapWidget::SlotSetBox10()
{
    CheckBoxs ^= 0x0200;
    //RePars();
    this->repaint();
}
void MapWidget::SlotSetBox11()
{
    CheckBoxs ^= 0x0400;
    //RePars();
    this->repaint();
}
void MapWidget::SlotSetBox12()
{
    CheckBoxs ^= 0x0800;
    //RePars();
    this->repaint();
}
void MapWidget::SlotSetBox13()
{
    CheckBoxs ^= 0x1000;
    //RePars();
    this->repaint();
}
void MapWidget::SlotSetBox14()
{
    CheckBoxs ^= 0x2000;
    //RePars();
    this->repaint();
}
void MapWidget::SlotSetBox15()
{
    CheckBoxs ^= 0x4000;
    this->repaint();
}
void MapWidget::SlotSetBox16()
{
    CheckBoxs ^= 0x8000;
    this->repaint();
}

void MapWidget::paintEvent(QPaintEvent *) {

    QPainter p_wind(this);
    QPixmap qq;

    p_wind.setPen(QPen(Qt::red,1,Qt::SolidLine)); //настройки рисования

    if(loadOk) // && !cnts.empty())
    {
        p_wind.drawEllipse(mouse_coord, m_scale, m_scale);
        max_point_y = max_point_x = -999999999;
        min_point_y = min_point_x = 999999999;
        w = width();
        h = height();

        if(CheckBoxs & 0x0001)
           //obj_ozera->Drow(*this);
        if(CheckBoxs & 0x0002)
           //obj_vodohranil->Drow(*this);
        if(CheckBoxs & 0x0004)
           ob[0]->Drow(*this);
           //obj_river->Drow(*this);
    }
}
void MapWidget::mouseMoveEvent(QMouseEvent*pe)
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
}

void MapWidget::mouseDoubleClickEvent(QMouseEvent *pe)
{
    m_scale=50;
    m_x=0;
    m_y=0;
    //realpos_point_x = min_point_x = max_point_x = cnts[0][0].x;
    //realpos_point_y = min_point_y = max_point_y = cnts[0][0].y;
    mouse_delta_x = (pe->globalX());
    mouse_delta_y = (pe->globalY());
    this->repaint();
}
void MapWidget::wheelEvent(QWheelEvent *event)
{

    int numDegrees = event->delta() / 8;
         int numSteps = 5*numDegrees / 15;

         if (event->orientation() == Qt::Horizontal) {
             //scrollHorizontally(numSteps);
         } else {
             //scrollVertically(numSteps);
             realpos_point_x = min_point_x;
             realpos_point_y = min_point_y;
             m_x = 10*numSteps*(max_point_x - min_point_x)*(mouse_coord.x()/w);// -10*m_scale*(mouse_coord.x()/(w*1.0))*(max_point_x - min_point_x);
             m_y = 10*numSteps*(max_point_y - min_point_y)*(mouse_coord.y()/h);//-10*m_scale*(mouse_coord.y()/(h*1.0))*(max_point_y - min_point_y);
             m_scale += numSteps;

            this->repaint();
         }
         event->accept();
}

QPointF MapWidget::GeoToMap(const vektor &geocoord)
{
    QPointF result;
    double startx, starty;
    double scale=m_scale*10;
    startx = realpos_point_x + m_x/scale;
    starty = realpos_point_y + m_y/scale;

    result.setX((geocoord.x-startx )*scale);
    result.setY((geocoord.y-starty)*scale);
    if(geocoord.x>max_point_x)max_point_x=geocoord.x;
    if(geocoord.y>max_point_y)max_point_y=geocoord.y;
    if(geocoord.x<min_point_x)min_point_x=geocoord.x;
    if(geocoord.y<min_point_y)min_point_y=geocoord.y;

    return result;
}

void BaseObject::LoadFromFile(QString file_map_sxf){
    unsigned pnts_num;

    loadOk=false;
    CSXFMap map;
    if(file_map_sxf>0)
    {
        std::string filesxf = file_map_sxf.toStdString();
        std::string filersc =  ""; //D:\\sxf\\OSM.rsc";
        map.load(filesxf, filersc, codes);
        if(!cnts.empty())
        {
            //cnts.erase(cnts.begin(), cnts.end());
            cnts.clear();
        }
        cnts.reserve(10000);
        cnts = map.contours(pnts_num);
        objs = map.objs;
        loadOk = true;
    }
}

void BaseObject::Drow(MapWidget &mapWidget){
    mapWidget.realpos_point_x = cnts[0][0].x;
    mapWidget.realpos_point_y = cnts[0][0].y;
    QPainter p_wind(&mapWidget);

    p_wind.setPen(pen_style);
    p_wind.setBrush(brush_style);
    p_wind.setFont(font_style);

    int i=0, i2=0;
    bool new_obj_f = false;

    std::vector< CObject >::iterator obj_it;
    std::vector< std::vector<vektor> >::iterator iterlvl2; // итератор для второго измерения.
    std::vector< vektor >::iterator iterlvl1; // итератор для первого измерения

    if(loadOk)
    {

        for (iterlvl2=cnts.begin();iterlvl2 != cnts.end();iterlvl2++)
        {
            for (iterlvl1=(*iterlvl2).begin();iterlvl1 != (*iterlvl2).end();iterlvl1++)
            {
                QPointF point( mapWidget.GeoToMap(cnts[i][i2]) );
                if(point.x()>0 && point.y()>0 && point.x()<mapWidget.width() && point.y()<mapWidget.height())
                {
                    p_wind.drawPoint(point);
                }
                i2++;
            }
            i++;
            i2=0;
        }
        i=0;i2=0;
        QPoint p;
        for(obj_it=objs.begin();obj_it != objs.end(); obj_it++)
        {
            std::vector<vektor> pnts = (*obj_it).pnts;
            sxf::EObjectType type;
            type =(*obj_it).type; // EOT_NOT_DRAW, EOT_POINT, EOT_LINE, EOT_POLYGON, EOT_TEXT
            QString label = QString( (*obj_it).label.c_str() );

            std::vector<vektor>::iterator pnts_it;
            switch (type){
            case EOT_NOT_DRAW:
                break;
            case EOT_POINT:
                if(mapWidget.CheckBoxs & 0x4000)
                    for(pnts_it=pnts.begin();pnts_it != pnts.end(); pnts_it++)
                    {
                        QPointF point( mapWidget.GeoToMap(*pnts_it) );
                        if(point.x()>0 && point.y()>0 && point.x()<mapWidget.width() && point.y()<mapWidget.height())
                        {
                            p_wind.drawEllipse(point, 1, 1);
                        }
                    }
                break;
            case EOT_LINE:
                new_obj_f = false;
                if(mapWidget.CheckBoxs & 0x4000)
                    for(pnts_it=pnts.begin();pnts_it != pnts.end(); pnts_it++)
                    {
                        QPointF point( mapWidget.GeoToMap(*pnts_it) );
                        if(point.x()>0 && point.y()>0 && point.x()<mapWidget.width() && point.y()<mapWidget.height())
                        {
                            if(new_obj_f) p_wind.drawLine(point, p);
                            new_obj_f = true;
                        }
                        p.setX(point.x());
                        p.setY(point.y());
                    }
                break;
            case EOT_POLYGON:
                QPointF *poligon;
                poligon = new QPointF[int(pnts.size())];
                i = 0;
                new_obj_f = false;
                if(mapWidget.CheckBoxs & 0x8000)
                    for(pnts_it=pnts.begin();pnts_it != pnts.end(); pnts_it++)
                    {
                        QPointF point( mapWidget.GeoToMap(*pnts_it) );
                        if(new_obj_f)poligon[i++] = point;
                        new_obj_f = true;
                    }
                if(new_obj_f) p_wind.drawPolygon(poligon, i, Qt::WindingFill);
                if(poligon)delete [] poligon;
                break;

            case EOT_TEXT:
                if(mapWidget.CheckBoxs & 0x8000)
                    for(pnts_it=pnts.begin();pnts_it != pnts.end(); pnts_it++)
                    {
                        QPointF point( mapWidget.GeoToMap(*pnts_it) );
                        if(point.x()>0 && point.y()>0 && point.x()<mapWidget.width() && point.y()<mapWidget.height())
                        {
                            p_wind.drawText(point, label);
                        }
                    }
                break;
            }
        }
    }

}
