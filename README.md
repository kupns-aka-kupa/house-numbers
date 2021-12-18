# house-numbers
pytorch

## Install dependencies
```shell
sudo apt-get install -y libpqxx-dev libboost-all-dev
```

## Run
```shell
docker run mnist 
-e CONNECTION_STRING=postgresql://postgres:postgres@localhost:5432/mnist
-v cmake-build-debug/_deps/pytorch-src/lib:/usr/local/pytorch/lib:ro cmake-build-debug:/app/build
```