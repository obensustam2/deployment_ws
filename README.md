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
# list running docker containers (ps = process status)
docker ps

# run docker container (-it, bash = interactive terminal)
docker run -it <image name> bash

# stop all running containers
docker stop $(docker ps -q)

# remove docker container (rm = remove)
docker rm <container name>

# remove all docker containers
docker container prune
```

