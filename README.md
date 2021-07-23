## simple-redis-clone

### 簡介

一個簡單的 in-memory key-value 資料庫。

### Build the code

```shell
// generate makefiles
mkdir build
cd build
cmake ..
cd ..
// build
cmake --build build/
```

### Run the server

```shell
./build/src/simple-key-value-database-binary
```

### Run the client

```shell
./build/src/simple-key-value-database-client
```

### Run test

```shell
cd build
cmake -DCODE_COVERAGE=ON ..
make simple-key-value-database-test
./test/simple-key-value-database-test
```

