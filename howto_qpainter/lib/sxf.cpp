#include <lib/sxf.h>
//#include <lib/all.h>
#include <common.h>
#include <map.h>

SXFMap::SXFMap() :
    BaseMap()
{
    objs.reserve(100000);
    ;
}

void SXFMap::__load(const STRING map_fname, const STRING height_map_fname)
{
    objs = map.load(map_fname);
    /*
    hm.matrix = height_map.load(height_map_fname);

    hm.left_top = height_map.left_top();
    hm.size_in_map_coord = height_map.size_in_map_coord();
    hm.height = height_map.header.height;
    hm.width = height_map.header.width;
    */
}
