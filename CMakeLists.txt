cmake_minimum_required(VERSION 3.16)

project(shopping-list VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

add_library(storage INTERFACE)

target_include_directories(storage INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/Storage)

qt_standard_project_setup(REQUIRES 6.10)

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/importedcontent)
endif()

qt_add_executable(shopping-list
    main.cpp
)

qt_add_qml_module(shopping-list
    URI ShoppingList
    QML_FILES
        Main.qml
)

set_target_properties(shopping-list PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(shopping-list
    PRIVATE Qt6::Quick storage
)

install(TARGETS shopping-list
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
