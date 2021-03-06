# Copyright (c) 2011-2021, The DART development contributors
# All rights reserved.
#
# The list of contributors can be found at:
#   https://github.com/dartsim/dart/blob/main/LICENSE
#
# This file is provided under the "BSD-style" License

# Set basic component settings
set(project_name ${PROJECT_NAME})
set(component_name gui)

# Add component
dart_add_component(
  PROJECT_NAME
    ${PROJECT_NAME}
  PROJECT_VERSION_MAJOR
    ${DART_MAJOR_VERSION}
  PROJECT_SOURCE_DIR
    ${DART_SOURCE_DIR}
  PROJECT_BINARY_DIR
    ${DART_BINARY_DIR}
  COMPONENT_NAME
    ${component_name}
  COMPONENT_DEPENDENCIES
    external-imgui  # TODO(JS): Make this a private dependency
    common math optimization collision dynamics simulation io
  COMPONENT_DEPENDENCY_PACKAGES
    OpenGL
  TARGET_LINK_LIBRARIES_PUBLIC
    OpenGL::GL
    OpenGL::GLU
  TARGET_COMPILE_FEATURES_PUBLIC
    cxx_std_17
  SUB_DIRECTORIES
    glut osg
  GENERATE_META_HEADER
  FORMAT_CODE
)
