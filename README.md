# DDSCore
DDSCore is a ROS 2 Humble package that implements an abstraction layer to make ROS 2 communication with PX4 easier.

![image](assets/x500_pocho.png)
![image](assets/schema.png)

This proyect is still a WIP.

## Attention

This branch is for the use of multi-UAV Kubernetes applications through <a href="https://minikube.sigs.k8s.io/docs/" target="_blank" rel="noreferrer">Minikube</a>. If you wish to use the single-UAV version through Docker, please head to <a href="https://github.com/SDuSDi/DDSCore/tree/master" target="_blank" rel="noreferrer">here</a>.

## Dependencies

To use the code hosted on this repo, it is advised that you use <a href="https://www.docker.com/" target="_blank" rel="noreferrer">Docker</a>. To install Docker Engine, which is the advised part, you can find the instructions <a href="https://docs.docker.com/engine/install/ubuntu/" target="_blank" rel="noreferrer">here</a>.

```
# Add Docker's official GPG key:
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources: 
### IMPORTANT: If you use an Ubuntu derivative distro, you may need to use UBUNTU_CODENAME instead of VERSION_CODENAME
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update

# Install the Docker packages
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

# OPTIONAL Verify that the Docker Engine Installation is sucessful by running the `hello-world` image
sudo docker run hello-world
```

Optionally, you can set the docker commands to be used without the need for ```sudo``` by giving the user clearance.

```
# Create the `docker` group
sudo groupadd docker

# Add your user to the `docker` group
sudo usermod -aG docker $USER

# Log put and log back in or use the following command to activates changes to groups
newgrp docker

# OPTIONAL Re-verify that you can run `docker` commands without sudo
docker run hello-world
```

Another good addition if your computer has an Nvidia GPU is <a href="https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/latest/install-guide.html" target="_blank" rel="noreferrer">Nvidia Container Toolkit</a>. This allows the container made through Docker to use or improve the use of said GPU, but it is not required. If you do <b>NOT</b> use it, please remove ```--runtime=nvidia``` and ```--gpus all``` from the command ```docker run``` found below.

If you do and use <b>APT</b> commands for installation, please use the following commands.
```
# Configure the production repository
curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | sudo gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg \
  && curl -s -L https://nvidia.github.io/libnvidia-container/stable/deb/nvidia-container-toolkit.list | \
    sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
    sudo tee /etc/apt/sources.list.d/nvidia-container-toolkit.list

# Update the package list from the repository
sudo apt-get update

# Install the NVIDIA Container Toolkit packages
sudo apt-get install -y nvidia-container-toolkit

# Configure the container runtime by using the `nvidia-ctk` command
sudo nvidia-ctk runtime configure --runtime=docker

# Restart the Docker daemon
sudo systemctl restart docker
```

The use of Minikube is <b>REQUIRED</b> to work with this branch of the repository. I advise that you head to the Minikube installation guide that can be found <a href="https://minikube.sigs.k8s.io/docs/start/" target="_blank" rel="noreferrer">here</a>, since it will best suit your needs.

## Build

First, to use this repository, you have to clone it in you host computer. The following commands clones the repository in a nested folder called ```ros2_ws/ddscore```.

```
git clone -b kubernetes https://github.com/SDuSDi/DDSCore.git ros2_ws/ddscore
```

Next, to use the code present, you need to build the Docker image through the present Dockerfile. To do this, you need to build that image <b>inside</b> Minikube for it to be accesible from the Minikube cluster. To do this, you need to start Minikue and change the path where the Docker will be built.

```
minikube start
minikube docker-env
```

Now if you check the Docker images through terminal commands, you'll find a few Docker images that you may not recognize. Those are Minikube's own Docker images that it uses to work. Additionally, if Minikube is up, you'll find a container running that belongs to Minikube's internal processes. To build the repository's Docker image, please use the following command.

```
docker build -t local/ddscore:v1 ./ros2_ws/ddscore/.
```

This will take >10 minutes, so relax for a bit.

## Usage

Now, to begin using this repository, get Minikube up if it isnt already up with the following command.

```
minikube start
```

Now that Minikube is up, the next step is deploying some pods in the Minikube cluster. To do this, a deployment file is used, that specifies how the pods should be build and what should they contain. This way, if a pod ceases to exist, the deployment will generate another one according to the deployment file. The deployment file can be used through the following command.

```
kubectl apply -f ./ros2_ws/ddscore/deployment.yaml
```

To end the execution of Minikube and its cluster, the following commands are helpful.

```
# Deletes the deployment and its pods
kubectl delete deployment my-deployment

# Halts the execution of the Minikube master node
minikube stop

# Stop Minikube and deletes the cluster
minikube delete

# Remove everything about the Minikube cluster (use with caution)
minikube delete --all
```

## Work in progress

At the time of writing this, the control mode with attitude is still incomplete and being developed. The reason for it being incomplete is the complexity of the problems it presents. The control through attitude can be sumed up as control through quaternions and thrust. Since thrust is a vector of forces applied on the drone, the only force needed to keep the drone flying is the force in the Z axis. Using this, the movement of the drone on the horizontal plane must be made slightly tilting the drone and lightly raising the thurst to keep it at the same altitude and moving. Problems come from the need of calculating the angle needed to decompose the thrust to reach a certain speed on any of the horizontal movement axis. For this reason, this method of control is on standby. If anyone knows how to do it, please contact me.

## Contact

Brais Martínez -> bmartinez.ext@catec.aero 