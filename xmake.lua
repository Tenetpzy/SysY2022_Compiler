add_cxflags("-std=c++11")

target("compile")
    set_kind("binary")
    add_files("src/*.cpp")
    add_includedirs("inc")