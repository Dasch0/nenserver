# Add sources
set(
    SOURCES
        "src/env.cpp"
        "src/main.cpp"
        "src/server.cpp"
        "src/renderer.cpp"
)
add_executable(nenserver ${SOURCES})
target_include_directories(nenserver PUBLIC "include")

# Link everything
include_directories(${chipmunk_SOURCE_DIR}/include)

include_directories(${CMAKE_SOURCE_DIR}/SFML/extlibs/libs-osx/Frameworks/freetype.framework/Versions/A/freetype)

target_link_libraries(nenserver chipmunk sfml-graphics sfml-window libzmq)
install(
    TARGETS nenserver
    ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib
    LIBRARY DESTINATION ${lPROJECT_SOURCE_DIR}/lib
    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
)
