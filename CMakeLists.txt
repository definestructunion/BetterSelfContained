cmake_minimum_required(VERSION 3.15)
project(BetterSelfContained)

set(CMAKE_CXX_STANDARD 17)

# LINUX
add_compile_definitions(PLATFORM_LINUX)
set(MAIN_IMPL src/Mains/MainLinux.cpp src/Impl/ImplLinux.hpp)

# WINDOWS
#add_compile_definitions(PLATFORM_WINDOWS)
#set(MAIN_IMPL src/Mains/MainWindows.cpp src/Impl/ImplWindows.hpp)

#if(APPLE)
#    add_compile_definitions(PLATFORM_OSX)
#    set(MAIN_IMPL src/Mains/MainOsx.cpp src/Impl/ImplOsx.hpp)
#elseif(UNIX)
#    add_compile_definitions(PLATFORM_LINUX)
#    set(MAIN_IMPL src/Mains/MainLinux.cpp src/Impl/ImplLinux.hpp)
#else() #WIN32
#    add_compile_definitions(PLATFORM_WINDOWS)
#    set(MAIN_IMPL src/Mains/MainWindows.cpp src/Impl/ImplWindows.hpp)
#endif(APPLE)

add_executable(${PROJECT_NAME}
        ${MAIN_IMPL}
        src/coreclrhost.h
        src/Vendor/nlohmann/json.hpp
        src/Config/SelfContainedConfig.hpp
        src/Config/SelfContainedConfig.cpp
        src/Util/Utilities.hpp
        src/Util/Utilities.cpp)

# Removing the console
if(APPLE)
    target_compile_options(${PROJECT_NAME} PRIVATE -mwindows)
elseif(UNIX)
    #target_compile_options(${PROJECT_NAME} PRIVATE -mwindows)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
    target_compile_options(${PROJECT_NAME} PRIVATE -ldl)
else() #WIN32
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:WINDOWS)
endif(APPLE)