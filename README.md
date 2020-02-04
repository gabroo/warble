# warble

## how to build
1. setup a Vagrant VM with the [`ubuntu/bionic64`](https://app.vagrantup.com/ubuntu/boxes/bionic64) box
2. install [protobuf](https://github.com/protocolbuffers/protobuf/tree/master/src) and [gRPC](https://github.com/grpc/grpc/blob/master/BUILDING.md)
3. clone this repository:
```
git clone https://github.com/gabroo/cs499_gabroo.git
```
4. make a `build` directory:
```
mkdir build && cd build
```
5. build the binaries:
```
cmake ..
make
```

## how to run
tbd
