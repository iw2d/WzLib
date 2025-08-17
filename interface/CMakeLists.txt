# Generate TLB files
set(IDL_DIR ${CMAKE_SOURCE_DIR}/interface)
set(IDL_FILES
    IWzArchive.idl
    IWzSeekableArchive.idl
    IWzSerialize.idl
    IWzProperty.idl
    IWzNameSpace.idl
    IWzWritableNameSpace.idl
    IWzPackage.idl
    IWzFileSystem.idl
    IWzResMan.idl
    IWzUOL.idl
    IWzCanvas.idl
    IWzSound.idl
    IWzShape2D.idl
    IWzConvex2D.idl
    IWzVector2D.idl
    IWzGr2DLayer.idl
    IWzGr2D.idl
)

set(TLB_FILES "")
foreach(IDL_FILE IN LISTS IDL_FILES)
    get_filename_component(IDL_NAME ${IDL_FILE} NAME_WE)
    set(TLB_FILE "${IDL_DIR}/${IDL_NAME}.tlb")

    add_custom_command(
        OUTPUT ${TLB_FILE}
        COMMAND midl /nologo /win32 /I ${IDL_DIR} /tlb ${TLB_FILE} ${IDL_FILE}
        DEPENDS ${IDL_FILE}
        COMMENT "Running MIDL on ${IDL_FILE}"
        VERBATIM
    )
    list(APPEND TLB_FILES ${TLB_FILE})
endforeach()

add_custom_target(IDL_ALL DEPENDS ${TLB_FILES})


# Generate TLH files
add_library(WzInterface STATIC
    generate.cpp
)
add_dependencies(WzInterface IDL_ALL)


# Process into header files
add_custom_command(
    TARGET WzInterface POST_BUILD
    COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/process.py ${CMAKE_CURRENT_BINARY_DIR}/WzInterface.dir/${CMAKE_CFG_INTDIR} ${CMAKE_SOURCE_DIR}/include
)