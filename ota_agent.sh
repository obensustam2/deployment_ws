#!/bin/bash

IMAGE="ghcr.io/obensustam2/deployment_ws/battery-monitor"
CONTAINER_NAME="battery-monitor"
CHECK_INTERVAL=30
HEALTH_WAIT=10

echo "OTA agent started - watching $IMAGE"

check_health() {
    echo "Waiting $HEALTH_WAIT seconds for node to start..."
    sleep $HEALTH_WAIT

    TOPIC=$(docker exec $CONTAINER_NAME \
        /bin/bash -c "source /opt/ros/humble/setup.bash && ros2 topic list 2>/dev/null" \
        | grep "battery_state_fail")

    echo "Topic found: $TOPIC"

    if [ -n "$TOPIC" ]; then
        echo "Health check PASSED ✅ — topic is publishing"
        return 0
    else
        echo "Health check FAILED ❌ — topic not found"
        return 1
    fi
}

while true; do
    echo "Checking for new image..."

    docker pull $IMAGE:latest

    RUNNING_ID=$(docker inspect --format='{{.Image}}' $CONTAINER_NAME 2>/dev/null)
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
            $IMAGE:latest

        if check_health; then
            echo "Update complete — new version running ✅"
        else
            echo "Update failed — needs rollback ⚠️"
        fi
    else
        echo "Already on latest — no update needed"
    fi

    sleep $CHECK_INTERVAL
done