# Copyright (c) 2011-2021, The DART development contributors
# All rights reserved.
#
# The list of contributors can be found at:
#   https://github.com/dartsim/dart/blob/main/LICENSE
#
# This file is provided under the "BSD-style" License

dart_add_component_sub_directory(
  COMPONENT_DEPENDENCY_PACKAGES
    OpenSceneGraph
  TARGET_LINK_LIBRARIES_PUBLIC
    osg::osg
  SUB_DIRECTORIES
    render
)
