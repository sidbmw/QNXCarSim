#/bin/bash

#  Simulation of regular driving followed by an accident where airbags are deployed.


./engine &

sleep 1
./brakes 100

sleep 1
./brakes 50

sleep 1
./throttle 20

sleep 1
./indicator l

sleep 1
./indicator l

sleep 1
./brakes 10

sleep 1
./throttle 0

sleep 1
./indicator r

sleep 1
./indicator l

sleep 1
./indicator r

sleep 1
./brakes 100

sleep 1
./brakes 100

sleep 1
./throttle 100

sleep 1
./throttle 100

sleep 1
./throttle 100

sleep 1
./throttle 100

sleep 1
./throttle 100

sleep 1
./steering 5

sleep 1
./steering 95

sleep 1
./steering -500

sleep 1
./steering 900

sleep 1
./airbags

sleep 1
./throttle 50

sleep 1
./engine_toggle

