#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

//#include <QWidget>
#include <QObject>
#include <QtWidgets>
#include <lib/sxf.h>
#include <lib/all.h>

class QPaintEvent;

class BaseObject;

class ObjOzera;
class ObjVodohranil;
class ObjRiver;


class MapWidget : public QWidget
{
    Q_OBJECT

    void RePars();

public:
    MapWidget(QWidget * parent = 0);
    virtual ~MapWidget(){
        delete[] ob;
    };
public slots: // публичные слоты


private slots: // приватные
    void SetFileNameSlot();
    void SlotSetBox1();
    void SlotSetBox2();
    void SlotSetBox3();
    void SlotSetBox4();
    void SlotSetBox5();
    void SlotSetBox6();
    void SlotSetBox7();
    void SlotSetBox8();
    void SlotSetBox9();
    void SlotSetBox10();
    void SlotSetBox11();
    void SlotSetBox12();
    void SlotSetBox13();
    void SlotSetBox14();
    void SlotSetBox15();
    void SlotSetBox16();
signals: // сигналы

public:
    void paintEvent(QPaintEvent *);
    virtual void mouseMoveEvent(QMouseEvent*pe);
    virtual void mouseDoubleClickEvent(QMouseEvent *pe);
    virtual void wheelEvent(QWheelEvent *event);
        int CheckBoxs;
     double max_point_x, max_point_y, min_point_x, min_point_y, realpos_point_x, realpos_point_y;

         QPointF GeoToMap(const vektor &geocoord);
         vektor MapToGeo(const QPoint &mapcoord);
       //  std::shared_ptr<QPainter> p_wind;
protected:
             int mouse_delta_x, mouse_delta_y;
         QPointF mouse_coord;
             int m_scale, w, h;
          double m_x, m_y;
         QString file_map_sxf;
            bool loadOk;

    std::shared_ptr<ObjOzera> obj_ozera;
    std::shared_ptr<ObjVodohranil> obj_vodohranil;
    std::shared_ptr<ObjRiver> obj_river;

    //vector<std::shared_ptr <BaseObject> > objects;
    //vector <BaseObject*> objects;
    BaseObject **ob;

};

class BaseObject
{
public:
    BaseObject(){};
    BaseObject& operator = ( const BaseObject& source );
    BaseObject& operator = ( BaseObject&& other );
    BaseObject( BaseObject&& other );
    virtual ~BaseObject(){};
    virtual void LoadFromFile(QString file_map_sxf);;
    virtual void Drow(MapWidget &mapWidget);;

          vector<CObject> objs;
vector< vector<vektor> > cnts;
protected:
            bool loadOk;
          double max_point_x, max_point_y, min_point_x, min_point_y;

vector<unsigned> codes;
  Qt::BrushStyle brush_style;
            QPen pen_style;
           QFont font_style;
};
class ObjOzera : public BaseObject
{
public:
    ObjOzera& operator = ( const ObjOzera& source );
    ObjOzera& operator = ( ObjOzera&& other );
    ObjOzera( ObjOzera&& other );

    ObjOzera():BaseObject(){
        max_point_y = max_point_x = -999999999;
        min_point_y = min_point_x = 999999999;
        codes.push_back( 0x1DADA80 );  // ОЗЕРА (ПОСТОЯННЫЕ)  = НАБОР
        brush_style = Qt::VerPattern;
        pen_style = QPen(Qt::blue,1,Qt::SolidLine);
        font_style = QFont("Arial", 30);
     };
    virtual ~ObjOzera(){};
};
class ObjVodohranil : public BaseObject
{
public:
    ObjVodohranil& operator = ( const ObjVodohranil& source );
    ObjVodohranil& operator = ( ObjVodohranil&& other );
    ObjVodohranil( ObjVodohranil&& other );
    ObjVodohranil():BaseObject(){
        max_point_y = max_point_x = -999999999;
        min_point_y = min_point_x = 999999999;
        codes.push_back( 0x1DB0578 );  // ВОДОХРАНИЛИЩА ДЕЙСТВУЮЩИЕ = НАБОР
        brush_style = Qt::HorPattern;
        pen_style = QPen(Qt::blue,1,Qt::SolidLine);
        font_style = QFont("Arial", 30);
    };

    virtual ~ObjVodohranil(){};
    //void LoadFromFile(QString file_map_sxf);
    //void Drow(MapWidget &mapWidget);
};
class ObjRiver : public BaseObject
{
public:

    ObjRiver& operator = ( const ObjRiver& source );
    ObjRiver& operator = ( ObjRiver&& other );
    ObjRiver( ObjRiver&& other );

    ObjRiver():BaseObject(){
        max_point_y = max_point_x = -999999999;
        min_point_y = min_point_x = 999999999;
        codes.push_back( 0x1DF4750 );  // РЕКИ ПОСТОЯНЫЕ (от 20-120 м) = ЛИНИЯ
        brush_style = Qt::HorPattern;
        pen_style = QPen(Qt::blue,1,Qt::SolidLine);
        font_style = QFont("Arial", 30);
    };
    virtual ~ObjRiver(){};
};

/*
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
*/

#endif // QPAINTWIDGET_H
