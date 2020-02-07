# 499

## 1/21

### different uses of const

#### 1

```C++
int foo(const std::string &s)
```

#### 2

```C++
class Foo {
    public:
        const std::string &s() const {
            return s_;
        }
    private:
        std::string s_;
}
```

- first one says that you can't modify what you get from `s()`
- second one says that `s()` won't change any member variables (the compiler actually checks this, ie, if you are calling a function )

#### 3

```C++
const double pi(3.14);
```

- an actual "constant"

#### 4

```C++
const expr
```

- kind of like macros but the compiler will optimize (not needed unless you want optimization)

### reference vs pointer

- functionally a reference is just syntactic sugar to let you treat a variable that actually is a pointer as not a pointer
- the style guide says: if you want to modify the variable, use a pointer, if not, pass by reference

### avoid long lists of arguments

- use a state object
- also try:

```C++
struct Foo {
    int x;
    double y;
}
Foo f{.x = 7, .y = 3.2}
```

### testing

- every PR should have unit tests for all public functions implemented
- no real way to unit test the CLI
- don't write unit tests for functions that talk over network

### logistics

- PRs every Tuesday & Friday at 2PM
- 50 to 300 lines long (no more than 500 lines hard limit)
- invite @barath and CPs as collaborators to the repo, named csci499_sajeevsa

## 1/28

### unit testing

- look into tmux
- for each [file], need [file].cc, [file].h, and [file]_test.cc
- typedef vs using: just use one, not very different
  - `using MyType = std::map<int, int>;`
  - `typedef std::map<int, int> MyType;`
- use `enum class` instead of pure `enum`
- comments for functions should be like API docs; don't want to talk about the implementation strategies
- use `auto` whenever possible, but make sure the variable names are sufficient to convey context
- use `ASSERT_EQ` if you need something to pass in order for the code to execute
- use braces `{}` to introduce new scope within a function, so that you can reuse variable names for verbose unit tests

### RAII

- resource acquisition is initialization
- basically turns dynamic memory allocation into static
- eg, `std::unique_ptr<Graph> g(new Graph());`
  - so when the pointer goes out of scope then the graph will be destructed automatically
  - cannot copy the `unique_ptr`
- eg, `std::shared_ptr<Graph> sg(new Graph());`
  - keeps a count of references and only frees the memory when there are 0 references left
- eg, `std::scoped_lock(m) // m is mutex`
  - unlocks when the scope is cleared

### other stuff

- builder class pattern: one class manages all instances of an object type

## 2/4

### office hours

- Barath W 9-10 SAL 214 (or lawn)
- Tianhang M 2-4 SAL
- Aliya R 2-4 SAL

### to do

- don't actually test the gRPC server/clients
  - have them call functions that are unit tested
- update `kvstore` to support multimap functionality
- figure out project directory structure
- start using `glog`
  - what would someone potentially need to know about the code I'm writing right now?
  - severity levels
  - `CHECK` macros similar to assertions except it always gets called
    - also there are special `CHECK_*`
