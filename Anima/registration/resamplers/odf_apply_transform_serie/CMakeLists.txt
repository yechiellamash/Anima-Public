if(BUILD_TOOLS AND USE_RPI AND RPI_FOUND)

project(animaODFApplyTransformSerie)

## #############################################################################
## List Sources
## #############################################################################

list_source_files(${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

## #############################################################################
## add executable
## #############################################################################

add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_CFILES}
  )


## #############################################################################
## Link
## #############################################################################

target_link_libraries(${PROJECT_NAME}
  ${ITKIO_LIBRARIES}
  ${ITK_TRANSFORM_LIBRARIES}
  ${TinyXML2_LIBRARY}
  AnimaSHTools
  )

## #############################################################################
## install
## #############################################################################

set_exe_install_rules(${PROJECT_NAME})

endif()
