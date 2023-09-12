# Customer Archive

To install:

 1. Clone the repo:
$ git clone --recurse-submodules git@github.com:Ismayil92/customer_base.git

2. Enter the project's source directory:
$ cd customer_base

3. Run build commands:

    $ cmake -B ./build -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release -S .
    
    $ cmake --build ./build --config Release

4. Run the application:
$ ./build/CustomerService -f ./resource/data.csv

5. Test the application:

    $ cd build/test
    
    $ ./tester