set(INSTPAT_NAMES base compressed)

set(INSTPAT_SRC_DIR ${PROJECT_SOURCE_DIR}/src/cpu/riscv/instpat)
set(INSTPAT_DST_DIR ${PROJECT_SOURCE_DIR}/src/cpu/riscv/autogen)
set(DECODE_GEN_SCRIPT ${PROJECT_SOURCE_DIR}/scripts/riscv-decoder-gen/main.py)

foreach(name ${INSTPAT_NAMES})
    set(instpat_src ${INSTPAT_SRC_DIR}/${name}.instpat)
    set(instpat_dst ${INSTPAT_DST_DIR}/${name}-decoder.inc)

    add_custom_command(
        OUTPUT ${instpat_dst}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${INSTPAT_DST_DIR}
        COMMAND python3 ${DECODE_GEN_SCRIPT} --input ${instpat_src} --output ${instpat_dst}
        DEPENDS ${instpat_src} ${DECODE_GEN_SCRIPT}
        COMMENT "GEN ${name}-decoder.inc"
    )
endforeach()

set(INSTPAT_DST_FILES)

foreach(name ${INSTPAT_NAMES})
    list(APPEND INSTPAT_DST_FILES ${INSTPAT_DST_DIR}/${name}-decoder.inc)
endforeach()

add_custom_target(instpat
    DEPENDS ${INSTPAT_DST_FILES}
)

add_dependencies(${KXEMU_TARGET} instpat)
