# warble

## how to build
1. setup a Vagrant VM with the [`ubuntu/bionic64`](https://app.vagrantup.com/ubuntu/boxes/bionic64) box
2. install [bazel](https://bazel.build)
3. clone this repository:
```
git clone https://github.com/gabroo/cs499_gabroo.git
```
4. build the binaries 
```
bazel build kvstore:kvstore_server
```
5. run the binaries
```
./bazel-bin/kvstore/kvstore_server
```
