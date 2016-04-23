TEMPLATE = subdirs
CONFIG -= ordered

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
SUBDIRS += classmaker
SUBDIRS += opencv_tool/image_rand_draw
SUBDIRS += setgetutility

guiprojectmaker.file =$$PWD/guiprojectmaker/guiprojectmaker.pro
guiprojectmaker.depends+=projectMaker
SUBDIRS+=guiprojectmaker

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

allinone.file = $$PWD/allinone/allinone.pro
allinone.depends += core_utility
SUBDIRS += allinone

opencv_intersectConvexConvex.file = $$PWD/opencv_point_algorithm/opencv_intersectConvexConvex/opencv_intersectConvexConvex.pro
opencv_intersectConvexConvex.depends += core_utility
SUBDIRS += opencv_intersectConvexConvex

opencv_matchShapes.file = $$PWD/opencv_point_algorithm/opencv_matchShapes/opencv_matchShapes.pro
opencv_matchShapes.depends += core_utility
SUBDIRS += opencv_matchShapes

opencv_HuMoments.file = $$PWD/opencv_imgproc/opencv_HuMoments/opencv_HuMoments.pro
opencv_HuMoments.depends += core_utility
SUBDIRS += opencv_HuMoments

quick_test.file = $$PWD/opencv_imgproc/quick_test/quick_test.pro
quick_test.depends += core_utility
SUBDIRS += quick_test

x00000.file = $$PWD/tmp/x00000/x00000.pro
x00000.depends += core_utility
SUBDIRS += x00000

opencv_copyMakeBorder.file = $$PWD/opencv_imgproc/opencv_copyMakeBorder/opencv_copyMakeBorder.pro
opencv_copyMakeBorder.depends += core_utility
SUBDIRS += opencv_copyMakeBorder

opencv_bilateralFilter.file = $$PWD/opencv_filter/opencv_bilateralFilter/opencv_bilateralFilter.pro
opencv_bilateralFilter.depends += core_utility
SUBDIRS += opencv_bilateralFilter

opencv_boxFilter.file = $$PWD/opencv_filter/opencv_boxFilter/opencv_boxFilter.pro
opencv_boxFilter.depends += core_utility
SUBDIRS += opencv_boxFilter

opencv_buildPyramid.file = $$PWD/opencv_filter/opencv_buildPyramid/opencv_buildPyramid.pro
opencv_buildPyramid.depends += core_utility
SUBDIRS += opencv_buildPyramid

opencv_dilate.file = $$PWD/opencv_filter/opencv_dilate/opencv_dilate.pro
opencv_dilate.depends += core_utility
SUBDIRS += opencv_dilate

opencv_erode.file = $$PWD/opencv_filter/opencv_erode/opencv_erode.pro
opencv_erode.depends += core_utility
SUBDIRS += opencv_erode

opencv_filter2D.file = $$PWD/opencv_filter/opencv_filter2D/opencv_filter2D.pro
opencv_filter2D.depends += core_utility
SUBDIRS += opencv_filter2D

opencv_GaussianBlur.file = $$PWD/opencv_filter/opencv_GaussianBlur/opencv_GaussianBlur.pro
opencv_GaussianBlur.depends += core_utility
SUBDIRS += opencv_GaussianBlur

opencv_Laplacian.file = $$PWD/opencv_filter/opencv_Laplacian/opencv_Laplacian.pro
opencv_Laplacian.depends += core_utility
SUBDIRS += opencv_Laplacian

opencv_medianBlur.file = $$PWD/opencv_filter/opencv_medianBlur/opencv_medianBlur.pro
opencv_medianBlur.depends += core_utility
SUBDIRS += opencv_medianBlur

opencv_morphologyEx.file = $$PWD/opencv_filter/opencv_morphologyEx/opencv_morphologyEx.pro
opencv_morphologyEx.depends += core_utility
SUBDIRS += opencv_morphologyEx

opencv_pyrMeanShiftFiltering.file = $$PWD/opencv_filter/opencv_pyrMeanShiftFiltering/opencv_pyrMeanShiftFiltering.pro
opencv_pyrMeanShiftFiltering.depends += core_utility
SUBDIRS += opencv_pyrMeanShiftFiltering

opencv_Scharr.file = $$PWD/opencv_filter/opencv_Scharr/opencv_Scharr.pro
opencv_Scharr.depends += core_utility
SUBDIRS += opencv_Scharr

opencv_sepFilter2D.file = $$PWD/opencv_filter/opencv_sepFilter2D/opencv_sepFilter2D.pro
opencv_sepFilter2D.depends += core_utility
SUBDIRS += opencv_sepFilter2D

opencv_Sobel.file = $$PWD/opencv_filter/opencv_Sobel/opencv_Sobel.pro
opencv_Sobel.depends += core_utility
SUBDIRS += opencv_Sobel

opencv_spatialGradient.file = $$PWD/opencv_filter/opencv_spatialGradient/opencv_spatialGradient.pro
opencv_spatialGradient.depends += core_utility
SUBDIRS += opencv_spatialGradient

opencv_sqrBoxFilter.file = $$PWD/opencv_filter/opencv_sqrBoxFilter/opencv_sqrBoxFilter.pro
opencv_sqrBoxFilter.depends += core_utility
SUBDIRS += opencv_sqrBoxFilter

opencv_warpPerspective.file = $$PWD/opencv_image_transformations/opencv_warpPerspective/opencv_warpPerspective.pro
opencv_warpPerspective.depends += core_utility
SUBDIRS += opencv_warpPerspective

opencv_remap.file = $$PWD/opencv_image_transformations/opencv_remap/opencv_remap.pro
opencv_remap.depends += core_utility
SUBDIRS += opencv_remap

opencv_resize.file = $$PWD/opencv_image_transformations/opencv_resize/opencv_resize.pro
opencv_resize.depends += core_utility
SUBDIRS += opencv_resize

opencv_warpAffine.file = $$PWD/opencv_image_transformations/opencv_warpAffine/opencv_warpAffine.pro
opencv_warpAffine.depends += core_utility
SUBDIRS += opencv_warpAffine

opencv_matchTemplate.file = $$PWD/opencv_imgproc/opencv_matchTemplate/opencv_matchTemplate.pro
opencv_matchTemplate.depends += core_utility
SUBDIRS += opencv_matchTemplate

opencv_cornerHarris.file = $$PWD/opencv_imgproc/opencv_cornerHarris/opencv_cornerHarris.pro
opencv_cornerHarris.depends += core_utility
SUBDIRS += opencv_cornerHarris

opencv_HoughCircles.file = $$PWD/opencv_imgproc/opencv_HoughCircles/opencv_HoughCircles.pro
opencv_HoughCircles.depends += core_utility
SUBDIRS += opencv_HoughCircles

opencv_HoughLines.file = $$PWD/opencv_imgproc/opencv_HoughLines/opencv_HoughLines.pro
opencv_HoughLines.depends += core_utility
SUBDIRS += opencv_HoughLines

opencv_HoughLinesP.file = $$PWD/opencv_imgproc/opencv_HoughLinesP/opencv_HoughLinesP.pro
opencv_HoughLinesP.depends += core_utility
SUBDIRS += opencv_HoughLinesP

opencv_2GRAY.file = $$PWD/opencv_cvtColor/opencv_2GRAY/opencv_2GRAY.pro
opencv_2GRAY.depends += core_utility
SUBDIRS += opencv_2GRAY

opencv_2XYZ.file = $$PWD/opencv_cvtColor/opencv_2XYZ/opencv_2XYZ.pro
opencv_2XYZ.depends += core_utility
SUBDIRS += opencv_2XYZ

opencv_2YCrCb.file = $$PWD/opencv_cvtColor/opencv_2YCrCb/opencv_2YCrCb.pro
opencv_2YCrCb.depends += core_utility
SUBDIRS += opencv_2YCrCb

opencv_2HSV.file = $$PWD/opencv_cvtColor/opencv_2HSV/opencv_2HSV.pro
opencv_2HSV.depends += core_utility
SUBDIRS += opencv_2HSV

opencv_2Lab.file = $$PWD/opencv_cvtColor/opencv_2Lab/opencv_2Lab.pro
opencv_2Lab.depends += core_utility
SUBDIRS += opencv_2Lab

opencv_2Luv.file = $$PWD/opencv_cvtColor/opencv_2Luv/opencv_2Luv.pro
opencv_2Luv.depends += core_utility
SUBDIRS += opencv_2Luv

opencv_2HLS.file = $$PWD/opencv_cvtColor/opencv_2HLS/opencv_2HLS.pro
opencv_2HLS.depends += core_utility
SUBDIRS += opencv_2HLS

opencv_2YUV.file = $$PWD/opencv_cvtColor/opencv_2YUV/opencv_2YUV.pro
opencv_2YUV.depends += core_utility
SUBDIRS += opencv_2YUV

opencv_2RGBA.file = $$PWD/opencv_cvtColor/opencv_2RGBA/opencv_2RGBA.pro
opencv_2RGBA.depends += core_utility
SUBDIRS += opencv_2RGBA

gifMaker.file = $$PWD/opencv_tool/gifMaker/gifMaker.pro
gifMaker.depends += core_utility
SUBDIRS += gifMaker
