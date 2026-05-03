# install base image
FROM ros:humble-ros-base

# create directory
WORKDIR /deployment_ws

# copy src
COPY src/ src/

# install dependencies
RUN apt-get update && \
    rosdep install --from-paths src --ignore-src -r -y

# build the workspace
RUN /bin/bash -c "source /opt/ros/humble/setup.bash && colcon build"

# run the node when container starts
CMD ["/bin/bash", "-c", \
    "source /opt/ros/humble/setup.bash && \
     source /deployment_ws/install/setup.bash && \
     ros2 run deployment_pkg battery_monitor"]