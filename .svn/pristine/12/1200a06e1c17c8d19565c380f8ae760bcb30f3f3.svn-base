#-*-cmake-*-
#
# Test for GLUT libraries
#
# Once loaded this will define
#  GLUT_FOUND        - system has libGLUT
#  GLUT_INCLUDE_DIR  - include directory
#  GLUT_LIBRARIES    - libraries you need to link to
#

SET(GLUT_FOUND   "NO" )

FIND_PATH( GLUT_INCLUDE_DIR glut.h
	"${GLUT_HOME}/"
	"${GLUT_HOME}/include"
	"${GLUT_HOME}/include/GL"
	/usr/include/GL
	/usr/include/
  )

FIND_LIBRARY(GLUT_LIBRARIES
  NAMES GLUT glut32 glut freeglut
  PATHS
	"${GLUT_HOME}/"
	"${GLUT_HOME}/lib"
	"${GLUT_HOME}/lib/x86"
	"${GLUT_HOME}/bin"
	"${GLUT_HOME}/bin/x86"
	/usr/lib
	)


IF (GLUT_INCLUDE_DIR)
  IF(GLUT_LIBRARIES)
    SET(GLUT_FOUND "YES")
    GET_FILENAME_COMPONENT(GLUT_LIBRARY_DIR ${GLUT_LIBRARIES}   PATH)
  ENDIF(GLUT_LIBRARIES)
ENDIF(GLUT_INCLUDE_DIR)

#MESSAGE( GLUT_LIBRARIES=${GLUT_LIBRARIES} )

IF(NOT GLUT_FOUND)
	MESSAGE( GLUT_HOME=${GLUT_HOME} )
	MESSAGE( GLUT_INCLUDE_DIR=${GLUT_INCLUDE_DIR} )
	MESSAGE( GLUT_LIBRARIES=${GLUT_LIBRARIES} )
	MESSAGE(FATAL_ERROR "GLUT required, please specify it's location with GLUT_HOME")
ENDIF(NOT GLUT_FOUND)

#####
