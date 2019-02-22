## Lex Common

ROS packages for facilitating the use of AWS cloud services.

## License

This library is licensed under the Apache 2.0 License. 
=======
# lex_common


## Overview

### License
The source code is released under an [Apache 2.0].

**Author**: AWS RoboMaker<br/>
**Affiliation**: [Amazon Web Services (AWS)]<br/>
**Maintainer**: AWS RoboMaker, ros-contributions@amazon.com

### Supported ROS Distributions
- Kinetic
- Lunar
- Crystal

### Build status

@TODO: build status

## Installation

### Building from Source

To build from source you'll need to create a new workspace, clone and checkout the latest release branch of this repository, install all the dependencies, and compile. If you need the latest development features you can clone from the `master` branch instead of the latest release branch. While we guarantee the release branches are stable, __the `master` should be considered to have an unstable build__ due to ongoing development. 

- Create a ROS workspace and a source directory

    mkdir -p ~/ros-workspace/src

- Clone the package into the source directory . 

_Note: Replace __`{MAJOR.VERSION}`__ below with the latest major version number to get the latest release branch._

        cd ~/ros-workspace/src
        git clone https://github.com/aws-robotics/lex-common.git -b release-v{MAJOR.VERSION}

- Install dependencies

        cd ~/ros-workspace 
        sudo apt-get update && rosdep update
        rosdep install --from-paths src --ignore-src -r -y
        
_Note: If building the master branch instead of a release branch you may need to also checkout and build the master branches of the packages this package depends on._

- Build the packages

        cd ~/ros-workspace && colcon build

- Configure ROS library Path

        source ~/ros-workspace/install/setup.bash


- Build and run the unit tests

        colcon build --packages-select lex_common --cmake-target tests
        colcon test --packages-select lex_common && colcon test-result --all


## Bugs & Feature Requests
Please contact the team directly if you would like to request a feature.

Please report bugs in [Issue Tracker].


[Amazon Web Services (AWS)]: https://aws.amazon.com/
[Apache 2.0]: https://aws.amazon.com/apache-2-0/
[AWS Configuration and Credential Files]: https://docs.aws.amazon.com/cli/latest/userguide/cli-config-files.html
[aws-sdk-c++]: https://github.com/aws/aws-sdk-cpp
[Getting Started with Amazon Lex]: https://docs.aws.amazon.com/lex/latest/dg/getting-started.html
[Issue Tracker]: TODO
[ROS]: http://www.ros.org
[sample app]: TODO

