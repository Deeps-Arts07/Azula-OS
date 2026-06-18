set(CAMKES_COMPONENT_DIRS
    "../../../../camkes-components/BusyBox"
    "../../../../camkes-components/drivers/Framebuffer"
    "../../../../camkes-components/drivers/USB"
    "../../../../camkes-components/AzulaInit"
)

foreach(dir ${CAMKES_COMPONENT_DIRS})
    get_filename_component(name ${dir} NAME)
    add_subdirectory(${dir} ${CMAKE_CURRENT_BINARY_DIR}/components/${name})
endforeach()

list(APPEND CAmkES_CPP_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/../../../../camkes-components")
list(APPEND CAmkES_CPP_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/../../../../camkes-components/interfaces")

DeclareCAmkESRootserver(AzulaOS.camkes)
