function(fetch3Libs)
    include(FetchContent)
    message(STATUS "--------------------------------------")
    message(STATUS "Importing nlohmann_json")
    message(STATUS "--------------------------------------")
    FetchContent_Declare(
            nlohmann_json
            GIT_REPOSITORY https://github.com/nlohmann/json
            GIT_TAG v3.11.3
            GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(nlohmann_json)

    message(STATUS "--------------------------------------")
    message(STATUS "Importing fmt")
    message(STATUS "--------------------------------------")
    FetchContent_Declare(
            fmt
            GIT_REPOSITORY https://github.com/fmtlib/fmt
            GIT_TAG 9.1.0
            GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(fmt)

    message(STATUS "--------------------------------------")
    message(STATUS "Importing spdlog")
    message(STATUS "--------------------------------------")
    FetchContent_Declare(
            spdlog
            GIT_REPOSITORY https://github.com/gabime/spdlog
            GIT_TAG v1.13.0
            GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(spdlog)

    message(STATUS "--------------------------------------")
    message(STATUS "Importing cxxopts")
    message(STATUS "--------------------------------------")
    FetchContent_Declare(
            cxxopts
            GIT_REPOSITORY https://github.com/jarro2783/cxxopts
            GIT_TAG v3.1.1
            GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(cxxopts)


    message(STATUS "--------------------------------------")
    message(STATUS "Importing googletest")
    message(STATUS "--------------------------------------")
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest
            GIT_TAG v1.15.2
            GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(googletest)
endfunction(fetch3Libs)
