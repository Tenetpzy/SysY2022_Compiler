add_requires("gtest")

add_cxflags("-g", "-Wall", "-std=c++17")

target("front_end")
    set_kind("static")
    on_load
    (
        function ()
            import("core.project.depend")
            local targetfile
            for _, tarfile in ipairs(os.files("$(scriptdir)/frontend_src/*.l")) do 
                -- 只有当.l源文件改变时，才重新编译
                depend.on_changed   
                (
                    function()
                        targetfile = path.basename(tarfile) .. ".cc"
                        os.runv("flex", {"-o", targetfile, tarfile})
                        os.mv(targetfile, "$(scriptdir)/src")
                    end,
                    {files = tarfile}
                )
            end

            for _, tarfile in ipairs(os.files("$(scriptdir)/frontend_src/*.yy")) do 
                depend.on_changed
                (
                    function()
                        targetfile = path.basename(tarfile) .. ".cc"
                        os.runv("bison", {"-o", targetfile, tarfile})
                        os.mv(targetfile, "$(scriptdir)/src")
                        os.mv(path.basename(tarfile) .. ".hh", "$(scriptdir)/inc")
                    end,
                    {files = tarfile}
                )
            end
        end
    )
    add_files("src/*.cpp|main.cpp", "src/*.cc")
    add_includedirs("inc")


target("test")
    set_kind("binary")
    add_files("test/*.cpp")
    add_includedirs("inc")
    add_packages("gtest")
    add_deps("front_end")

target("compiler")
    set_kind("binary")
    add_files("src/main.cpp")
    add_deps("front_end")
    set_targetdir("$(scriptdir)")
    add_includedirs("inc")