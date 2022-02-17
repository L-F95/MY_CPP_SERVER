cmake_minimum_required(VERSION 3.10)


project(newserver)



set(CLIENT client).cpp)
set(SERVER server.cpp)
aux_source_directory(./src SRC_CXX)



add_executable(Client ${SRC_CXX} ${CLIENT})

add_executable(Server ${SRC_CXX} ${SERVER})


include_directories(./include)

# target_link_libraries()