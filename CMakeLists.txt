cmake_minimum_required(VERSION 3.7)

project(boost-log)

set(SOURCES
    main.cpp
    logger.cpp
)


# Boost
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/opt/boost_1_63_0")
add_definitions(-DBOOST_ALL_DYN_LINK)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS log_setup log)

if(Boost_FOUND)
  add_executable(${PROJECT_NAME} ${SOURCES})
  target_link_libraries(${PROJECT_NAME} Boost::log_setup Boost::log)
endif()
