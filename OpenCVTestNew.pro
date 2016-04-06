TEMPLATE = subdirs

#
#git clone https://github.com/qtproject/qtcharts
#

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
