#!/bin/bash

# This script is an example of all the functionalities working together.

VM_IP=172.16.162.2

echo "Assuming qnxenv-sdp.sh is already sourced and being run with qemu support on the host machine."

make
# Assuming qemu is installed and can be run on the host. May work on Windows with --type='vmware' or --type='virtualbox'. 
# This has not been tested to run on Windows.
rm -rf local output
mkqnximage --data-size=500 --type=qemu --arch=x86_64 --toybox='yes' --force --run &
sleep 30
ssh-copy-id root@$VM_IP
scp -r engine airbags throttle indicator brakes demo.sh root@$VM_IP:/tmp
ssh root@$VM_IP "cd /tmp/ && chmod +x demo.sh && ./demo.sh"

