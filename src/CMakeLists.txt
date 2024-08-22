project(ACG_GET)
# find source
file(GLOB_RECURSE SRC_LIST "${CMAKE_SOURCE_DIR}/src/*.cpp")

#import CURL

set(CURL_ROOT "/usr/local/curl")

find_package(Curses REQUIRED)


add_executable(${PROJECT_NAME} ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CURL_ROOT}/include
    ${CURSES_INCLUDE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
    ${CURL_ROOT}/lib/libcurl_ssl_zlib.a
    ${CURSES_LIBRARY}
)