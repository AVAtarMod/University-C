name=$(uuidgen)
force_file=""
destFilename="serv_client"
if [[ $1 != "" ]]; then
    force_file=$1
fi
printf "\e[1;33;1m[I] Starting container\e[0m\n"
docker run --tty -d=true --name $name -v networks_server-client:/data -v $(pwd)/files:/data-updated opensuse/tumbleweed:latest

if [[ $? != 0 ]]; then
    printf "[E] Cannot start container\n"
    exit $?
fi

printf "\e[1;33m[I] Build application\e[0m\n"
make dev && make

filename="realease.app"
printf "\e[1;33m[I] Move build to container\e[0m\n"
if [[ $? != 0 && $force_file != "" ]]; then
    cp $force_file files/$destFilename
    filename="$force_file"
else
    cp realease.app files/$destFilename
fi
container_id=$(docker ps -a 2>&1 | grep $name | cut -d' ' -f1)

printf "\e[1;33m[I] Move build inside container to volume\e[0m\n"
docker exec $container_id bash -c "cp /data-updated/* /data/"

printf "\e[1;33m[I] Stopping container\e[0m "
docker stop -t 5 $name
if [[ $? != 0 ]]; then
    printf "[E] Cannot stop container\n"
else
    printf "\e[1;32m[I] Stopped successfuly\e[0m\n"
fi

printf "\e[1;33m[I] Removing container\e[0m "
docker container rm $name
if [[ $? != 0 ]]; then
    printf "[E] Cannot remove container\n"
else
    printf "\e[1;32m[I] Removed successfuly\e[0m\n"
fi

printf "\e[1;33m[I] Run test\e[0m "
docker run --tty -d=true --name $name -v networks_server-client:/usr/local/bin opensuse/tumbleweed:latest
container_id=$(docker ps -a 2>&1 | grep $name | cut -d' ' -f1)
out=$(docker exec $container_id bash -c "ls -la /usr/local/bin" 2>&1)
echo "Dest filename=${destFilename}"
printf "$out\n" > tmp
grep $destFilename tmp
if [[ $? != 0 ]]; then
    printf "[E] Test failed\n"
else
    printf "\e[1;32m[I] Test completed successfuly\e[0m\n"
fi
rm tmp
docker stop -t 5 $name
docker container rm $name
