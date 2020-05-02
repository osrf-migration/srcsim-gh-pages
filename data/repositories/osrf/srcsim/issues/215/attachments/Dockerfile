# Use an official Python runtime as a base image
#FROM python:2.7-slim
FROM ros:indigo-ros-base

# Set the working directory to /app
WORKDIR /app

COPY requirements.txt /app
COPY src_robotclient.py /app
COPY src_comms.py /app
COPY src_vision.py /app
COPY src_ihmc.py /app
COPY src_utils.py /app
COPY src_parser.py /app
COPY src_dbg.py /app
COPY src_planner.py /app
COPY src_planner_utils.py /app
COPY src_planner_task1.py /app
COPY src_planner_task3.py /app

RUN apt-get -y update
RUN apt-get -y install build-essential gfortran libatlas-base-dev python-pip python-dev
RUN pip install --upgrade pip

# ROS installation

# add ihmc messages
RUN apt-get update \
 && apt-get install -y \
    build-essential \
    python-catkin-tools \
    ros-indigo-catkin \
    ros-indigo-ihmc-msgs \
    ros-indigo-rosbag \
    ros-indigo-tf \
    ros-indigo-tf2 \
 && rm -rf /var/lib/apt/lists/*

RUN apt-get -y update
RUN  apt-get -y install wget
RUN  sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable trusty main" > /etc/apt/sources.list.d/gazebo-stable.list'
RUN  wget -O - http://packages.osrfoundation.org/gazebo.key | sudo apt-key add -
RUN sh -c 'echo "deb http://srcsim.gazebosim.org/src trusty main" \ > /etc/apt/sources.list.d/src-latest.list'
RUN wget -O - http://srcsim.gazebosim.org/src/src.key | sudo apt-key add -
RUN wget -O - https://bintray.com/user/downloadSubjectPublicKey?username=bintray | sudo apt-key add -

RUN apt-get -y update
RUN  apt-get -y install gazebo7
RUN  apt-get -y install srcsim
RUN  export IS_GAZEBO=true
RUN  export ROS_IP=127.0.0.1
RUN  chown -R $USER:$USER /opt/ros/indigo/share/ihmc_ros_java_adapter
RUN  mkdir -p ${HOME}/.ihmc; curl https://raw.githubusercontent.com/ihmcrobotics/ihmc_ros_core/0.8.0/ihmc_ros_common/configurations/IHMCNetworkParametersTemplate.ini > ${HOME}/.ihmc/IHMCNetworkParameters.ini

# clone srcsim
RUN mkdir -p /app/src
WORKDIR /app
RUN hg clone https://bitbucket.org/osrf/srcsim /app/src/srcsim

# build srcsim messages
RUN . /opt/ros/indigo/setup.sh \
  && catkin_make install
# && catkin config --cmake-args -DBUILD_MSGS_ONLY=True \
# && catkin config --install \
# && catkin build

RUN . /app/install/setup.sh

EXPOSE 8000
EXPOSE 8001
ENV ROS_MASTER_URI http://127.0.0.1:11311

#RUN rosdep init
#RUN rosdep update
#RUN echo "source /opt/ros/indigo/setup.bash" >> ~/.bashrc
#RUN . /opt/ros/indigo/setup.sh
# Install any needed packages specified in requirements.txt
RUN pip install -r requirements.txt

# opencv installation
ENV NUM_CORES 4

# Install OpenCV 3.0
RUN apt-get -y update
RUN apt-get -y install   unzip \
                       build-essential cmake git pkg-config libatlas-base-dev gfortran \
                       libjasper-dev libgtk2.0-dev libavcodec-dev libavformat-dev \
                       libswscale-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libv4l-dev
RUN pip install matplotlib

RUN wget https://github.com/Itseez/opencv/archive/3.2.0.zip -O opencv3.zip && \
    unzip -q opencv3.zip && mv ./opencv-3.2.0 ./opencv
RUN wget https://github.com/Itseez/opencv_contrib/archive/3.2.0.zip -O opencv_contrib3.zip && \
    unzip -q opencv_contrib3.zip && mv ./opencv_contrib-3.2.0 ./opencv_contrib
RUN mkdir ./opencv/build
WORKDIR ./opencv/build
RUN cmake -D CMAKE_BUILD_TYPE=RELEASE \
	-D BUILD_PYTHON_SUPPORT=ON \
	-D CMAKE_INSTALL_PREFIX=/usr/local \
	-D INSTALL_C_EXAMPLES=ON \
	-D INSTALL_PYTHON_EXAMPLES=ON \
	-D OPENCV_EXTRA_MODULES_PATH=/app/opencv_contrib/modules \
	-D BUILD_EXAMPLES=ON \
	-D BUILD_NEW_PYTHON_SUPPORT=ON \
	-D WITH_IPP=OFF \
	-D WITH_V4L=ON ..
RUN make -j$NUM_CORES
RUN make install
RUN ldconfig

#cv2_bridge
RUN apt-get -y install ros-indigo-cv-bridge

# Make port 80 available to the world outside this container
EXPOSE 80
EXPOSE 5000
EXPOSE 5001
EXPOSE 11311

# Define environment variable
ENV NAME World

WORKDIR /app

# Run app.py when the container launches
CMD ["python", "src_robotclient.py"]

