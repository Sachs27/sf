solution "libsf"
    configurations {"Debug", "Release"}

    language "C"

    includedirs {"include/"}

    configuration "Debug"
        defines {"SF_DEBUG"}
        flags {"ExtraWarnings", "Symbols"}

    configuration "Release"
        defines {"NDEBUG"}
        flags {"Optimize"}

    project "sf"
        kind "StaticLib"
        targetdir "lib/"
        files {
            "src/*.c"
        }

    project "test-array"
        kind "ConsoleApp"
        targetdir "test/"
        links {"sf"}
        files {
            "test/test_array.c"
        }

    project "test-list"
        kind "ConsoleApp"
        targetdir "test/"
        links {"sf"}
        files {
            "test/test_list.c"
        }

    project "test-log"
        kind "ConsoleApp"
        targetdir "test/"
        links {"sf"}
        files {
            "test/test_log.c"
        }
