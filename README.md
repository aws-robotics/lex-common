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

## Installation

### Building from Source
Create a ROS workspace

    mkdir ~/ros-workspace
    cd ~/ros-workspace

Create a source directory in the workspace created from above

    mkdir src

To build from source, clone the latest version from master branch and compile the package

- Clone the package into the source directory

        cd ~/ros-workspace/src
        git clone https://github.com/aws-robotics/utils-common.git
        git clone https://github.com/aws-robotics/utils-ros2.git
        git clone https://github.com/aws-robotics/lex-common.git

- Install dependencies

        sudo echo "yaml https://s3-us-west-2.amazonaws.com/rosdep/base.yaml" > /etc/ros/rosdep/sources.list.d/19-aws-sdk.list
        rosdep update
        sudo apt-get update
        rosdep install --from-paths src --ignore-src -r -y

- Build the packages
  - ROS: `cd ~/ros-workspace && colcon build`

- Configure ROS library Path

        source ~/ros-workspace/install/setup.bash

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

