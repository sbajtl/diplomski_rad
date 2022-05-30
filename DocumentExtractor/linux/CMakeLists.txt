option(USE_CCACHE "Use ccache during compile if exist?" on)
find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND AND (USE_CCACHE))
    MESSAGE(STATUS "## Using CCache when building!")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
else (CCACHE_FOUND AND (USE_CCACHE))
    MESSAGE(STATUS "## Not using CCache!")
endif (CCACHE_FOUND AND (USE_CCACHE))

add_definitions(-pthread)

set(LINUX_SRCS
        linux/main.cc
        )

set(LINUX_HDRS)

list(APPEND SRCS ${LINUX_SRCS})
list(APPEND HDRS ${LINUX_HDRS})
