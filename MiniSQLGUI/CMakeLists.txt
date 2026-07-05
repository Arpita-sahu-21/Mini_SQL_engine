cmake_minimum_required(VERSION 3.19)
project(MiniSQLGUI LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(MiniSQLGUI
    WIN32
    MACOSX_BUNDLE

    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    ../src/Database.cpp
    ../src/Database.h

    ../src/Engine.cpp
    ../src/Engine.h

    ../src/Parser.cpp
    ../src/Parser.h

    ../src/Storage.cpp
    ../src/Storage.h

    ../src/Table.cpp
    ../src/Table.h

    ../src/Utils.h
)
target_include_directories(MiniSQLGUI PRIVATE
    ../src
)

target_link_libraries(MiniSQLGUI
    PRIVATE
        Qt::Core
        Qt::Widgets
)
install(TARGETS MiniSQLGUI
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET MiniSQLGUI
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
