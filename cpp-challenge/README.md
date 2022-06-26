## Requirement
You'll need:

* "CMake >= 2.8".

## Build
To build the C++ project, as usual:
```sh
mkdir build
cd build
cmake ../
cmake --build .
```


## Perl Test
To test the app with perl
```sh
cd build
cd test
bash test.sh 
```

## File

buggy/
-- source code

test/
-- data_generator.pl : perl file to generate input and output test file
-- compare.pl: check the test result with pre-defined answer
-- input_data.txt: input_data random genertaed by data_generator 
-- output_data.txt: pre-defined answer genertaed by data_generator 
-- test.sh: perl test sh script


