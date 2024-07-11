add_rules("mode.debug", "mode.release")
set_languages("c++latest")

add_requires("spdlog")

target("learn-design-patterns")
set_kind("binary")
add_files("src/*.cpp")
set_warnings("all")
add_packages("spdlog")
target_end()
