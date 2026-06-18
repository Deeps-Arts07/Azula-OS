set(CAMKES_COMPONENT_DIRS
    "${CMAKE_CURRENT_LIST_DIR}/../../../../camkes-components/BusyBox"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../camkes-components/drivers/Framebuffer"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../camkes-components/drivers/USB"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../camkes-components/AzulaInit"
)

foreach(dir ${CAMKES_COMPONENT_DIRS})
    get_filename_component(name ${dir} NAME)
    add_subdirectory(${dir} ${CMAKE_CURRENT_BINARY_DIR}/components/${name})
endforeach()

list(APPEND CAmkES_CPP_INCLUDES "${CMAKE_CURRENT_LIST_DIR}/../../../../camkes-components")
list(APPEND CAmkES_CPP_INCLUDES "${CMAKE_CURRENT_LIST_DIR}/../../../../camkes-components/interfaces")

DeclareCAmkESRootserver(AzulaOS.camkes)
