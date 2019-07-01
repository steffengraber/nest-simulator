#!/bin/bash
docker container exec -it --env "xMPI=1" --env "xPYTHON=0" --user nest travis-test-nest sh /home/nest/data/extras/travis_tests.sh
docker container exec -it --env "xMPI=0" --env "xPYTHON=1" --user nest travis-test-nest sh  /home/nest/data/extras/travis_tests.sh
docker ps -a