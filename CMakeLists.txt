cmake_minimum_required(VERSION 3.14)
project(WzLib)

set(WZLIB_NAME "WzLib" CACHE STRING "Name of the WzLib target")
set(CMAKE_CXX_STANDARD 17)


# Generate TLB files
set(IDL_DIR ${CMAKE_CURRENT_SOURCE_DIR})
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
    # DX9 IDL
    IWzGr2DLayer_DX9.idl
    IWzGr2D_DX9.idl
)

set(TLB_FILES "")
foreach(IDL_FILE IN LISTS IDL_FILES)
    get_filename_component(IDL_NAME ${IDL_FILE} NAME_WE)
    set(TLB_FILE "${CMAKE_CURRENT_BINARY_DIR}/${IDL_NAME}.tlb")

    add_custom_command(
        OUTPUT ${TLB_FILE}
        COMMAND midl /nologo /win32 /I ${IDL_DIR} /tlb ${TLB_FILE} ${IDL_FILE}
        DEPENDS ${IDL_FILE}
        COMMENT "Running MIDL on ${IDL_FILE}"
        VERBATIM
    )
    list(APPEND TLB_FILES ${TLB_FILE})
endforeach()

set(IDL_TARGET_NAME ${WZLIB_NAME}_IDL)
add_custom_target(${IDL_TARGET_NAME} DEPENDS ${TLB_FILES})


# Generate TLH files
set(GENERATOR_NAME ${WZLIB_NAME}_TLH)
add_library(${GENERATOR_NAME} STATIC
    generate.cpp
)

add_dependencies(${GENERATOR_NAME} ${IDL_TARGET_NAME})

target_include_directories(${GENERATOR_NAME} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)


# Process into header files
add_custom_command(
    TARGET ${GENERATOR_NAME} POST_BUILD
    COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/process.py ${CMAKE_CURRENT_BINARY_DIR}/${GENERATOR_NAME}.dir/${CMAKE_CFG_INTDIR} ${CMAKE_CURRENT_SOURCE_DIR}/include/WzLib
)


# Add library
set(LIBRARY_NAME ${WZLIB_NAME})
add_library(${LIBRARY_NAME} INTERFACE)

add_dependencies(${LIBRARY_NAME} ${GENERATOR_NAME})

target_include_directories(${LIBRARY_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(${LIBRARY_NAME} INTERFACE cxx_std_17)


# Compile Gr2D_DX8to9
set(WZLIB_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE STRING "" FORCE)
add_subdirectory(Gr2D_DX8to9)
add_dependencies(Gr2D_DX8to9 ${GENERATOR_NAME})
