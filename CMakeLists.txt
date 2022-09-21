
cmake_minimum_required(VERSION 3.0)

project(ganymede)

set(CMAKE_CXX_STANDARD 14)


include_directories("/usr/include/")
include_directories("/usr/local/include/")
# find_package(GTK?)
# https://cmake.org/cmake/help/v3.6/module/FindGTK.html
include_directories("/usr/include/gtk-3.0/")
include_directories("/usr/include/glib-2.0/")
include_directories("/usr/lib/glib-2.0/include/")
include_directories("/usr/include/pango-1.0/")
include_directories("/usr/include/harfbuzz/")
include_directories("/usr/include/cairo/")
include_directories("/usr/include/gdk-pixbuf-2.0/")
include_directories("/usr/include/libwnck-3.0/")
include_directories("/usr/include/atk-1.0/")
#include_directories("")
#include_directories("")
#include_directories("")
#include_directories("")
#include_directories("")


link_directories("/usr/lib/")
link_directories("/usr/local/lib/")

# stolen from devilspie Makefile.am:
#	$(WNCK_CFLAGS) \
#	$(UNIQUE_CFLAGS) \
#	-DLOCALEDIR=\""$(datadir)/locale"\" \
#	-DSYSCONFDIR=\""$(sysconfdir)"\" \
#	-DDATADIR=\""$(datadir)"\" \
#	-DG_DISABLE_DEPRECATED \
#	-DGDK_DISABLE_DEPRECATED \
#	-DGTK_DISABLE_DEPRECATED \
#	-DWNCK_I_KNOW_THIS_IS_UNSTABLE

add_definitions("-DG_DISABLE_DEPRECATED")
add_definitions("-DGDK_DISABLE_DEPRECATED")
add_definitions("-DGTK_DISABLE_DEPRECATED")
add_definitions("-DWNCK_I_KNOW_THIS_IS_UNSTABLE")
#add_definitions("-DLINUX")
#add_definitions("-DLINUX")


file(GLOB HEADERS include/*.h)
file(GLOB SOURCES src/*.c*)


add_executable(ganymede ${HEADERS} ${SOURCES} include/Types.h)

include_directories(include)
target_link_libraries(ganymede g glib-2.0 gio-2.0 gtk-3 gtkmm-3.0 gdk-3 gdk_pixbuf-2.0 gobject-2.0 wnck-3)

#-L/usr/lib/python3.5/config-3.5m-arm-linux-gnueabihf -L/usr/lib -lpython3.5m -lpthread -#ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions

# /usr/bin/python3-config --ldflags
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/usr/lib/python3.5/config-3.5m-arm-linux-gnueabihf -L/usr/lib -lpython3.5m -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions")
