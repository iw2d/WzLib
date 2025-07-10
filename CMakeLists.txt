cmake_minimum_required(VERSION 3.14)
project(WzLib)

set(CMAKE_CXX_STANDARD 17)


set(IDL_DIR ${CMAKE_SOURCE_DIR})
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


add_library(${PROJECT_NAME} SHARED
    main.cpp
)
add_dependencies(${PROJECT_NAME} IDL_ALL)

