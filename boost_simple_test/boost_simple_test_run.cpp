/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include <OpenCVBoost.hpp>
#include "private/boost_simple_test_run_exception.cpp"
//#include <QtCharts>

namespace boost_simple_test{
extern void run(OpenCVWindow * ) try{

    {
        namespace bgi=boost::geometry::index;
        namespace bg=boost::geometry;
        typedef bg::model::point<std::int32_t,3,bg::cs::cartesian> point/*笛卡尔坐标系点*/;
        typedef std::pair<point,std::int32_t> value;

        bgi::rtree<value,bgi::quadratic<16>> rtree;
        rtree.insert(std::make_pair(point(1,2,3),std::int32_t(0)));
        rtree.insert(std::make_pair(point(0,2,3),std::int32_t(0)));
        rtree.insert(std::make_pair(point(1,5,3),std::int32_t(0)));
        rtree.insert(std::make_pair(point(1,0,3),std::int32_t(0)));

        std::vector<value> ans;
        rtree.query(bgi::nearest(point(1,0,3),1),std::back_inserter(ans));

        for (const auto & i:ans) {
            std::cout
                <<"x:"<<i.first.get<0>()
                <<"y:"<<i.first.get<1>()
                <<"z:"<<i.first.get<2>()
                <<std::endl;
        }

    }

    {
        boost::shared_ptr<int> value=boost::make_shared<int>(12);
        assert(value);
        assert(*value==12);
    }

    {
        boost::pool<> testPool{ 16 };
        auto data=testPool.malloc();
        assert(data);
        (void)data;
    }

    {
        std::cout<<"test:0"<<std::endl;
        boost::circular_buffer<int> buffer{3};
        buffer.push_back(0);
        buffer.push_back(1);
        buffer.push_back(2);
        buffer.rset_capacity(2);
        for (const auto & i:buffer) {
            std::cout<<i<<std::endl;
        }
        std::cout<<"~test:0"<<std::endl;
    }

    {
        std::cout<<"test:1"<<std::endl;
        boost::circular_buffer<int> buffer{3};
        buffer.push_back(0);
        buffer.push_back(1);
        buffer.push_back(2);
        buffer.set_capacity(2);
        for (const auto & i:buffer) {
            std::cout<<i<<std::endl;
        }
        std::cout<<"~test:1"<<std::endl;
    }

    {
        boost::ptr_vector<int> test;
        test.push_back(new int(0));
        test.push_back(new int(1));
        test.push_back(new int(2));

        auto v =test.release(test.begin());
        std::cout<<test.size()<<std::endl;
    }

    {
        boost::optional<int> value;
        assert(bool(value)==false);
        value=12;
        assert(value);
    }

    {
        boost::signals2::signal<void(void)> signal;
        auto sc= signal.connect([]() {std::cout<<"1"<<std::endl; });
        signal();
        sc.disconnect();
        signal();
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}
/*
#include <boost/assign.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include <boost/geometry/algorithms/transform.hpp>
#include <boost/geometry/strategies/transform/inverse_transformer.hpp>
#include <boost/geometry/strategies/transform/matrix_transformers.hpp>

namespace bg = boost::geometry;
typedef bg::model::d2::point_xy<double> DPoint;
typedef bg::model::segment<DPoint> DSegment;
typedef bg::model::linestring<DPoint> DLineString;
typedef bg::model::box<DPoint> DBox;
typedef bg::model::ring<DPoint, false> DRing;
typedef bg::model::polygon<DPoint, false> DPolygon;
//对Geometry库一些函数进行了封装，更加方便使用，包括(平移，旋转，缩放，求点到直线的垂足，通过比例求段上的点等等)
namespace GeometryExtend
{
DPoint operator +(const DPoint& pt1, const DPoint& pt2)
{
DPoint pt(pt1);
bg::add_point(pt, pt2);
return pt;
}

const DPoint& operator +=(DPoint& pt1, const DPoint& pt2)
{
bg::add_point(pt1, pt2);
return pt1;
}

DPoint operator -(const DPoint& pt1, const DPoint& pt2)
{
DPoint pt(pt1);
bg::subtract_point(pt, pt2);
return pt;
}

const DPoint& operator -=(DPoint& pt1, const DPoint& pt2)
{
bg::subtract_point(pt1, pt2);
return pt1;
}

//////////////////////////////////////////////////////////////////////////
//  平移变换
//////////////////////////////////////////////////////////////////////////
template<typename Geometry, typename CalculationType>
struct translate_impl
{
static void apply(Geometry& geometry, const CalculationType& x, const CalculationType& y)
{
bg::strategy::transform::translate_transformer<CalculationType, 2, 2> t(x, y);
bg::transform(geometry, geometry, t);
}
};

template<typename Geometry, typename CalculationType>
struct translate_trais
{
static void apply(Geometry& geometry, const CalculationType& x, const CalculationType& y);
};


#define TRANSLATE_TRAIS(Geometry) \
template<typename CalculationType> \
struct translate_trais<Geometry, CalculationType> \
{ \
static void apply(Geometry& geometry, const CalculationType& x, const CalculationType& y) \
{ \
translate_impl<Geometry, CalculationType>::apply(geometry, x, y); \
} \
};

TRANSLATE_TRAIS(DPoint)
TRANSLATE_TRAIS(DSegment)
TRANSLATE_TRAIS(DBox)
TRANSLATE_TRAIS(DRing)
TRANSLATE_TRAIS(DPolygon)

template<typename Geometry, typename CalculationType>
void translate(Geometry& geometry, const CalculationType& x, const CalculationType& y)
{
translate_trais<Geometry, CalculationType>::apply(geometry, x, y);
}


//////////////////////////////////////////////////////////////////////////
//  旋转变换
//////////////////////////////////////////////////////////////////////////
template<typename Geometry, typename DegreeOrRadian, typename CalculationType>
struct rotate_impl
{
static void apply(Geometry& geometry, const CalculationType& angle)
{
bg::strategy::transform::rotate_transformer<DegreeOrRadian, CalculationType, 2, 2> t(angle);
bg::transform(geometry, geometry, t);
}
};

template<typename Geometry, typename DegreeOrRadian, typename CalculationType>
struct rotate_trais
{
static void apply(Geometry& geometry, const CalculationType& angle);
};

#define ROTATE_TRAIS(Geometry, DegreeOrRadian) \
template<typename CalculationType> \
struct rotate_trais<Geometry, DegreeOrRadian, CalculationType> \
{ \
static void apply(Geometry& geometry, const CalculationType& angle) \
{ \
rotate_impl<Geometry, DegreeOrRadian, CalculationType>::apply(geometry, angle); \
} \
};

ROTATE_TRAIS(DPoint, bg::degree)
ROTATE_TRAIS(DPoint, bg::radian)
ROTATE_TRAIS(DSegment, bg::degree)
ROTATE_TRAIS(DSegment, bg::radian)
ROTATE_TRAIS(DBox, bg::degree)
ROTATE_TRAIS(DBox, bg::radian)
ROTATE_TRAIS(DRing, bg::degree)
ROTATE_TRAIS(DRing, bg::radian)
ROTATE_TRAIS(DPolygon, bg::degree)
ROTATE_TRAIS(DPolygon, bg::radian)

template<typename Geometry, typename DegreeOrRadian, typename CalculationType>
void rotate(Geometry& geometry, const DegreeOrRadian&, const CalculationType& angle)
{
rotate_trais<Geometry, DegreeOrRadian, CalculationType>::apply(geometry, angle);
}

template<typename Geometry, typename Point, typename DegreeOrRadian, typename CalculationType>
void point_rotate(Geometry& geometry, const Point& point, const DegreeOrRadian& type, const CalculationType& angle)
{
Point pt(0, 0);

bg::subtract_point(pt, point);
translate(geometry, bg::get<0>(pt), bg::get<1>(pt));
rotate(geometry, type, angle);
translate(geometry, bg::get<0>(point), bg::get<1>(point));
}


//////////////////////////////////////////////////////////////////////////
//  比例变形
//////////////////////////////////////////////////////////////////////////
template<typename Geometry, typename CalculationType>
struct scale_impl
{
static void apply(Geometry& geometry, const CalculationType& scale_x, const CalculationType& scale_y)
{
bg::strategy::transform::scale_transformer<CalculationType, 2, 2> t(scale_x, scale_y);
bg::transform(geometry, geometry, t);
}
};

template<typename Geometry, typename CalculationType>
struct scale_trais
{
static void apply(Geometry& geometry, const CalculationType& scale_x, const CalculationType& scale_y);
};

#define SCALE_TRAIS(Geometry) \
template<typename CalculationType> \
struct scale_trais<Geometry, CalculationType> \
{ \
static void apply(Geometry& geometry, const CalculationType& scale_x, const CalculationType& scale_y) \
{ \
scale_impl<Geometry, CalculationType>::apply(geometry, scale_x, scale_y); \
} \
};

SCALE_TRAIS(DPoint)
SCALE_TRAIS(DSegment)
SCALE_TRAIS(DBox)
SCALE_TRAIS(DRing)
SCALE_TRAIS(DPolygon)

template<typename Geometry, typename CalculationType>
void scale(Geometry& geometry, const CalculationType& scale_x, const CalculationType& scale_y)
{
scale_trais<Geometry, CalculationType>::apply(geometry, scale_x, scale_y);
}


//////////////////////////////////////////////////////////////////////////
//  函数功能：
//      扩充box
//////////////////////////////////////////////////////////////////////////
template<typename Geometry, typename CalculateType>
void InflateBox(Geometry& geometry, CalculateType const& cx, CalculateType const& cy)
{
typedef typename bg::point_type<Geometry>::type point_type;
point_type& ptMin = geometry.min_corner();
point_type& ptMax = geometry.max_corner();

ptMin.x(ptMin.x() - cx);
ptMin.y(ptMin.y() - cy);
ptMax.x(ptMax.x() + cx);
ptMax.y(ptMax.y() + cy);
}

//////////////////////////////////////////////////////////////////////////
//  函数功能：
//      求点到线段的垂足；
//  返回值：
//      true，垂足在线段上；
//      false，垂足在线段外；
//////////////////////////////////////////////////////////////////////////
template<typename Point, typename Segment>
bool point_to_segment_org(Point const& point, Segment const& segment, Point& ptOut)
{
bool bInSegment = true;

try
{
typedef typename bg::point_type<Segment>::type point_type;
point_type p[2] = {segment.first, segment.second};

if (boost::geometry::equals(point, p[0]) ||
boost::geometry::equals(point, p[1]))
{
boost::geometry::assign_point(ptOut, point);
bInSegment = true;
throw bInSegment;
}

point_type v(p[1]), w(point);

boost::geometry::subtract_point(v, p[0]);
boost::geometry::subtract_point(w, p[0]);

typedef typename bg::select_calculation_type<Point, Segment, void>::type calculation_type;

calculation_type const zero = calculation_type();
calculation_type const c1 = boost::geometry::dot_product(w, v);
if (c1 < zero)
{
bInSegment = false;
}

double const c2 = boost::geometry::dot_product(v, v);
if (c2 < c1)
{
bInSegment = false;
}

calculation_type const b = c1 / c2;
DPoint projected(p[0]);

boost::geometry::multiply_value(v, b);
boost::geometry::add_point(projected, v);
boost::geometry::assign_point(ptOut, projected);
}
catch (bool)
{
}

return bInSegment;
}


//////////////////////////////////////////////////////////////////////////
//  函数功能：
//      通过比例求段上的点；
//////////////////////////////////////////////////////////////////////////
template<typename Segment, typename Point>
void get_segment_on_point_by_scale(Segment const& segment, double const& dScale, Point& ptOut)
{
typedef typename bg::point_type<Segment>::type point_type;

point_type p[2] = {segment.first, segment.second};
point_type v(p[1]);
point_type ptDest(p[0]);

boost::geometry::subtract_point(v, p[0]);
boost::geometry::multiply_value(v, dScale);
boost::geometry::add_point(ptDest, v);
boost::geometry::assign_point(ptOut, ptDest);
}


//////////////////////////////////////////////////////////////////////////
//  函数功能：
//      通过长度求段上的点；
//////////////////////////////////////////////////////////////////////////
template<typename Segment, typename Point>
void get_segment_on_point_by_length(Segment const& segment, double const& dLength, Point& ptOut)
{
typedef typename bg::point_type<Segment>::type point_type;

point_type p[2] = {segment.first, segment.second};
double dTotalLength = boost::geometry::distance(p[0], p[1]);
double dScale = dLength / dTotalLength;

get_segment_on_point_by_scale(segment, dScale, ptOut);
}
}


int main()
{
DBox box1(DPoint(100, 100), DPoint(300, 200));
GeometryExtend::InflateBox(box1, 20, 10);

DSegment sg1(DPoint(100, 100), DPoint(300, 300));
DPoint pt1(300, 100);
DPoint pt2(100, 0);
DPoint ptOut;
bool bOnSegment;

bOnSegment = GeometryExtend::point_to_segment_org(pt1, sg1, ptOut);
bOnSegment = GeometryExtend::point_to_segment_org(pt2, sg1, ptOut);

GeometryExtend::get_segment_on_point_by_scale(sg1, 0.5, ptOut);
GeometryExtend::get_segment_on_point_by_length(sg1, 0, ptOut);

DPoint pt4;
DSegment sg4;
//平移变换
bg::assign_point(pt4, pt1);
GeometryExtend::translate(pt4, 10, 20);
bg::assign(sg4, sg1);
GeometryExtend::translate(sg4, 10, 20);

//旋转变形
bg::assign(pt4, pt1);
GeometryExtend::rotate(pt4, bg::degree(), 45.0);
bg::assign(sg4, sg1);
GeometryExtend::rotate(sg4, bg::degree(), 45.0);

//比例变换
bg::assign(pt4, pt1);
GeometryExtend::scale(pt4, 0.5, 0.2);
bg::assign(sg4, sg1);
GeometryExtend::scale(sg4, 0.5, 0.2);

return 0;
}
*/

/*
#include <boost/assign.hpp>
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/polygon.hpp>
namespace bg = boost::geometry;
typedef bg::model::d2::point_xy<double> DPoint;
typedef bg::model::segment<DPoint> DSegment;
typedef bg::model::linestring<DPoint> DLineString;
typedef bg::model::box<DPoint> DBox;
//这里的ring就是我们通常说的多边形闭合区域(内部不存在缕空)，模板参数为true，表示顺时针存储点，为false，表示逆时针存储点，由于MM_TEXT坐标系与传统上的坐标系的Y轴方向是相反的，所以最后为false，将TopLeft、TopRight、BottomRight、BottomLeft、TopLeft以此存储到ring中，以便能正确计算
typedef bg::model::ring<DPoint, false> DRing;
//polygon模板参数false，也是由上面相同的原因得出来的
typedef bg::model::polygon<DPoint, false> DPolygon;

int _tmain(int argc, _TCHAR* argv[])
{
DPoint pt0(100, 100);
DPoint pt1(200, 200);
DSegment sg0(pt0, pt1);

double dDistance = 0;

//1、点到点的距离
dDistance = bg::distance(pt0, pt1);
//2、点到线段的距离，如果点到直线的垂足不在线段上，所计算的距离为(点到直线的距离、线段到垂足延长的距离之和）
dDistance = bg::distance(DPoint(200, 100), sg0);
dDistance = bg::distance(DPoint(100, 0), sg0);

//3、判断线段是否相交
DSegment sg1(DPoint(0, 100), DPoint(100, 0));
DSegment sg2(DPoint(100, 200), DPoint(200, 100));
bool bIntersect = false;
bIntersect = bg::intersects(sg0, sg1);
bIntersect = bg::intersects(sg0, sg2);

//4、求线段与线段的交点
std::list<DPoint> lstPoints;
bg::intersection(sg0, sg1, lstPoints);
lstPoints.clear();
bg::intersection(sg0, sg2, lstPoints);

DBox rc2(DPoint(0, 0), DPoint(0, 0));

//5、判断box是否相交
DBox rc(DPoint(0, 0), DPoint(200, 200));
DBox rc0(DPoint(250, 250), DPoint(450, 450));
DBox rc1(DPoint(100, 100), DPoint(300, 300));

bIntersect = bg::intersects(rc, rc0);
bIntersect = bg::intersects(rc, rc1);
//bg::intersection(rc, rc0, container);//error

//6、判断box是否与LineString相交
DLineString line0;

line0.push_back(DPoint(10, 250));
line0.push_back(DPoint(100, 100));
line0.push_back(DPoint(120, -10));
line0.push_back(DPoint(210, 200));
bIntersect = bg::intersects(rc, line0);
bIntersect = bg::intersects(rc0, line0);

//7、求box与linestring的交点
std::list<DLineString> lstLines;
bg::intersection(rc, line0, lstLines);

//8、点是否在box内
DBox rc7(DPoint(0, 0), DPoint(100, 100));
bool bInside = false;
bInside = bg::within(DPoint(50, 50), rc7);
bInside = bg::within(DPoint(0, 0), rc7);

//9、判断LineString与LineString是否相交
DLineString line1, line2, line3;

line1.push_back(DPoint(50, 50));
line1.push_back(DPoint(150, 50));
line1.push_back(DPoint(50, 200));
line1.push_back(DPoint(150, 200));
line2.push_back(DPoint(100, 0));
line2.push_back(DPoint(70, 100));
line2.push_back(DPoint(150, 210));
line3.push_back(DPoint(200, 0));
line3.push_back(DPoint(200, 200));

bIntersect = bg::intersects(line1, line2);
bIntersect = bg::intersects(line1, line3);

//10、求LineString与LineString的交点
lstPoints.clear();
bg::intersection(line1, line2, lstPoints);
lstPoints.clear();
bg::intersection(line1, line3, lstPoints);


//11、判断ring与ring是否相交
DPoint arDPoint0[6] = {DPoint(0, 0), DPoint(100, 0), DPoint(200, 100), DPoint(100, 200), DPoint(0, 200), DPoint(0, 0)};
DPoint arDPoint1[6] = {DPoint(100, 100), DPoint(200, 0), DPoint(300, 0), DPoint(300, 200), DPoint(200, 200), DPoint(100, 100)};
DRing r0(arDPoint0, arDPoint0 + 6);
DRing r1(arDPoint1, arDPoint1 + 6);
bIntersect = bg::intersects(r0, r1);

//12、求ring与ring的交点
lstPoints.clear();
bg::intersection(r0, r1, lstPoints);

DPolygon poly1;
DPolygon poly2;
DPolygon poly3;

auto lstOf = boost::assign::list_of(DPoint(0, 0))(DPoint(200, 0))(DPoint(200, 200))(DPoint(0, 200))(DPoint(0, 0));
poly1.outer().assign(lstOf.begin(), lstOf.end());
lstOf = boost::assign::list_of(DPoint(50, 50))(DPoint(150, 50))(DPoint(150, 150))(DPoint(50, 150))(DPoint(50, 50));
poly1.inners().push_back(lstOf);
lstOf = boost::assign::list_of(DPoint(100, 0))(DPoint(120, 0))(DPoint(120, 200))(DPoint(100, 200))(DPoint(100, 0));
poly2.outer().assign(lstOf.begin(), lstOf.end());
lstOf = boost::assign::list_of(DPoint(100, 60))(DPoint(120, 60))(DPoint(120, 140))(DPoint(100, 140))(DPoint(100, 60));
poly3.outer().assign(lstOf.begin(), lstOf.end());

//13、判断polygon与polygon是否相交
bIntersect = bg::intersects(poly1, poly2);
bIntersect = bg::intersects(poly1, poly3);

//14、求polygon与polygon相交的区域
std::list<DPolygon> lstPolygon;

bg::intersection(poly1, poly2, lstPolygon);
lstPolygon.clear();
bg::intersection(poly1, poly3, lstPolygon);

//15、判断点是否在polygon内
bInside = bg::within(DPoint(100, 100), poly1);
bInside = bg::within(DPoint(25, 25), poly1);

return 0;
}
*/

