<h1 align="center">
  GenEnum
</h1>
  
<p align="center">
  Useful C++17 Boost Based Header Only Enum Generator
  <br/>
</p>

## Table Of Contents
* [About the Project](#about-the-project)
* [Getting Started](#getting-started)
  * [Installation](#installation)
* [Usage](#usage)
  * [Example](#example)
  * [Features](#features)
    * [getSize](#1-getsize)
    * [toString](#2-tostring)
    * [fromString](#3-fromstring)
    * [maxSourceStringLength](#4-maxsourcestringlength)
* [License](#license)
* [Authors](#authors)

## About The Project

Easy and fast way to generate enums in C++ code:

```C++
GENENUM(uint8_t, PlayerState, Idle, Wait, Run);
```

## Getting Started

### Installation

With boost linkage:
1. Download ```GenEnum.hpp``` file
2. Link boost preprocessor to your project

Or with cmake:
1. Clone this project
2. Link GenEnum target in cmake
```C++
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/third_party/GenEnum")
target_link_libraries(${PROJECT_NAME} PUBLIC GenEnum)
```

## Usage

### Example
Here the way to use GENENUM
```C++
GENENUM(uint8_t, PlayerState, Idle, Wait, Run);

PlayerState state = PlayerStates::Idle;
if (state == PlayerStates::Wait)
{
    std::cout << "Current Player State is Wait" << '\n';
}
```

### Features
All functions have ```constexpr``` specifier so you can call this functions on ```compile-time``` context like this:

```C++
std::array<uint8_t, PlayerStates::getSize()> states;
```

#### 1. getSize
Get count of enum elements
```C++
GENENUM(uint8_t, PlayerState, Idle, Wait, Run);
std::cout << "Count of player states " << PlayerStates::getSize() << '\n';
// Output: Count of player states 3
```

#### 2. toString
Easy way to get ```std::string_view``` from genenum value
```C++
std::string_view str = PlayerStates::toString(PlayerStates::Idle);
std::cout << "Current Player State is " << str << '\n';
// Output: Current Player State is Idle
```

#### 3. fromString
Get enum value from string representation
```C++
PlayerState state;
std::string_view str = "Idle";
if (PlayerStates::fromString(str, state))
{
    std::cout << "Successfully got enum from string" << '\n';
}
```

#### 4. maxSourceStringLength
Get length of longest enum-element
```C++
GENENUM(uint8_t, LoggerSource, Core, DeviceController);
std::cout << "Max length in LoggerSource enum " << LoggerSources::maxSourceStringLength() << "\n";
// Output: Max length in LoggerSource enum 16
```

## License

Distributed under the MIT License. See [LICENSE](https://github.com/brano-san/GenEnum/blob/master/LICENSE.txt) for more information.

## Authors

* **Andrey** - *C++ Developer* - [brano-san](https://github.com/brano-san) - *All work*
