add_rules("mode.debug", "mode.release")
add_requires("spdlog")
set_languages("c++latest")

target("learn-design-patterns")
set_kind("binary")
add_files("src/*.cpp")
add_packages("spdlog")
target_end()
