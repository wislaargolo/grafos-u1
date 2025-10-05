cmake_minimum_required(VERSION 3.14)
project(GraphTests CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tenta primeiro o pacote CONFIG (targets GTest::gtest etc.)
find_package(GTest QUIET CONFIG)
if (NOT GTest_FOUND)
  # Tenta o módulo FindGTest (define variáveis GTEST_* ao invés de targets)
  find_package(GTest QUIET)
endif()

# Se ainda não achou, pode cair para FetchContent (descomentando este bloco)
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
# )
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

add_executable(graph_tests graph_tests.cpp)

# Link robusto cobrindo os três jeitos (targets modernos, targets antigos, variáveis do FindGTest)
if (TARGET GTest::gtest_main)
  target_link_libraries(graph_tests PRIVATE GTest::gtest_main)
elseif (TARGET gtest_main)
  target_link_libraries(graph_tests PRIVATE gtest_main)
elseif (GTEST_MAIN_LIBRARIES)
  target_link_libraries(graph_tests PRIVATE ${GTEST_MAIN_LIBRARIES})
  if (GTEST_INCLUDE_DIRS)
    target_include_directories(graph_tests PRIVATE ${GTEST_INCLUDE_DIRS})
  endif()
else()
  message(FATAL_ERROR "GoogleTest não encontrado. Instale libgtest-dev/googletest, ou habilite o bloco FetchContent.")
endif()

include(GoogleTest)
gtest_discover_tests(graph_tests)
