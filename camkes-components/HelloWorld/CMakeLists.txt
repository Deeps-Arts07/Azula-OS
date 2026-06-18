cmake_minimum_required(VERSION 3.8.2)

project(AzulaOS C CXX ASM)

# In a full setup, this relies on seL4 build tools being present in the workspace
# e.g., via a repo manifest or submodules for camkes-tool, seL4_libs, etc.
# For Phase 1 we assume the seL4 tools are available.

find_package(camkes-project REQUIRED)

DeclareCAmkESComponent(
    Hello
    SOURCES src/hello.c
)

DeclareCAmkESRootserver(
    HelloWorld.camkes
)
