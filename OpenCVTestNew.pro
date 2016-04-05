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
