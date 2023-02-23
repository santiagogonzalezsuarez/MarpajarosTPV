cmake_minimum_required(VERSION 3.5)

project(MarpajarosTPV VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/util)

set(PROJECT_SOURCES
        util/util.h util/util.cpp
        main.cpp
        forms/mainwindow.h forms/mainwindow.cpp forms/mainwindow.ui
        forms/frmsplash.h forms/frmsplash.cpp forms/frmsplash.ui
        forms/frmlogin.h forms/frmlogin.cpp forms/frmlogin.ui
        forms/frmproductoslist.h forms/frmproductoslist.cpp forms/frmproductoslist.ui
        forms/frmusuarioslist.h forms/frmusuarioslist.cpp forms/frmusuarioslist.ui
        forms/frmusuariosform.h forms/frmusuariosform.cpp forms/frmusuariosform.ui
        forms/frmroleslist.h forms/frmroleslist.cpp forms/frmroleslist.ui
        forms/frmrolesform.h forms/frmrolesform.cpp forms/frmrolesform.ui
        forms/frmabrircerrarcaja.h forms/frmabrircerrarcaja.cpp forms/frmabrircerrarcaja.ui
        forms/frmconfiguracion.h forms/frmconfiguracion.cpp forms/frmconfiguracion.ui
        forms/frmsolicitarcontrasena.h forms/frmsolicitarcontrasena.cpp forms/frmsolicitarcontrasena.ui
        forms/frmproductosform.h forms/frmproductosform.cpp forms/frmproductosform.ui
        forms/frmproveedoreslist.h forms/frmproveedoreslist.cpp forms/frmproveedoreslist.ui
        forms/frmproveedoresform.h forms/frmproveedoresform.cpp forms/frmproveedoresform.ui
        util/crelaxeddoublespinbox.h util/crelaxeddoublespinbox.cpp
        util/flowlayout.h util/flowlayout.cpp
        controls/treeitem.h controls/treeitem.cpp
        controls/treemodel.h controls/treemodel.cpp
        controls/treeviewautohideable.h controls/treeviewautohideable.cpp
        controls/productoproveedorcontrol.h controls/productoproveedorcontrol.cpp controls/productoproveedorcontrol.ui
        Resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MarpajarosTPV
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MarpajarosTPV APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MarpajarosTPV SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MarpajarosTPV
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MarpajarosTPV PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(MarpajarosTPV PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS MarpajarosTPV
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MarpajarosTPV)
endif()
