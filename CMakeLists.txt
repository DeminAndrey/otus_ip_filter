cmake_minimum_required(VERSION 3.12)

option(CHECK_DOXYGEN "enable doc generation" ON)

set(APP_NAME print-ip)
if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(${APP_NAME} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${APP_NAME} VERSION 0.0.1)
endif()

configure_file(version.h.in version.h)

if (${CHECK_DOXYGEN} STREQUAL ON)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        set(DOXYFILE ${CMAKE_SOURCE_DIR}/Doxyfile)
        add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE} 
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen")
        unset(DOXYFILE)
    endif()
endif()

add_executable(${APP_NAME} main.cxx)

set_target_properties(${APP_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${APP_NAME} PRIVATE ${CMAKE_BINARY_DIR})
#target_compile_options(${APP_NAME} PRIVATE -Wall -Wpedantic -Wextra -Werror)

install(TARGETS ${APP_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT scfocus@yandex.ru)

include(CPack)
