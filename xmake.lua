add_requires("gtest")

add_cxflags("-g", "-Wall", "-std=c++17")

target("front_end")
    set_kind("static")
    add_files("src/*.cpp")
    add_includedirs("inc")

target("test")
    set_kind("binary")
    add_files("test/*.cpp")
    add_includedirs("inc")
    add_packages("gtest")
    add_deps("front_end")