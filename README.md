# Assignment 01 for COMP 4300 Course

--------------------------------------
## About the course
[Video Lectures on YouTube](https://www.youtube.com/playlist?list=PL_xRyXins848nDj2v-TJYahzvs-XW9sVV)
COMP 4300 - C++ Game Programming (2022-09) by Dave Churchill

## About the assignment

For more information about assignment itsled, please read the 
[ASSIGNMENT.md](ASSIGNMENT01.md) file.
I made this assignment not in one file but split the code to different files.
There was a code, it is in `initial_code.cpp` file, given by Dave as an example.
It took me some time to get acquainted with SMFL library and ImGui as well to
be able to finish the assignment.


## How to compile and run

```bash
mkdir mybuild && cd mybuild
cmake ..
make
cp -r ../assets ../.. # I should think of a better way with paths
```

## Dev Notes
I'm using CLion as my IDE, and I endeavor to adhere to its provided guidelines,
which aid with the code style and project structure. Thus, the code style and
related aspects might not strictly adhere to established standards, if any
exist (😅).
Nonetheless, I consult authoritative pillars such as the
([C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines.html))
and
[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
to ensure that the code remains readable and consistent.


### Guide style
* Each row of text in your code should be at most 80 characters long;
* Use a .cpp suffix for code files and .h for interface files;
  [NL.27](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines.html#Rl-file-suffix)
* [Names and order of includes](https://google.github.io/styleguide/cppguide.html#Names_and_Order_of_Includes)
  Related header, C system headers, C++ standard library headers, other headers;
* The names of all types — classes, structs, type aliases, enums, and type
  template parameters start with a capital letter and have a capital letter
  for each new word, with no underscores: MyExcitingClass, MyExcitingEnum;
* The names of variables (including function parameters) and data members are
  snake_case. E.g.: a_struct_data_member, a_class_data_member, a_variable;
* m_ prefix is used for private member variables of classes, for public vars
  you should use just a snake_case rule;
* Functions and methods should also use snake_case;
* Note! While I prefer using all uppercase for constants, both guides recommend
  using it for macros. Therefore, I'll adhere to the
  [Google rule](https://google.github.io/styleguide/cppguide.html#Constant_Names)
  use `const int k_days_in_a_week = 7`. It's important for me to clearly indicate
  that it is a constant.
