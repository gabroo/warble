# Warble

"Warble" is a command line interface that allows users to post Warbles (ie, Tweets), reply to specific Warbles, and read entire Warble threads, among other functions. Class project for [CSCI 499](https://raghavan.usc.edu/2020-spring-robust-software-design-and-implementation/) at USC.

## Setup

1. Setup a [Vagrant](https://app.vagrantup.com) VM with the [`ubuntu/bionic64`](https://app.vagrantup.com/ubuntu/boxes/bionic64) box.

2. Install [`bazel`](https://bazel.build).

3. Clone this repository:

  ```
  git clone https://github.com/gabroo/cs499_gabroo.git
  ```

## Build

Bazel will find all dependencies and make the necessary executables:

```
bazel build --config=all
```

## Test

Run all the tests with bazel:

```
bazel test --config=all
```

## Run

1. Start the key value store:

  ```
  ./bazel-bin/kvstore/server [--store <file>]
  ```
(Note: the store is run without bazel because otherwise the paths for the persistence feature become overly complicated.)

2. Start the FaaS server:

  ```
  bazel run --config=func
  ```

3. Warble!

  ```
   bazel run --config=warble -- [flags]
  ```
  
You must include one of the following flags, but not both:

  `--registeruser <username>` - registers the given username
  
  `--user <username>` - logs in as the given username

If the `--user` flag is specified, you must include one of the following actions:
  
  `--warble <warble text>` - creates a new warble with the given text

  `--reply <reply warble id>` - indicates that the new warble is a reply to the given id

  `--follow <username>` - starts following the given username

  `--read <warble id>` - reads the warble thread starting at the given id

  `--profile` - gets the user’s profile of following and followers
