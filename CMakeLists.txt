cmake_minimum_required(VERSION 3.12)

option(CHECK_DOXYGEN "enable doc generation" ON)

set(PROJECTNAME print-ip)
if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(${PROJECTNAME} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${PROJECTNAME} VERSION 0.0.1)
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

add_executable(${PROJECTNAME} main.cxx)

set_target_properties(${PROJECTNAME}
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${PROJECTNAME}
  PRIVATE ${CMAKE_BINARY_DIR})

if(MSVC)
    target_compile_options(${PROJECTNAME} PRIVATE
        /W4
    )
else()
    target_compile_options(${PROJECTNAME} PRIVATE
        -Werror -Wall -Wimplicit-fallthrough -pedantic-errors
    )
endif()

install(TARGETS ${PROJECTNAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT scfocus@yandex.ru)

include(CPack)
