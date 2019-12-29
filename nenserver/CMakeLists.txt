# Add sources
set(
    SOURCES
        "src/env.cpp"
        "src/main.cpp"
)
add_executable(nenserver ${SOURCES})
target_include_directories(nenserver PUBLIC "include")

# Link everything
include_directories(${chipmunk_SOURCE_DIR}/include)

if(APPLE)
include_directories(${CMAKE_SOURCE_DIR}/SFML/extlibs/libs-osx/Frameworks/freetype.framework/Versions/A/freetype)
endif()

target_link_libraries(nenserver chipmunk sfml-graphics sfml-window libzmq)

# Add resources
file(COPY "assets" DESTINATION "./")

install(
    TARGETS nenserver
    ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib
    LIBRARY DESTINATION ${lPROJECT_SOURCE_DIR}/lib
    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
)
