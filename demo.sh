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

./airbags
