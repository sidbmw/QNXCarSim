#/bin/bash

#  Simulation of regular driving followed by an accident where airbags are deployed.


./engine &

./brakes 100

./brakes 50

./throttle 20

./indicator l

./indicator l

./brakes 10

./throttle 0

./indicator r

./indicator l

./indicator r

./brakes 100

./brakes 100

./throttle 100

./throttle 100

./throttle 100

./throttle 100

./throttle 100

./steering 5

./steering 95

./steering -500

./steering 900

./airbags

./throttle 50

./engine_toggle

