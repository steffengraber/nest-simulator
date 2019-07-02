#!/bin/bash

docker pull steffengraber/travis-nest:latest
docker run -it --rm -d --user nest --name travis-test-nest -v $(pwd):/home/nest/data steffengraber/travis-nest:latest


docker ps -a
docker container exec -it --user nest travis-test-nest sh /home/nest/data/extras/travis_tests.sh

