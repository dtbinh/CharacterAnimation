
PROJECT(CharA)

############################## LES OPTIONS
SET( CMAKE_BUILD_TYPE Debug)			# used only by make
#SET( CMAKE_BUILD_TYPE RelWithDebInfo)
#SET( CMAKE_BUILD_TYPE Release)

#si vous avez besoin de spéficiez le chemin vers GLUT
SET(GLUT_HOME 		"D:\\alex\\lib\\freeglut-2.8.1-mingw")
###################################################




cmake_minimum_required(VERSION 2.4)
if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

###### Dependencies
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/")

######## OPENGL
FIND_PACKAGE(OpenGL REQUIRED)
MESSAGE(STATUS "OPENGL_FOUND=${OPENGL_FOUND}")
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
   MESSAGE( STATUS "    OPENGL_INCLUDE_DIR=${OPENGL_INCLUDE_DIR}" )
   MESSAGE( STATUS "    OPENGL_LIBRARIES=${OPENGL_LIBRARIES}" )


FIND_PACKAGE(GLUT REQUIRED)
MESSAGE(STATUS "GLUT_FOUND=${GLUT_FOUND}")
INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIR})
   MESSAGE( STATUS "    GLUT_INCLUDE_DIR=${GLUT_INCLUDE_DIR}" )
   MESSAGE( STATUS "    GLUT_LIBRARIES=${GLUT_LIBRARIES}" )



INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/ext)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CACore)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CALoader)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CAMath)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CAPhysics)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CAViewer)


SET( CHARA_FILES
			./src/CALoader/BVHChannel.cpp
			./src/CALoader/BVHChannel.h

			./src/CALoader/BVHAxis.h
			./src/CAMath/Mat4.h
			./src/CAMath/Vec4.h
			./src/CAMath/Vec3.h
			./src/CAMath/Vec2.h
			./src/CAMath/Quaternion.h
			./src/ext/GLee.h

			./src/CALoader/BVH.h
			./src/CALoader/BVH.cpp

			./src/CALoader/BVHJoint.h
			./src/CALoader/BVHJoint.cpp

			./src/CACore/CASkeleton.h
			./src/CACore/CASkeleton.cpp

			./src/CAViewer/Camera.h
			./src/CAViewer/Viewer.h
			./src/CAViewer/Viewer.cpp
			./src/CAViewer/CAViewer.h
			./src/CAViewer/CAViewer.cpp
			./src/CAViewer/main.cpp
)


ADD_EXECUTABLE( CharA  ${CHARA_FILES})
TARGET_LINK_LIBRARIES( CharA  	${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${BULLET_LIBRARIES})
SET_TARGET_PROPERTIES( CharA PROPERTIES DEBUG_POSTFIX _d)
SET_TARGET_PROPERTIES( CharA PROPERTIES COMPILE_FLAGS -D_CRT_SECURE_NO_WARNINGS)
SET_TARGET_PROPERTIES( CharA PROPERTIES PROJECT_LABEL _app_CharA)
SET(TARGET ${TARGET}  CharA)
MESSAGE(STATUS "Building app CharA")
