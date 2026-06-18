set(CAMKES_COMPONENT_DIRS
    "../BusyBox"
    "../drivers/Framebuffer"
    "../drivers/USB"
    "../AzulaInit"
)

foreach(dir ${CAMKES_COMPONENT_DIRS})
    add_subdirectory(${dir} ${CMAKE_CURRENT_BINARY_DIR}/components/${dir})
endforeach()

DeclareCAmkESRootserver(AzulaOS.camkes)
