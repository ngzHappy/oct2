TEMPLATE = subdirs

#http://heanet.dl.sourceforge.net/project/opencvlibrary
#http://heanet.dl.sourceforge.net/project/opencvlibrary/opencv-win/3.1.0/opencv-3.1.0.exe

#
#git clone https://github.com/qtproject/qtcharts
#

#vsbuild.bat
#set PATH=%PATH%;C:\QT\Qt57\vs2015\qtbase\bin;
#qmake "../OpenCVTestNew" -r -tp vc

#vsrun.bat
#@set PATH=%PATH%;C:\QT\Qt57\vs2015\qtbase\bin;
#@cd C:\Temp\ffjjj\otestnew\OpenCVTestNew\binlib\msvc\bin
#cmd

#.subdir #Use the specified subdirectory instead of SUBDIRS value.
#.file #Specify the subproject pro file explicitly. Cannot be used in conjunction with .subdir modifier.
#.depends #This subproject depends on specified subproject.
#.makefile #The makefile of subproject. Available only on platforms that use makefiles.
#.target #Base string used for makefile targets related to this subproject. Available only on platforms that use makefiles.
SUBDIRS += projectMaker
SUBDIRS += setgetutility

core_utility.file = $$PWD/core_utility/core_utility.pro
SUBDIRS += core_utility

lua_simple_test.file = $$PWD/lua_simple_test/lua_simple_test.pro
lua_simple_test.depends += core_utility
SUBDIRS += lua_simple_test

quazip_simple_test.file = $$PWD/quazip_simple_test/quazip_simple_test.pro
quazip_simple_test.depends += core_utility
SUBDIRS += quazip_simple_test

lua.file = $$PWD/lua/lua.pro
lua.depends += core_utility
SUBDIRS += lua

first_window.file = $$PWD/first_window/first_window.pro
first_window.depends += core_utility
SUBDIRS += first_window

first_matrix.file = $$PWD/opencv_data/first_matrix/first_matrix.pro
first_matrix.depends += core_utility
SUBDIRS += first_matrix

first_image_show.file = $$PWD/opencv_imgproc/first_image_show/first_image_show.pro
first_image_show.depends += core_utility
SUBDIRS += first_image_show

simple_pca.file = $$PWD/opencv_data/simple_pca/simple_pca.pro
simple_pca.depends += core_utility
SUBDIRS += simple_pca

opencv_pca.file = $$PWD/opencv_data/opencv_pca/opencv_pca.pro
opencv_pca.depends += core_utility
SUBDIRS += opencv_pca

opencv_rect.file = $$PWD/opencv_data/opencv_rect/opencv_rect.pro
opencv_rect.depends += core_utility
SUBDIRS += opencv_rect

opencv_point.file = $$PWD/opencv_data/opencv_point/opencv_point.pro
opencv_point.depends += core_utility
SUBDIRS += opencv_point

opencv_size.file = $$PWD/opencv_data/opencv_size/opencv_size.pro
opencv_size.depends += core_utility
SUBDIRS += opencv_size

opencv_scalar.file = $$PWD/opencv_data/opencv_scalar/opencv_scalar.pro
opencv_scalar.depends += core_utility
SUBDIRS += opencv_scalar

opencv_blur.file = $$PWD/opencv_imgproc/opencv_blur/opencv_blur.pro
opencv_blur.depends += core_utility
SUBDIRS += opencv_blur

opencv_pyrDown.file = $$PWD/opencv_imgproc/opencv_pyrDown/opencv_pyrDown.pro
opencv_pyrDown.depends += core_utility
SUBDIRS += opencv_pyrDown

opencv_canny.file = $$PWD/opencv_imgproc/opencv_canny/opencv_canny.pro
opencv_canny.depends += core_utility
SUBDIRS += opencv_canny

opencv_draw.file = $$PWD/opencv_imgproc/opencv_draw/opencv_draw.pro
opencv_draw.depends += core_utility
SUBDIRS += opencv_draw

opencv_saveload.file = $$PWD/opencv_data/opencv_saveload/opencv_saveload.pro
opencv_saveload.depends += core_utility
SUBDIRS += opencv_saveload

opencv_matrix_wrap.file = $$PWD/opencv_data/opencv_matrix_wrap/opencv_matrix_wrap.pro
opencv_matrix_wrap.depends += core_utility
SUBDIRS += opencv_matrix_wrap

opencv_pyrUp.file = $$PWD/opencv_imgproc/opencv_pyrUp/opencv_pyrUp.pro
opencv_pyrUp.depends += core_utility
SUBDIRS += opencv_pyrUp

opencv_roi.file = $$PWD/opencv_imgproc/opencv_roi/opencv_roi.pro
opencv_roi.depends += core_utility
SUBDIRS += opencv_roi

opencv_fft.file = $$PWD/opencv_imgproc/opencv_fft/opencv_fft.pro
opencv_fft.depends += core_utility
SUBDIRS += opencv_fft

opencv_stitcher.file = $$PWD/opencv_tool/opencv_stitcher/opencv_stitcher.pro
opencv_stitcher.depends += core_utility
SUBDIRS += opencv_stitcher

opencv_minAreaRect.file = $$PWD/opencv_point_algorithm/opencv_minAreaRect/opencv_minAreaRect.pro
opencv_minAreaRect.depends += core_utility
SUBDIRS += opencv_minAreaRect

opencv_minEnclosingCircle.file = $$PWD/opencv_point_algorithm/opencv_minEnclosingCircle/opencv_minEnclosingCircle.pro
opencv_minEnclosingCircle.depends += core_utility
SUBDIRS += opencv_minEnclosingCircle

opencv_minEnclosingTriangle.file = $$PWD/opencv_point_algorithm/opencv_minEnclosingTriangle/opencv_minEnclosingTriangle.pro
opencv_minEnclosingTriangle.depends += core_utility
SUBDIRS += opencv_minEnclosingTriangle

opencv_approxPolyDP.file = $$PWD/opencv_point_algorithm/opencv_approxPolyDP/opencv_approxPolyDP.pro
opencv_approxPolyDP.depends += core_utility
SUBDIRS += opencv_approxPolyDP

gzip_simple_test.file = $$PWD/gzip_simple_test/gzip_simple_test.pro
gzip_simple_test.depends += core_utility
SUBDIRS += gzip_simple_test

opencv_boundRect.file = $$PWD/opencv_point_algorithm/opencv_boundRect/opencv_boundRect.pro
opencv_boundRect.depends += core_utility
SUBDIRS += opencv_boundRect

opencv_convexHull.file = $$PWD/opencv_point_algorithm/opencv_convexHull/opencv_convexHull.pro
opencv_convexHull.depends += core_utility
SUBDIRS += opencv_convexHull

opencv_simple_test.file = $$PWD/opencv_simple_test/opencv_simple_test.pro
opencv_simple_test.depends += core_utility
SUBDIRS += opencv_simple_test

opencv_findContours.file = $$PWD/opencv_imgproc/opencv_findContours/opencv_findContours.pro
opencv_findContours.depends += core_utility
SUBDIRS += opencv_findContours

opencv_delaunay.file = $$PWD/opencv_point_algorithm/opencv_delaunay/opencv_delaunay.pro
opencv_delaunay.depends += core_utility
SUBDIRS += opencv_delaunay

configure_file_simple_test.file = $$PWD/configure_file_simple_test/configure_file_simple_test.pro
configure_file_simple_test.depends += core_utility
SUBDIRS += configure_file_simple_test

data_view.file = $$PWD/data_view/data_view.pro
data_view.depends += core_utility
SUBDIRS += data_view

opencv_findContours_freeman.file = $$PWD/opencv_imgproc/opencv_findContours_freeman/opencv_findContours_freeman.pro
opencv_findContours_freeman.depends += core_utility
SUBDIRS += opencv_findContours_freeman

opencv_contourArea.file = $$PWD/opencv_imgproc/opencv_contourArea/opencv_contourArea.pro
opencv_contourArea.depends += core_utility
SUBDIRS += opencv_contourArea

opencv_arcLength.file = $$PWD/opencv_imgproc/opencv_arcLength/opencv_arcLength.pro
opencv_arcLength.depends += core_utility
SUBDIRS += opencv_arcLength

opencv_fitLine.file = $$PWD/opencv_point_algorithm/opencv_fitLine/opencv_fitLine.pro
opencv_fitLine.depends += core_utility
SUBDIRS += opencv_fitLine

opencv_fitEllipse.file = $$PWD/opencv_point_algorithm/opencv_fitEllipse/opencv_fitEllipse.pro
opencv_fitEllipse.depends += core_utility
SUBDIRS += opencv_fitEllipse

opencv_pointPolygonTest.file = $$PWD/opencv_imgproc/opencv_pointPolygonTest/opencv_pointPolygonTest.pro
opencv_pointPolygonTest.depends += core_utility
SUBDIRS += opencv_pointPolygonTest

opencv_applyColorMap.file = $$PWD/opencv_imgproc/opencv_applyColorMap/opencv_applyColorMap.pro
opencv_applyColorMap.depends += core_utility
SUBDIRS += opencv_applyColorMap

opencv_connectedComponents.file = $$PWD/opencv_imgproc/opencv_connectedComponents/opencv_connectedComponents.pro
opencv_connectedComponents.depends += core_utility
SUBDIRS += opencv_connectedComponents

opencv_connectedComponentsWithStats.file = $$PWD/opencv_imgproc/opencv_connectedComponentsWithStats/opencv_connectedComponentsWithStats.pro
opencv_connectedComponentsWithStats.depends += core_utility
SUBDIRS += opencv_connectedComponentsWithStats

boost_simple_test.file = $$PWD/boost_simple_test/boost_simple_test.pro
boost_simple_test.depends += core_utility
SUBDIRS += boost_simple_test

opencv_convexityDefects.file = $$PWD/opencv_imgproc/opencv_convexityDefects/opencv_convexityDefects.pro
opencv_convexityDefects.depends += core_utility
SUBDIRS += opencv_convexityDefects
