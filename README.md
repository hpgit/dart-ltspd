# Dart with Linear Time Stable PD

Adopt [Linear Time Stable PD](https://arpspoof.github.io/project/spd/spd.html) (SCA2020) to DART.

### Usage
If you don't need to get actual torques,

    skeleton->setSPDTarget(target_pose, k_p, k_d);
    world->step();

Or, if you need to get actual torques,

    Eigen::VectorXd torques = skeleton->getSPDForces(target_pose, k_p, k_d, world->getConstraintSolver());
    // do someting with torques
    ...

    skeleton->setForces(torques);
    world->step();

### Notes

* Recommended to call world->step() right after using setSPDTarget method. ( after using setSPDTarget method, some functions like mass matrix, coriolis force don't work properly. )
* Don't use setForces after using setSPDTarget in one time step.
* Performance increased up to 40% compared to the conventional SPD with same timestep.
* You can lower the time step to 1/30 ~ 1/60s. (1/100s ~ 1/300s recommended.)


# ![DART: Dynamic Animation and Robotics Toolkit](https://raw.githubusercontent.com/dartsim/dart/main/docs/dart_logo_377x107.jpg)

## CI Status

| Item              | Status                                                                                                                                 |
| ----------------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| Build Status      | [![CI Ubuntu](https://github.com/dartsim/dart/actions/workflows/ci_ubuntu.yml/badge.svg)](https://github.com/dartsim/dart/actions/workflows/ci_ubuntu.yml) [![CI macOS](https://github.com/dartsim/dart/actions/workflows/ci_macos.yml/badge.svg)](https://github.com/dartsim/dart/actions/workflows/ci_macos.yml) [![CI Windows](https://github.com/dartsim/dart/actions/workflows/ci_windows.yml/badge.svg)](https://github.com/dartsim/dart/actions/workflows/ci_windows.yml) |
| API Documentation | [![API Documentation](https://github.com/dartsim/dart/actions/workflows/api_doc.yml/badge.svg)](https://github.com/dartsim/dart/actions/workflows/api_doc.yml) |
| Coverage          | [![codecov](https://codecov.io/gh/dartsim/dart/branch/main/graph/badge.svg)](https://codecov.io/gh/dartsim/dart) |
| Static Analysis   | [![Codacy Badge](https://app.codacy.com/project/badge/Grade/2d95a9b951be4b73a71097670ec351e8)](https://www.codacy.com/gh/dartsim/dart/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=dartsim/dart&amp;utm_campaign=Badge_Grade) |

## Resources

Visit the [DART website](http://dartsim.github.io/) for more information

* [Gallery](http://dartsim.github.io/gallery.html)
* Installation
  * C++: [Ubuntu](http://dartsim.github.io/install_dart_on_ubuntu.html) | [macOS](http://dartsim.github.io/install_dart_on_mac.html) | [Archlinux](http://dartsim.github.io/install_dart_on_archlinux.html) | [FreeBSD](http://dartsim.github.io/install_dart_on_freebsd.html) | [Windows](http://dartsim.github.io/install_dart_on_windows.html)
  * Python: [Ubuntu](http://dartsim.github.io/install_dartpy_on_ubuntu.html) | [macOS](http://dartsim.github.io/install_dartpy_on_macos.html)
* [Tutorials (C++)](http://dartsim.github.io/tutorials_introduction.html)
* [API Documentation (C++)](https://dartsim.github.io/dart/)
* [Forum](https://dartsim.discourse.group/)
* Python bindings: [dartpy](https://github.com/dartsim/dart/tree/main/python), [pydart2](https://github.com/sehoonha/pydart2) (deprecated)
* OpenAI Gym with DART support: [gym-dart](https://github.com/dartsim/gym-dart) (dartpy based), [DartEnv](https://github.com/DartEnv/dart-env) (pydart2 based, deprecated)
* If you use DART in an academic publication, please consider citing [![DOI](https://joss.theoj.org/papers/10.21105/joss.00500/status.svg)](https://doi.org/10.21105/joss.00500)
