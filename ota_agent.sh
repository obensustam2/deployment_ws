#!/bin/bash

IMAGE="ghcr.io/obensustam2/deployment_ws/battery-monitor"
CONTAINER_NAME="battery-monitor"
CHECK_INTERVAL=30

echo "OTA agent started - watching $IMAGE"

while true; do
    echo "Checking for new image..."

    # pull latest image from registry
    docker pull $IMAGE:latest

    # get the image ID from currently running container
    RUNNING_ID=$(docker inspect --format='{{.Image}}' $CONTAINER_NAME 2>/dev/null)

    # get the image ID of latest pulled image
    LATEST_ID=$(docker inspect --format='{{.Id}}' $IMAGE:latest)

    echo "Running ID: $RUNNING_ID"
    echo "Latest ID:  $LATEST_ID"

    if [ "$RUNNING_ID" != "$LATEST_ID" ]; then
        echo "New image detected — updating..."

        docker stop $CONTAINER_NAME 2>/dev/null
        docker rm $CONTAINER_NAME 2>/dev/null

        docker run -d \
            --name $CONTAINER_NAME \
            --restart unless-stopped \
            $IMAGE

        echo "Update complete — new version running"
    else
        echo "Already on latest — no update needed"
    fi

    sleep $CHECK_INTERVAL
done