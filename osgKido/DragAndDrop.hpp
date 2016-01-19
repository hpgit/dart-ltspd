/*
 * Copyright (c) 2015, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Michael X. Grey <mxgrey@gatech.edu>
 *
 * Georgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef OSGKIDO_DRAGANDDROP_HPP
#define OSGKIDO_DRAGANDDROP_HPP

#include <functional>

#include <Eigen/Geometry>

#include "kido/common/sub_ptr.hpp"
#include "kido/dynamics/Entity.hpp"
#include "kido/dynamics/Shape.hpp"
#include "DefaultEventHandler.hpp"

namespace kido {
namespace dynamics {
class SimpleFrame;
} // namespace dynamics
} // namespace kido

namespace osgKido
{

class Viewer;
class InteractiveFrame;

/// DragAndDrop is a class that facilitates enabling various kinds of kido
/// Entities to be dragged and dropped in an osgKido environment
class DragAndDrop : public kido::common::Subject,
                    public kido::common::Observer
{
public:

  enum class RotationOption : int {

    HOLD_MODKEY = 0, // Default setting, hold ctrl key to rotate
    ALWAYS_ON,
    ALWAYS_OFF

  };

  /// Constructor
  DragAndDrop(Viewer* viewer, kido::dynamics::Entity* entity);

  /// Virtual destructor
  virtual ~DragAndDrop();

  /// Get the Entity that this DragAndDrop is associated with
  kido::dynamics::Entity* getEntity() const;

  /// Called when mouse events are being handled
  virtual void update();

  /// If true is passed in, this object will only be drag and droppable if there
  /// are no other objects between its picked point and the camera.
  void setObstructable(bool _obstructable);

  /// If this is true, then this object will only be drag and droppable if there
  /// are no other objects between its picked point and the camera. Default is
  /// true.
  bool isObstructable() const;

  /// Called to specify how the Entity should be moved
  virtual void move() = 0;

  /// Called when a point gets picked, and is used to save the current state of
  /// the Entity
  virtual void saveState() = 0;

  /// Called when the user lets go of the object that they are dragging and
  /// dropping. This function does nothing by default, but you can override it.
  virtual void release();

  /// Default method for getting the translation requested by the user
  virtual Eigen::Vector3d getConstrainedDx() const;

  /// Default method for getting the rotation requested by the user
  virtual Eigen::AngleAxisd getConstrainedRotation() const;

  /// Remove all constraints from the dragging and dropping.
  void unconstrain();

  /// Constrain translation to only occur along the given slope, or constrain
  /// rotation to only occur about the given slope. For rotation, this function
  /// is equivalent to constrainToPlane
  void constrainToLine(const Eigen::Vector3d& slope);

  /// Constrain translation to only occur within the plane defined by the given
  /// normal, or constrain rotation to only occur about the given normal. For
  /// rotation, this function is equivalent to constrainToLine
  void constrainToPlane(const Eigen::Vector3d& normal);

  /// Returns the mAmMoving flag
  bool isMoving() const;

  /// Set the option for triggering rotations instead of translations
  void setRotationOption(RotationOption option);

  /// Get the current rotation option for this DnD
  RotationOption getRotationOption() const;

  /// Set the modkey that will be used to toggle rotation for this DnD
  void setRotationModKey(osgGA::GUIEventAdapter::ModKeyMask rotationModKey);

  /// Get the modkey that will be used to toggle rotation for this DnD
  osgGA::GUIEventAdapter::ModKeyMask getRotationModKey() const;

protected:

  /// Perform cleanup when the subject is destroyed
  virtual void handleDestructionNotification(
      const kido::common::Subject* subscription) override;

  /// Pointer to the DnD's Viewer
  Viewer* mViewer;

  /// Pointer to the DnD's Entity
  kido::dynamics::Entity* mEntity;

  /// The location in the world that was picked by the user
  Eigen::Vector3d mPickedPosition;

  /// Reference vector for constraint (slope for line constraint, or normal for
  /// plane constraint)
  Eigen::Vector3d mVector;

  /// Point in space about which rotations should happen
  Eigen::Vector3d mPivot;

  /// Constraint type for this DnD
  ConstraintType mConstraintType;

  /// Whether other objects can block this one from being picked
  bool mAmObstructable;

  /// Whether this DnD is currently moving
  bool mAmMoving;

  /// Option for rotation settings
  RotationOption mRotationOption;

  /// Modkey for rotation
  osgGA::GUIEventAdapter::ModKeyMask mRotationModKey;

};

//==============================================================================
/// SimpleFrameDnD is a DragAndDrop implementation for SimpleFrame objects
class SimpleFrameDnD : public DragAndDrop
{
public:

  /// Constructor
  SimpleFrameDnD(Viewer* viewer, kido::dynamics::SimpleFrame* frame);

  /// Virtual destructor
  virtual ~SimpleFrameDnD() = default;

  /// Get the SimpleFrame associated with this DnD
  kido::dynamics::SimpleFrame* getSimpleFrame() const;

  // Documentation inherited
  virtual void move() override;

  // Documentation inherited
  virtual void saveState() override;

protected:

  /// SimpleFrame pointer
  kido::dynamics::SimpleFrame* mFrame;

  /// The saved rotation of the frame
  Eigen::AngleAxisd mSavedRotation;
};

//==============================================================================
/// SimpleFrameShapeDnD is a version of SimpleFrameDnD that allows a specific
/// Shape within the SimpleFrame to be dragged and dropped (although it will
/// carry the entire SimpleFrame with it)
class SimpleFrameShapeDnD : public SimpleFrameDnD
{
public:

  /// Constructor
  SimpleFrameShapeDnD(Viewer* viewer, kido::dynamics::SimpleFrame* frame,
                      kido::dynamics::Shape* shape);

  /// Virtual destructor
  virtual ~SimpleFrameShapeDnD() = default;

  /// Get the Shape associated with this DnD
  kido::dynamics::Shape* getShape() const;

  // Documentation inherited
  virtual void update() override;

protected:

  // Documentation inherited
  virtual void handleDestructionNotification(
      const kido::common::Subject* subscription) override;

  /// Shape associated with this DnD
  kido::dynamics::Shape* mShape;
};

//==============================================================================
class InteractiveFrameDnD : public DragAndDrop
{
public:

  /// Constructor
  InteractiveFrameDnD(Viewer* viewer, osgKido::InteractiveFrame* frame);

  /// Virtual destructor
  virtual ~InteractiveFrameDnD() = default;

  /// Get the frame associated with this DnD
  InteractiveFrame* getFrame() const;

  // Documentation inherited
  virtual void update() override;

  // Documentation inherited
  virtual void move() override;

  // Documentation inherited
  virtual void saveState() override;

protected:

  /// Vector of DnD components that are united under this DnD
  std::vector<DragAndDrop*> mDnDs;

  /// Pointer to the interactive frame
  InteractiveFrame* mInteractiveFrame;
};

//==============================================================================
class BodyNodeDnD : public DragAndDrop
{
public:

  /// Constructor
  BodyNodeDnD(Viewer* viewer, kido::dynamics::BodyNode* bn,
              bool useExternalIK = true, bool useWholeBody = false);

  /// Virtual destructor
  virtual ~BodyNodeDnD() = default;

  /// Get the BodyNode associated with this DnD
  kido::dynamics::BodyNode* getBodyNode() const;

  // Documentation inherited
  virtual void move() override;

  // Documentation inherited
  virtual void saveState() override;

  // Documentation inherited
  virtual void release() override;

  /// Tell this DnD to use an external IK instead of the one embedded in the
  /// BodyNode. Using the one embedded in the BodyNode allows it to
  /// automatically be used in a WholeBodyIK, but using an external IK allows it
  /// to be automatically solved without instructing a WholeBodyIK to solve.
  void useExternalIK(bool external);

  /// Returns true if it is using an external IK
  bool isUsingExternalIK() const;

  /// Tell this DnD to use the whole body
  void useWholeBody(bool wholeBody);

  /// Returns true if this DnD is using the whole body
  bool isUsingWholeBody() const;

  /// Set the key that will preserve the orientation of the body
  void setPreserveOrientationModKey(osgGA::GUIEventAdapter::ModKeyMask modkey);

  /// Get the key that will preserve the orientation of the body
  osgGA::GUIEventAdapter::ModKeyMask getPreserveOrientationModKey() const;

  /// Set the key that will restrict which joints are used by the DnD
  void setJointRestrictionModKey(osgGA::GUIEventAdapter::ModKeyMask modkey);

  /// Get the key that will restrict which joints are used by the DnD
  osgGA::GUIEventAdapter::ModKeyMask getJointRestrictionModKey() const;

protected:

  /// The BodyNode associated with this DnD
  kido::dynamics::WeakBodyNodePtr mBodyNode;

  /// The IK module being used by this DnD
  kido::dynamics::InverseKinematicsPtr mIK;

  /// The offset of the pick from the BodyNode origin, expressed in global
  /// coordinates
  Eigen::Vector3d mSavedGlobalOffset;

  /// The offset of the pick from the BodyNode origin, expressed in local
  /// coordinates
  Eigen::Vector3d mSavedLocalOffset;

  /// The rotation of the BodyNode
  Eigen::AngleAxisd mSavedRotation;

  /// Whether to use an external IK
  bool mUseExternalIK;

  /// Whether to use the whole body
  bool mUseWholeBody;

  /// Key for preserving orientation
  osgGA::GUIEventAdapter::ModKeyMask mPreserveOrientationModKey;

  /// Key for restricting joint usage
  osgGA::GUIEventAdapter::ModKeyMask mJointRestrictionModKey;

  /// Currently unused, but this will change in the future
  size_t mAdditionalBodyNodes;
};

} // namespace osgKido


#endif // OSGKIDO_DRAGANDDROP_HPP