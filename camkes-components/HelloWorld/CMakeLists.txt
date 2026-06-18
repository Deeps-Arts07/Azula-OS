set(Hello_sources src/hello.c)

DeclareCAmkESComponent(
    Hello
    SOURCES ${Hello_sources}
)

DeclareCAmkESRootserver(
    HelloWorld.camkes
)
