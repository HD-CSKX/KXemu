if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/configs/.config)
    message(FATAL_ERROR "${CMAKE_CURRENT_SOURCE_DIR}/configs does not exist!")
endif()

function(parse_kconfig config_file)
    file(STRINGS "${config_file}" lines)

    foreach(line IN LISTS lines)
        if(line MATCHES "^# (CONFIG_[A-Za-z0-9_]+) is not set")
            set(${CMAKE_MATCH_1} OFF PARENT_SCOPE)
            continue()
        endif()

        if(line MATCHES "^(CONFIG_[A-Za-z0-9_]+)=([yYnN]|\".*\")$")
            set(var_name "${CMAKE_MATCH_1}")
            set(var_value "${CMAKE_MATCH_2}")

            if(var_value MATCHES "^(y|Y)$")
                set(var_value ON)
            elseif(var_value MATCHES "^(n|N)$")
                set(var_value OFF)
            else()
                string(REGEX REPLACE "^\"(.*)\"$" "\\1" var_value "${var_value}")
            endif()

            set(${var_name} "${var_value}" PARENT_SCOPE)
        endif()
    endforeach()
endfunction()

parse_kconfig(${CMAKE_CURRENT_SOURCE_DIR}/configs/.config)

if(CONFIG_DEBUG)
    set(CMAKE_BUILD_TYPE Debug)
else()
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CCACHE_PROGRAM ccache)

if(CCACHE_PROGRAM)
    message(STATUS "Found CCache: ${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
else()
    message(STATUS "ccache not found")
endif()

set(CMAKE_CXX_COMPILER ${CONFIG_CC})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CONFIG_CC_EXTRA_FLAGS "")

if(CONFIG_CC_ADDRASAN)
    list(APPEND CONFIG_CC_EXTRA_FLAGS "-fsanitize=address")
endif()

if(CONFIG_CC_UBASAN)
    list(APPEND CONFIG_CC_EXTRA_FLAGS "-fsanitize=undefined")
endif()

add_compile_options(${CONFIG_CC_EXTRA_FLAGS})
add_link_options(${CONFIG_CC_EXTRA_FLAGS})
