cmake_minimum_required(VERSION 3.19)
project(meal-planning LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)

qt_standard_project_setup()

qt_add_executable(meal-planning
    WIN32 MACOSX_BUNDLE
    main.cpp
    meal_planning.cpp
    meal_planning.h
    meal_planning.ui

    dropdownquerymodel.h dropdownquerymodel.cpp
    databaseconnection.h databaseconnection.cpp
)

target_link_libraries(meal-planning
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
)

include(GNUInstallDirs)

install(TARGETS meal-planning
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET meal-planning
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
