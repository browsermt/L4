cmake_minimum_required(VERSION 2.8.12)
project(L4 CXX)

# Enable setting options from repository above.
if (POLICY CMP0077)
  cmake_policy(SET CMP0077 NEW)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  if(L4_COMPILE_UNIT_TESTS)
      add_definitions(-DBOOST_TEST_DYN_LINK)
  endif(L4_COMPILE_UNIT_TESTS)

endif()

if(L4_COMPILE_UNIT_TESTS)
    set(Boost_USE_STATIC_LIBS OFF) 
    set(Boost_USE_MULTITHREADED ON)  
    set(Boost_USE_STATIC_RUNTIME OFF) 
    find_package(Boost 1.45.0 COMPONENTS unit_test_framework REQUIRED)
    if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS}) 
    endif()
endif(L4_COMPILE_UNIT_TESTS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/L4)

# Need to expand the followings for installation.
set(L4_HEADERS
    inc/L4/Utils/MurmurHash3.h)

set(L4_SOURCES
    src/EpochActionManager.cpp
    src/MurmurHash3.cpp
    src/PerfLogger.cpp)

add_library(L4
    ${L4_SOURCES}
    ${L4_HEADERS})

if(L4_COMPILE_UNIT_TESTS)
    enable_testing()
    add_executable(L4.UnitTests
        Unittests/CacheHashTableTest.cpp
        Unittests/EpochManagerTest.cpp
        Unittests/HashTableManagerTest.cpp
        Unittests/HashTableRecordTest.cpp
        Unittests/HashTableServiceTest.cpp
        Unittests/PerfInfoTest.cpp
        Unittests/ReadWriteHashTableSerializerTest.cpp
        Unittests/ReadWriteHashTableTest.cpp
        Unittests/SettingAdapterTest.cpp
        Unittests/Utils.cpp
        Unittests/UtilsTest.cpp
        Unittests/Main.cpp)

    target_link_libraries(L4.UnitTests
        L4
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        -lpthread)
        #${CMAKE_THREAD_LIBS_INIT})

    add_test(NAME L4UnitTests COMMAND L4.UnitTests)

endif(L4_COMPILE_UNIT_TESTS)
