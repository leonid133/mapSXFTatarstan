#ifndef MAP_H
#define MAP_H

#include <common.h>
#include <QObject>
#include <QtWidgets>
#include <lib/sxf.h>

//#define uint64_t int

#include <vector>
#include <string>

using namespace sxf;

class QPaintEvent;

class WMap : public QWidget
{
    Q_OBJECT

    void Pars();

public:
    WMap(QWidget * parent = 0);

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
    void SlotSetBox17();
signals: // сигналы

public:
    QPointF GeoToMap(const GVektor &geocoord);
    GVektor MapToGeo(const QPoint &mapcoord);

protected:
    void paintEvent(QPaintEvent *);
    virtual void mouseMoveEvent(QMouseEvent*pe);
    virtual void mousePressEvent(QMouseEvent *pe);
    virtual void mouseDoubleClickEvent(QMouseEvent *pe);
    virtual void wheelEvent(QWheelEvent *event);

    BaseMap *map = 0;
    //std::vector<Object> objs;
    std::vector< std::vector<GVektor> > cnts;
        int CheckBoxs;
     double max_point_x, max_point_y, min_point_x, min_point_y, realpos_point_x, realpos_point_y;

        int mouse_delta_x, mouse_delta_y;
    QPointF mouse_coord;
        int m_scale, w, h;
     double m_x, m_y;
    QString file_map_sxf;
       bool loadOk;

    QPointF m_coord_SelectObj;
};

#endif // MAP_H
