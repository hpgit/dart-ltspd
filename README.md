# Dart with Linear Time Stable PD

Linear Time Stable PD[https://arpspoof.github.io/project/spd/spd.html] (SCA2020) 를 Dart에 적용.

## 사용방법 및 유의사항 
* 기존에 skeleton->setForces(torques) 으로 사용하던 부분을 skeleton->setSPDTarget(target_pose, k_p, k_d) 로 사용.
* setSPDTarget 함수를 사용하고 나서 곧바로 world->step()함수를 호출하는 것을 권장. ( setSPDTarget 함수를 사용하고 나면 mass matrix, coriolis force 등을 구하는 함수에서 틀린 결과 출력. )
* 기존에 setForces함수로 사용하던 코드도 사용 가능.
* setForces 와 setSPDTarget 혼용도 가능하나, 한 step 안에서는 한 종류만 써야함. (e.g. setForces() => step() => setSPDTarget() => step() )
* 기존 SPD 사용할 때와 비교하여 30 ~ 40 % 정도의 속도 향상 효과.

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
