cmake_minimum_required(VERSION 4.0)
project(dsp_my)

set(CMAKE_CXX_STANDARD 17)

#  GoogleTest
find_package(GTest REQUIRED)
find_package(Eigen3 REQUIRED)

#
#enable_testing()

include_directories(dsp_my)

#
add_executable(dsp_my
        dsp_my/Complex.h
        dsp_my/demodulator.cpp
        dsp_my/Demodulator.h
        dsp_my/downsample.cpp
        dsp_my/dsp_my.cpp
        dsp_my/filter.cpp
        dsp_my/Signal.h
        dsp_my/load_bin_and_data.cpp
        dsp_my/any_function.h
        dsp_my/save_wav_and_iqw.cpp
        dsp_my/save_bin_and_dat.cpp
        dsp_my/Class_declarations.h
        dsp_my/FileManager.cpp
        dsp_my/load_wav_and_iqw.cpp
)

#
add_executable(test
        dsp_my/load_wav_and_iqw.cpp
        dsp_my/load_wav_and_iqw.cpp

)

#
target_link_libraries(test
        GTest::gtest
        GTest::gtest_main
        pthread
)

# �
include(GoogleTest)
gtest_discover_tests(test)