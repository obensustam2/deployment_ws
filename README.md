## Docker CLI
### Docker Image
```sh
# list docker images
docker images

# build docker image (-t = tag, . = dockerfile directory)
docker build -t <image_name> .

# remove docker image  (rmi = remove image)
docker rmi <image_name>

# pull docker image
docker pull <image_url>
```

### Docker Container
```sh
# list all docker containers (ps = process status, -a = all)
docker ps -a

# run docker container with specific name first time (-it, bash = interactive terminal)
docker run -it --name <container_name> <image name> bash

# run docker container
docker run -it <container_name> bash

# stop all running containers
docker stop <container_name>

# remove docker container (rm = remove)
docker rm <container name>

# remove all docker containers
docker container prune

# access running container with terminal
docker exec -it <container name> bash
```


## Ansible
### Installation
```sh
pip install ansible
sudo apt install openssh-server
```

### Execution
```sh
ansible-playbook -i inventory.ini <desired_playbook>
```


## Prometheus
```sh
ros2 run deployment_pkg battery_state_monitor

python3 src/deployment_pkg/scripts/battery_exporter.py

docker run -d \
  --name prometheus \
  --add-host=host.docker.internal:host-gateway \
  -p 9091:9090 \
  -v ~/Projects/deployment_ws/prometheus/prometheus.yml:/etc/prometheus/prometheus.yml \
  prom/prometheus
```
