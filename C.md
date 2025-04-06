# C Programming Tutorial 

This tutorial covers the fundamentals of the C programming language, a powerful and widely-used language for system and application development. We'll start with basic concepts and gradually move to more advanced topics, ensuring a comprehensive understanding.

## Table of Contents

1. [Getting Started](#1-getting-started)
2. [Comments](#2-comments)
3. [Basic Concepts](#3-basic-concepts)
   - [3.1 Data Types](#31-data-types)
   - [3.2 Naming Conventions in Programming](#32-naming-conventions-in-programming)
   - [3.3 Variables](#33-variables)
   - [3.4 Storage Classes](#34-storage-classes)
   - [3.5 Constants](#35-constants)
4. [Input and Output](#4-input-and-output)
   - [4.1 Output Formatting](#41-output-formatting)
   - [4.2 User Input](#42-user-input)
5. [Operators](#5-operators)
   - [5.1 Arithmetic Operators](#51-arithmetic-operators)
   - [5.2 Assignment Operators](#52-assignment-operators)
   - [5.3 Comparison Operators](#53-comparison-operators)
   - [5.4 Logical Operators](#54-logical-operators)
   - [5.5 Bitwise Operators](#55-bitwise-operators)
6. [Control Flow](#6-control-flow)
   - [6.1 Conditions](#61-conditions)
   - [6.2 Ternary Operator](#62-ternary-operator)
   - [6.3 Switch](#63-switch)
   - [6.4 Loops](#64-loops)
7. [Arrays and Strings](#7-arrays-and-strings)
   - [7.1 Arrays](#71-arrays)
   - [7.2 Strings](#72-strings)
8. [Functions](#8-functions)
   - [8.1 Declaration and Definition](#81-declaration-and-definition)
   - [8.2 Parameters](#82-parameters)
   - [8.3 Return Values](#83-return-values)
   - [8.4 Recursion](#84-recursion)
9. [Pointers](#9-pointers)
   - [9.1 Memory Address](#91-memory-address)
   - [9.2 Creating Pointers](#92-creating-pointers)
10. [Structures and Enums](#10-structures-and-enums)
    - [10.1 Structures](#101-structures)
    - [10.2 Enums](#102-enums)
11. [C Preprocessor](#11-c-preprocessor)
    - [11.1 Directives](#111-directives)
    - [11.2 Predefined Macros](#112-predefined-macros)
    - [11.3 Macro Continuation](#113-macro-continuation)
    - [11.4 String Concatenation](#114-string-concatenation)
    - [11.5 Token Pasting](#115-token-pasting)
    - [11.6 defined() Operator](#116-defined-operator)
    - [11.7 Parameterized Macros](#117-parameterized-macros)
12. [File Handling](#12-file-handling)
    - [12.1 File Functions](#121-file-functions)
    - [12.2 File Modes](#122-file-modes)
    - [12.3 Opening a File](#123-opening-a-file)
    - [12.4 Writing with fprintf](#124-writing-with-fprintf)
    - [12.5 Reading with fscanf](#125-reading-with-fscanf)
    - [12.6 Writing with fputc](#126-writing-with-fputc)
    - [12.7 Reading with fgetc](#127-reading-with-fgetc)
    - [12.8 Writing with fputs](#128-writing-with-fputs)
    - [12.9 Reading with fgets](#129-reading-with-fgets)
    - [12.10 Moving Pointer with fseek](#1210-moving-pointer-with-fseek)
    - [12.11 Resetting Pointer with rewind](#1211-resetting-pointer-with-rewind)
    - [12.12 Getting Position with ftell](#1212-getting-position-with-ftell)
13. [Mathematical Functions](#13-mathematical-functions)
14. [The `<string.h>` Library](#14-the-stringh-library)
    - [14.1 Including the Library](#141-including-the-library)
    - [14.2 Common `<string.h>` Functions](#142-common-stringh-functions)
    - [14.3 Best Practices](#143-best-practices)
    - [14.4 Example Program](#144-example-program)
15. [Creating Library Files](#15-creating-library-files)
    - [15.1 Overview of Libraries](#151-overview-of-libraries)
    - [15.2 Creating a Static Library](#152-creating-a-static-library)
    - [15.3 Creating a Dynamic Library](#153-creating-a-dynamic-library)
    - [15.4 Key Differences Between Static and Dynamic Libraries](#154-key-differences-between-static-and-dynamic-libraries)
    - [15.5 Best Practices](#155-best-practices)
    - [15.6 Example with Error Handling](#156-example-with-error-handling)
16. [Comprehensive Example](#16-comprehensive-example)
---

## 1. Getting Started

C is a structured programming language known for its efficiency and control. Let's begin by writing and running a simple program.

### First Program: Hello World(`hello.c`)
```c
#include <stdio.h>

int main(void) 
{
  printf("Hello World!\n");
  return 0;
}
```

- **Compile** the hello.c file with gcc:

```bash
$ gcc hello.c -o hello
```

- **Run** the compiled binary:

```bash
$ ./hello
```

- **Output**: Hello World!

This program introduces the basic structure of a C program, including the main function and the `printf`function for output.

------

## 2. Comments

Comments explain code and are ignored by the compiler. They are essential for making code readable and maintainable, especially as programs grow more complex.

### Example

```c
// This is a comment
printf("Hello World!"); // Can comment anywhere

/* 
  Multi-line comment, print Hello World!
  to the screen, it's awesome. 
*/
```

------

## 3. Basic Concepts

Before writing complex programs, we need to understand the building blocks of C: data types, variables, and constants.

### 3.1 Data Types

C provides various data types to store different kinds of values. Here are the basic ones:

#### Basic Data Types Table

| Type               | Size         | Range                          | Description                             |
| ------------------ | ------------ | ------------------------------ | --------------------------------------- |
| `char              `| 1 byte       | −128 ~ 127                     | Single character/ASCII/Smallest Integer |
| `signed char       `| 1 byte       | −128 ~ 127                     | -                                       |
| `unsigned char     `| 1 byte       | 0 ~ 255                        | -                                       |
| `int               `| 2 to 4 bytes | −32,768 ~ 32,767               | Integer                                 |
| `signed int        `| 2 bytes      | −32,768 ~ 32,767               | -                                       |
| `unsigned int      `| 2 bytes      | 0 ~ 65,535                     | -                                       |
| `short int         `| 2 bytes      | −32,768 ~ 32,767               | -                                       |
| `signed short int  `| 2 bytes      | −32,768 ~ 32,767               | -                                       |
| `unsigned short int`| 2 bytes      | 0 ~ 65,535                     | -                                       |
| `long int          `| 4 bytes      | -2,147,483,648 ~ 2,147,483,647 | -                                       |
| `signed long int   `| 4 bytes      | -2,147,483,648 ~ 2,147,483,647 | -                                       |
| `unsigned long int `| 4 bytes      | 0 ~ 4,294,967,295              | -                                       |
| `float             `| 4 bytes      | 3.4E-38 ~ 3.4E+38              | Single-precision float                  |
| `double            `| 8 bytes      | 1.7E-308 ~ 1.7E+308            | Double-precision float                  |
| `long double       `| 10 bytes     | 3.4E-4932 ~ 1.1E+4932          | High-precision float                    |

#### Example: Using Data Types

```c
int my_num = 5;           // Integer
float my_float_num = 5.99;// Floating point number
char my_letter = 'D';     // Character
double my_double = 3.2325467; // High precision float

printf("%d\n", my_num);
printf("%f\n", my_float_num);
printf("%c\n", my_letter);
printf("%lf\n", my_double);
```

### 3.2 Naming Conventions in Programming

When naming variables in coding, we use **naming conventions** to keep our code readable and consistent. Here’s a quick guide to 11 popular styles!

#### 1. Pascal Case

- **Format**: Capitalize every word, no spaces (e.g., PascalCase)
- **Use**: Class names in Java, C# (e.g., UserProfile)

#### 2. Camel Case

- **Format**: First word lowercase, others capitalized (e.g., camelCase)
- **Use**: Variables in JavaScript, Java (e.g., userName)

#### 3. `Snake Case (Preferred)`

- **Format**: Lowercase, words separated by underscores (e.g., snake_case)
- **Use**: Variables in Python, C(e.g., user_name)

#### 4. Kebab Case

- **Format**: Lowercase, words separated by hyphens (e.g., kebab-case)
- **Use**: CSS class names, URLs (e.g., my-class) *Note*: Not valid for variables in most languages.

#### 5. Flat Case

- **Format**: All lowercase, no separators (e.g., flatcase)
- **Use**: Simple variable names (e.g., username)

#### 6. Upper Flat Case

- **Format**: All uppercase, no separators (e.g., UPPERFLATCASE)
- **Use**: Rarely used, sometimes for constants in older code.

#### 7. Pascal Snake Case

- **Format**: Pascal Case with underscores (e.g., Pascal_Snake_Case)
- **Use**: Rare, sometimes in specific frameworks.

#### 8. Camel Snake Case

- **Format**: Camel Case with underscores (e.g., camel_Snake_Case)
- **Use**: Uncommon, but seen in mixed-style projects.

#### 9. `Screaming Snake Case (Preferred)`

- **Format**: All uppercase, underscores between words (e.g., SCREAMING_SNAKE_CASE)
- **Use**: Constants in Python, C (e.g., MAX_LENGTH)

#### 10. Train Case

- **Format**: Capitalized words, hyphens between (e.g., Train-Case)
- **Use**: Rare, sometimes in documentation or file names.

#### 11. Cobol Case

- **Format**: All uppercase, hyphens between words (e.g., COBOL-CASE)
- **Use**: Legacy COBOL programming, not common today.

### 3.3 Variables

Variables store data in memory and must be declared with a type.

#### Example: Declaring and Using Variables

```c
char my_letter = 'M';  // Character
char my_number = 20;   // Small integer

int first_num = 15;

int second_num;        // Declare, then assign
second_num = 15;

int third_num = 15;    // Assign 15
third_num = 10;        // Reassign to 10

float my_float = 5.99; // Floating point number
double my_double = 4545.6789;

int x = 5;
int y = 6;
int sum = x + y;       // Add variables

// Declare multiple variables
int a = 5, b = 6, z = 50;

// Better way to declare multiple variables
int p = 5;
int q = 6;
int r = 50;

bool is_male = true;
bool is_girl = false;
```

### 3.4 Storage Classes

Storage classes in C define the scope, lifetime, and storage location of variables. There are five storage class specifiers: `auto`, `register`, `static`, `extern`, and `volatile`. Each serves a specific purpose in controlling how variables behave in a program.

##### 1. `auto`

- **Description**: The default storage class for local variables within a function or block. It indicates that the variable is automatically allocated and deallocated when the block is entered and exited.

- **Scope**: Local to the block where it’s defined.

- **Lifetime**: Exists only during the execution of the block.

- **Default Initial Value**: Uninitialized (garbage value).

- Example:

  ```c
  void my_function() 
  {
      auto int x = 10; // 'auto' is optional, as it's the default
      printf("x = %d\n", x);
  }
  
  int main() 
  {
      my_function(); // Output: x = 10
      // x is not accessible here 
      return 0;
  }
  ```

- **Note**: Rarely used explicitly since local variables are auto by default.

##### 2. `register`

- **Description**: Suggests to the compiler that the variable should be stored in a CPU register for faster access, rather than in RAM. However, the compiler may ignore this hint if registers are unavailable.

- **Scope**: Local to the block where it’s defined.

- **Lifetime**: Exists only during the execution of the block.

- **Default Initial Value**: Uninitialized (garbage value).

- **Restrictions**: Cannot take the address of a register variable (no & operator).

- Example:

  ```c
  int main() 
  {
      register int counter = 0;
      for (counter = 0; counter < 5; counter++) 
      {
          printf("%d\n", counter);
      }
      // printf("%p", &counter); // Error: address of register variable not allowed
      return 0;
  }
  ```

  

- **Use Case**: Useful in performance-critical code, like tight loops.

##### 3. `static`

- **Description**: Preserves the variable’s value between function calls and changes its scope/lifetime depending on where it’s declared. A static variable is initialized only once.

- Scope:

  - Local (inside a function): Limited to the function.
  - Global (outside a function): Limited to the file (internal linkage).
  
- **Lifetime**: Exists for the entire program duration.

- **Default Initial Value**: Zero if uninitialized.

- Example (Local Static):

  ```c
  void counter() 
  {
      static int count = 0; // Initialized once, retains value
      count++;
      printf("Count: %d\n", count);
  }
  
  int main() 
  {
      counter(); // Output: Count: 1
      counter(); // Output: Count: 2
      counter(); // Output: Count: 3
      return 0;
  }
  ```

- Example (Global Static):

  ```c
  static int global_count = 100; // Only accessible in this file
  
  int main() 
  {
      printf("Global count: %d\n", global_count); // Output: 100
      return 0;
  }
  ```

- **Use Case**: Counters, state preservation across function calls.

##### 4. `extern`

- **Description**: Declares a variable that is defined elsewhere (in another file or later in the same file). It extends the variable’s visibility across files.

- **Scope**: Global, accessible across files when linked.

- **Lifetime**: Exists for the entire program duration.

- **Default Initial Value**: Zero if uninitialized (but must be defined somewhere).

- Example:

  ```c
  // file1.c
  int global_var = 50; // Definition
  ```

  ```c
  // file2.c
  extern int global_var; // Declaration
  
  int main() 
  {
      printf("Global var: %d\n", global_var); // Output: 50
      return 0;
  }
  ```

- **Use Case**: Sharing variables across multiple source files.

##### 5. `volatile`

- **Description**: Tells the compiler that the variable’s value may change unexpectedly (e.g., by hardware or another thread), preventing optimization that assumes it’s stable.

- **Scope**: Depends on where it’s declared (local or global).

- **Lifetime**: Depends on where it’s declared (block or program duration).

- **Default Initial Value**: Uninitialized (garbage value).

  Example:

  ```c
  int main() 
  {
      volatile int flag = 0;
      while (flag == 0) 
      {
          // Wait for hardware to set flag
          printf("Waiting...\n");
      }
      printf("Flag changed!\n");
      return 0;
  }
  ```

- **Use Case**: Embedded systems, multi-threaded programs, hardware registers.

#### Summary of Storage Classes

| Storage Class | Scope      | Lifetime         | Default Value     | Storage Location           |
| ------------- | ---------- | ---------------- | ----------------- | -------------------------- |
| `auto          `| Block      | Block duration   | Garbage           | Stack                      |
| `register      `| Block      | Block duration   | Garbage           | CPU Register (if possible) |
| `static        `| Block/File | Program duration | Zero              | Data segment               |
| `extern        `| Global     | Program duration | Zero (if defined) | Data segment               |
| `volatile      `| Depends    | Depends          | Garbage           | Depends                    |

#### Notes

- Storage classes cannot be combined arbitrarily (e.g., static and extern together are invalid in the same declaration).
- Use volatile with caution, as it affects compiler optimizations.

### 3.5 Constants

Constants are fixed values that cannot be changed during execution.

#### Example: Defining Constants

```c
const int MINUTES_PER_HOUR = 60;
const float PI = 3.14;

#define PI 3.14
```

#### Best Practices

```c
const int BIRTHYEAR = 1980;

#define BIRTHYEAR 1980
```

------

## 4. Input and Output

Interacting with users requires printing data to the screen and reading input.

### 4.1 Output Formatting

The `printf` function displays data with format specifiers.

#### Basic Format Specifiers

| Specifier | Description                   |
| --------- | ----------------------------- |
| `%d` or `%i  `| Integer                       |
| `%f        `| Float (single-precision)      |
| `%lf       `| Double (high-precision float) |
| `%c        `| Character                     |
| `%s        `| String                        |

#### Octal, Decimal, Hexadecimal Specifiers

| Base        | Short     | Normal  | Long      |
| ----------- | --------- | ------- | --------- |
| Octal       | `%ho       `|` %o      `|` %lo       `|
| Decimal     | `%hd       `|` %d      `|` %ld       `|
| Hexadecimal | `%hx / %hX `|` %x` / `%X `|` %lx` / `%lX `|

#### Example: Printing Text

```c
printf("I am learning C.");

int test_integer = 5;
printf("Number = %d", test_integer);

float f = 5.99;
printf("Value = %f", f);

float g = 5.99;
printf("Value = %.2f", g); // Two digits after decimal

short a = 0b1010110; // Binary
int b = 02713;       // Octal
long c = 0x1DAB83;   // Hexadecimal

// Output in octal
printf("a=%ho, b=%o, c=%lo\n", a, b, c);
// Output: a=126, b=2713, c=7325603

// Output in decimal
printf("a=%hd, b=%d, c=%ld\n", a, b, c);
// Output: a=86, b=1483, c=1944451

// Output in hexadecimal (lowercase)
printf("a=%hx, b=%x, c=%lx\n", a, b, c);
// Output: a=56, b=5cb, c=1dab83

// Output in hexadecimal (uppercase)
printf("a=%hX, b=%X, c=%lX\n", a, b, c);
// Output: a=56, b=5CB, c=1DAB83
```

#### Controlling Spaces

```c
int a1 = 20, a2 = 345, a3 = 700;
int b1 = 56720, b2 = 9999, b3 = 20098;
int c1 = 233, c2 = 205, c3 = 1;
int d1 = 34, d2 = 0, d3 = 23;

printf("%-9d %-9d %-9d\n", a1, a2, a3);
printf("%-9d %-9d %-9d\n", b1, b2, b3);
printf("%-9d %-9d %-9d\n", c1, c2, c3);
printf("%-9d %-9d %-9d\n", d1, d2, d3);
```

**Output**:

```c
20        345       700      
56720     9999      20098    
233       205       1        
34        0         23  
```

- %-9d: Left-align, 9 characters wide, decimal.

### 4.2 User Input

The `scanf` function reads input from the user.

#### Example: Integer Input

```c
int my_num;
printf("Please enter a number: \n");
scanf("%d", &my_num);
printf("The number you entered: %d", my_num);
```

#### Example: String Input

```c
char first_name[30];
printf("Enter your name: \n");
scanf("%s", &first_name);
printf("Hello %s.", first_name);
```

------

## 5. Operators

Operators perform operations on variables and values.

### 5.1 Arithmetic Operators

| Operator | Description | Example |
| -------- | ----------- | ------- |
|` +        `| Add         |` x + y   `|
|` -        `| Subtract    |` x - y   `|
|` *        `| Multiply    |` x * y   `|
|` /        `| Divide      |` x / y   `|
|` %        `| Modulo      |` x % y   `|
|` ++       `| Increment   |` ++x     `|
|` --       `| Decrement   |` --x     `|

#### Example

```c
int my_num = 100 + 50;
int sum1 = 100 + 50;   // 150
int sum2 = sum1 + 250; // 400
int sum3 = sum2 + sum2;// 800
```

### 5.2 Assignment Operators

| Operator | Equivalent |
| :------- | :--------- |
| `x = 5    `|` x = 5      `|
| `x += 3   `|` x = x + 3  `|
| `x -= 3   `|` x = x - 3  `|
| `x *= 3   `|` x = x * 3  `|
| `x /= 3   `|` x = x / 3  `|
| `x %= 3   `|` x = x % 3  `|
| `x &= 3   `|` x = x & 3  `|
| `x \|= 3  `|` x = x \| 3 `|
| `x ^= 3   `|` x = x ^ 3  `|
| `x >>= 3  `|` x = x >> 3 `|
| `x <<= 3  `|` x = x << 3 `|

### 5.3 Comparison Operators

| Operator | Description        | Example |
| -------- | ------------------ | ------- |
|` ==       `| Equal              |` x == y  `|
|` !=       `| Not equal          |` x != y  `|
|` >        `| Greater than       |` x > y   `|
|` <        `| Less than          |` x < y   `|
|` >=       `| Greater or equal   |` x >= y  `|
|` <=       `| Less than or equal |` x <= y  `|

#### Example

```c
int x = 5;
int y = 3;
printf("%d", x > y); // 1 (true)
```

### 5.4 Logical Operators

| `&&` | `and` logical | returns true if both statements are true      | `x < 5 && x < 10`    |
| ---- | ------------- | --------------------------------------------- | -------------------- |
| `||` | `or` logical  | returns true if one of the statements is true | `x < 5 || x < 4`     |
| `!`  | `not` logical | Invert result, return false if true           | `!(x < 5 && x < 10)` |

### 5.5 Bitwise Operators

| Operator | Description | Example                  |
| -------- | ----------- | ------------------------ |
|` &        `| Bitwise AND |` (a & b) = 12 (0000 1100) `|
|` |       `| Bitwise OR  |` (a | b) = 12 (0000 1100)`|
|` ^        `| Bitwise XOR |` (a ^ b) = 49 (0011 0001) `|
|` ~        `| Bitwise NOT |` (~a) = -61 (1100 0011)   `|
|` <<       `| Left shift  |` a << 2 = 240 (1111 0000) `|
|` >>       `| Right shift |` a >> 2 = 15 (0000 1111)  `|

#### Example

```c
unsigned int a = 60; /* 0011 1100 */
unsigned int b = 13; /* 0000 1101 */
int c = 0;

c = a & b;  /* 12 = 0000 1100 */
printf("Line 1 - the value of c is %d\n", c);

c = a | b;  /* 61 = 0011 1101 */
printf("Line 2 - the value of c is %d\n", c);

c = a ^ b;  /* 49 = 0011 0001 */
printf("Line 3 - the value of c is %d\n", c);

c = ~a;     /* -61 = 1100 0011 */
printf("Line 4 - The value of c is %d\n", c);

c = a << 2; /* 240 = 1111 0000 */
printf("Line 5 - the value of c is %d\n", c);

c = a >> 2; /* 15 = 0000 1111 */
printf("Line 6 - The value of c is %d\n", c);
```

------

## 6. Control Flow

Control flow structures dictate the order of execution in a program.

### 6.1 Conditions

#### Example: If-Else

```c
int time = 20;
if (time < 18) 
{
  printf("Goodbye!");
} 
else 
{
  printf("Good evening!");
}
// Output: "Good evening!"

int time2 = 22;
if (time2 < 10)
{
  printf("Good morning!");
} 
else if (time2 < 20) 
{
  printf("Goodbye!");
}
else 
{
  printf("Good evening!");
}
// Output: "Good evening!"
```

### 6.2 Ternary Operator

#### Example

```c
int age = 20;
(age > 19) ? printf("Adult") : printf("Teenager");
// Output: "Adult"
```

### 6.3 `Switch`

#### Example

```c
int day = 4;
switch (day) 
{
  case 3: 
    printf("Wednesday"); 
    break;
  case 4: 
    printf("Thursday"); 
    break;
  default:
    printf("Weekend!");
}
// Output: "Thursday"
```

### 6.4 Loops

#### `While` Loop

```c
int i = 0;
while (i < 5) 
{
  printf("%d\n\r", i);
  i++;
}
```

**Note**: Increment the variable to avoid an infinite loop.

#### `Do-While` Loop

```c
int i = 0;
do
{
  printf("%d\n", i);
  i++;
} while (i < 5);
```

#### `For` Loop

```c
for (int i = 0; i < 5; i++) 
{
  printf("%d\n", i);
}
```

#### `Break` and `Continue`

```c
for (int i = 0; i < 10; i++) 
{
  if (i == 4) 
  {
    break;
  }
  printf("%d\n", i);
}
```

```c
for (int i = 0; i < 10; i++) 
{
  if (i == 4) 
  {
    continue;
  }
  printf("%d\n", i);
}
```

#### `While` with `Break`

```
int i = 0;
while (i < 10) 
{
  if (i == 4) 
  {
    break;
  }
  printf("%d\n", i);
  i++;
}
```

#### `While` with `Continue`

```c
int i = 0;
while (i < 10) 
{
  i++;
  if (i == 4) 
  {
    continue;
  }
  printf("%d\n", i);
}
```

------

## 7. Arrays and Strings

### 7.1 Arrays

Arrays store multiple values of the same type.

#### Example: Declaring and Accessing

```c
int my_numbers[] = {25, 50, 75, 100};
printf("%d", my_numbers[0]); // Output: 25
```

#### Changing Elements

```c
int my_numbers[] = {25, 50, 75, 100};
my_numbers[0] = 33;
printf("%d", my_numbers[0]); // Output: 33
```

#### Looping Through an Array

```c
int my_numbers[] = {25, 50, 75, 100};
int i;
for (i = 0; i < 4; i++) 
{
  printf("%d\n", my_numbers[i]);
}
```

#### Setting Array Size

```c
int my_numbers[4];
my_numbers[0] = 25;
my_numbers[1] = 50;
my_numbers[2] = 75;
my_numbers[3] = 100;
```

### 7.2 Strings

C uses character arrays for strings, terminated by `\0`.

#### Example: Declaring and Printing

```c
char greetings[] = "Hello World!";
printf("%s", greetings);
```

#### Accessing Characters

```c
char greetings[] = "Hello World!";
printf("%c", greetings[0]); // Output: H
```

#### Modifying Strings

```c
char greetings[] = "Hello World!";
greetings[0] = 'J';
printf("%s", greetings); // Output: "Jello World!"
```

#### Alternative Declaration

```c
char greetings[] = {'H','e','l','l','\0'};
printf("%s", greetings); // Output: "Hell"
```

#### String Literals with Pointers

```c
char *greetings = "Hello";
printf("%s", greetings); // Output: "Hello"
```

**Note**: String literals are read-only; modifying them causes undefined behavior.

------

## 8. Functions

Functions modularize code for reuse and clarity.

### 8.1 Declaration and Definition

```c
void my_function(); // Declaration

int main() 
{
  my_function(); // Call
}

void my_function()  // Definition
{
  printf("Good evening!");
}
```

#### Calling Functions

```c
void my_function() // Definition
{
  printf("Good evening!");
}

int main() 
{
  my_function();
  my_function(); // Called twice
}
```

### 8.2 Parameters

```c
void my_function(char name[]) 
{
  printf("Hello %s\n", name);
}

int main() 
{
  my_function("Liam");
  my_function("Jenny");
}
// Output:
// Hello Liam
// Hello Jenny
```

#### Multiple Parameters

```c
void my_function(char name[], int age) 
{
  printf("Hi %s, you are %d years old.\n", name, age);
}

int main() 
{
  my_function("Liam", 3);
  my_function("Jenny", 14);
}
// Output:
// Hi Liam, you are 3 years old.
// Hi Jenny, you are 14 years old.
```

### 8.3 Return Values

```c
int my_function(int x) 
{
  return 5 + x;
}

int main() 
{
  printf("Result: %d", my_function(3)); // Output: 8
}
```

#### Two Parameters

```c
int my_function(int x, int y) 
{
  return x + y;
}

int main() 
{
  printf("Result: %d", my_function(5, 3));
  int result = my_function(5, 3);
  printf("Result = %d", result);
}
// Output:
// Result: 8
// Result = 8
```

### 8.4 Recursion

```c
int sum(int k); // Decleration

int main() 
{
  int result = sum(10);
  printf("%d", result); // Output: 55
}

int sum(int k) // Definition
{
  if (k > 0) 
  {
    return k + sum(k - 1);
  } 
  else 
  {
    return 0;
  }
}
```

------

## 9. Pointers

Pointers store memory addresses, enabling direct memory manipulation.

### 9.1 Memory Address

```c
int my_age = 43;
printf("%p", &my_age); // Output: e.g., 0x7ffe5367e044
```

### 9.2 Creating Pointers

```c
int my_age = 43;
printf("%d", my_age);      // Output: 43
printf("%p", &my_age);     // Output: e.g., 0x7ffe5367e044

int *ptr = &my_age;
printf("%p\n", ptr);       // Output: e.g., 0x7ffe5367e044
printf("%d\n", *ptr);      // Output: 43
```

------

## 10. Structures and Enums

### 10.1 Structures

Structures group related data under one name.

#### Creating a Structure

```c
struct my_structure 
{
  int my_num;
  char my_letter;
};

int main() 
{
  struct my_structure s1;
  return 0;
}
```

#### Strings in Structures

```c
#include <string.h> // for str functions

struct my_structure 
{
  int my_num;
  char my_letter;
  char my_sring[30];
};

int main() 
{
  struct my_structure s1;
  strcpy(s1.my_sring, "Some text");
  printf("my string: %s", s1.my_sring);
  return 0;
}
```

#### Accessing Members

```c
struct my_structure 
{
  int my_num;
  char my_letter;
};

int main() 
{
  struct my_structure s1;
  s1.my_num = 13;
  s1.my_letter = 'B';

  struct my_structure s2 = {13, 'B'};
  printf("My number: %d\n", s1.my_num);
  printf("My letter: %c\n", s1.my_letter);
  return 0;
}
```

#### Multiple Variables

```c
struct my_structure s1;
struct my_structure s2;
s1.my_num = 13;
s1.my_letter = 'B';
s2.my_num = 20;
s2.my_letter = 'C';
```

#### Copying Structures

```c
struct my_structure s1 = {13, 'B', "Some text"};
struct my_structure s2;
s2 = s1;
```

#### Modifying Values

```c
struct my_structure s1 = {13, 'B'};
s1.my_num = 30;
s1.my_letter = 'C';
printf("%d %c", s1.my_num, s1.my_letter);
```

### 10.2 Enums

Enums define named integer constants.

#### Defining Enums

```c
enum week { Mon = 1, Tues, Wed, Thurs, Fri, Sat, Sun };
enum week a, b, c;

enum week { Mon = 1, Tues, Wed, Thurs, Fri, Sat, Sun }a, b, c;
```

#### Assigning Values

```c
enum week { Mon = 1, Tues, Wed, Thurs, Fri, Sat, Sun };
enum week a, b, c;
```

#### Example Application

```c
enum week {Mon = 1, Tues, Wed, Thurs} day;

scanf("%d", &day);

switch(day) 
{
  case Mon: 
    printf("Monday"); 
    break;
  case Tues: 
    printf("Tuesday"); 
    break;
  case Wed: 
    printf("Wednesday"); 
    break;
  case Thursday: 
    printf("Thursday"); 
    break;
  default: 
    printf("Error!");
}
```

------

## 11. C Preprocessor

The preprocessor modifies code before compilation.

### 11.1 Directives

| Directive | Description                     |
| --------- | ------------------------------- |
|` #define   `| Define a macro                  |
|` #include  `| Include a source file           |
|` #undef    `| Undefine a macro                |
|` #ifdef    `| True if macro defined           |
|` #ifndef   `| True if macro not defined       |
|` #if       `| Compile if condition true       |
|` #else     `| Alternative to #if              |
|` #elif     `| Else-if condition               |
|` #endif    `| End conditional block           |
|` #error    `| Print error message             |
|` #pragma   `| Issue special compiler commands |

#### Example

```c
#define MAX_ARRAY_LENGTH 20
#include <stdio.h>
#include "my_header.h"

#define FILE_SIZE 50
#undef FILE_SIZE
#define FILE_SIZE 42
```

### 11.2 Predefined Macros

| Macro      | Description                  |
| ---------- | ---------------------------- |
| `__DATE__` | Current date ("MMM DD YYYY") |
| `__TIME__` | Current time ("HH:MM:SS")    |
| `__FILE__` | Current filename             |
| `__LINE__` | Current line number          |
| `__STDC__` | 1 if ANSI standard compliant |

#### Example

```c
#include <stdio.h>

int main() 
{
  printf("File :%s\n", __FILE__);
  printf("Date :%s\n", __DATE__);
  printf("Time :%s\n", __TIME__);
  printf("Line :%d\n", __LINE__);
  printf("ANSI :%d\n", __STDC__);
}
```

### 11.3 Macro Continuation (\)

```c
#define message_for(a, b) \
  printf(#a " and " #b ": We love you!\n")
```

### 11.4 String Concatenation (#)

```c
#include <stdio.h>

#define ABS(x) ((x) < 0 ? -(x) : (x))

#define message_for(a, b) \
  printf(#a " and " #b ": We love you!\n")

int main(void) 
{
  message_for(Carole, Debra);
}
// Output: Carole and Debra: We love you!
```

### 11.5 `Token Pasting (##)`

```c
#include <stdio.h>

#define TOKEN_PARSER(n) printf("token" #n " = %d", token##n)

int main(void) 
{
  int token34 = 40;
  TOKEN_PARSER(34);
}
// Output: token34 = 40
```

### 11.6 `defined()` Operator

```c
#include <stdio.h>

#if !defined (MESSAGE)
   #define MESSAGE "You wish!"
#endif

int main(void) 
{
  printf("Here is the message: %s\n", MESSAGE);
}
```

### 11.7 Parameterized Macros

```c
#include <stdio.h>

#define MAX(x,y) ( (x) > (y) ? (x) : (y) )

int main(void) 
{
  printf("Max between 20 and 10 is %d\n", MAX(10, 20));
}
// Output: Max between 20 and 10 is 20
```

```c
int square(int x) 
{
  return x * x;
}

#define SQURE(x) ( (x) * (x) )
```

------

## 12. File Handling

C provides functions to read from and write to files.

### 12.1 File Functions

| Function  | Description                   |
| --------- | ----------------------------- |
|` fopen()   `| Open a file                   |
|` fprintf() `| Write data to file            |
|` fscanf()  `| Read data from file           |
|` fputc()   `| Write a character to file     |
|` fgetc()   `| Read a character from file    |
|` fclose()  `| Close a file                  |
|` fseek()   `| Move file pointer to position |
|` fputw()   `| Write an integer to file      |
|` fgetw()   `| Read an integer from file     |
|` ftell()   `| Get current file position     |
|` rewind()  `| Reset file pointer to start   |

### 12.2 File Modes

| Mode | Description                        |
| ---- | ---------------------------------- |
|` r    `| Read text file                     |
|` w    `| Write text file (overwrite)        |
|` a    `| Append text file                   |
|` r+   `| Read/write text file               |
|` w+   `| Read/write text file (overwrite)   |
|` a+   `| Read/write text file (append)      |
|` rb   `| Read binary file                   |
|` wb   `| Write binary file (overwrite)      |
|` ab   `| Append binary file                 |
|` rb+  `| Read/write binary file             |
|` wb+  `| Read/write binary file (overwrite) |
|` ab+  `| Read/write binary file (append)    |

### 12.3 Opening a File (`fopen`)

```c
#include <stdio.h>
void main() 
{
  FILE *fp;
  char ch;
  fp = fopen("file_handle.c", "r");
  while (1) 
  {
    ch = fgetc(fp);
    if (ch == EOF)
      break;
    printf("%c", ch);
  }
  fclose(fp);
}
```

### 12.4 Writing with `fprintf`

```c
#include <stdio.h>
void main() 
{
  FILE *fp;
  fp = fopen("file.txt", "w");
  fprintf(fp, "Hello file for fprintf..\n");
  fclose(fp);
}
```

### 12.5 Reading with `fscanf`

```c
#include <stdio.h>
void main() 
{
  FILE *fp;
  char buff[255];
  fp = fopen("file.txt", "r");
  while(fscanf(fp, "%s", buff) != EOF) 
  {
    printf("%s ", buff);
  }
  fclose(fp);
}
```

### 12.6 Writing with `fputc`

```c
#include <stdio.h>
void main() 
{
  FILE *fp;
  fp = fopen("file1.txt", "w");
  fputc('a', fp);
  fclose(fp);
}
```

### 12.7 Reading with `fgetc`

```c
#include <stdio.h>
#include <conio.h>
void main() 
{
  FILE *fp;
  char c;
  fp = fopen("myfile.txt", "r");
  while( (c = fgetc(fp)) != EOF) 
  {
    printf("%c", c);
  }
  fclose(fp);
}
```

### 12.8 Writing with `fputs`

```c
#include<stdio.h>
#include<conio.h>
void main() 
{
  FILE *fp;
  fp = fopen("myfile2.txt", "w");
  fputs("hello c programming", fp);
  fclose(fp);
}
```

### 12.9 Reading with `fgets`

```c
#include<stdio.h>
#include<conio.h>
void main() 
{
  FILE *fp;
  char text[300];
  fp = fopen("myfile2.txt", "r");
  printf("%s", fgets(text, 200, fp));
  fclose(fp);
}
```

### 12.10 Moving Pointer with `fseek`

```c
#include <stdio.h>
void main(void) 
{
  FILE *fp;
  fp = fopen("myfile.txt", "w+");
  fputs("This is Book", fp);
  fseek(fp, 7, SEEK_SET);
  fputs("Kenny Wong", fp);
  fclose(fp);
}
```

### 12.11 Resetting Pointer with `rewind`

```c
#include <stdio.h>
#include <conio.h>
void main() 
{
  FILE *fp;
  char c;
  fp = fopen("file.txt", "r");
  while( (c = fgetc(fp)) != EOF) 
  {
    printf("%c", c);
  }
  rewind(fp);
  while( (c = fgetc(fp)) != EOF) 
  {
    printf("%c", c);
  }
  fclose(fp);
}
// Output: Hello World! Hello World!
```

### 12.12 Getting Position with `ftell`

```c
#include <stdio.h>
#include <conio.h>
void main () 
{
  FILE *fp;
  int length;
  fp = fopen("file.txt", "r");
  fseek(fp, 0, SEEK_END);
  length = ftell(fp);
  fclose(fp);
  printf("File size: %d bytes", length);
}
// Output: File size: 18 bytes
```

------

## 13. Mathematical Functions

The `<math.h>` library provides mathematical operations.

### Example

```c
#include <math.h>

void main(void) 
{
  printf("%f", sqrt(16));  // 4.000000 (square root)
  printf("%f", ceil(1.4)); // 2.000000 (round up)
  printf("%f", floor(1.4));// 1.000000 (round down)
  printf("%f", pow(4, 3)); // 64.000000 (4^3)
}
```

- `abs(x) `: Absolute value
- `acos(x)`: Arc cosine
- `asin(x)`: Arc sine
- `atan(x)`: Arc tangent
- `cbrt(x)`: Cube root
- `cos(x) `: Cosine
- `exp(x) `: Exponential (e^x)
- `sin(x) `: Sine
- `tan(x) `: Tangent

------

## 14. The `<string.h>` Library

The `<string.h>` library in C provides a collection of functions for manipulating strings (null-terminated character arrays). These functions are essential for tasks like copying, comparing, concatenating, and measuring strings. This section covers the most commonly used functions in `<string.h>`.

### 14.1 Including the Library

To use `<string.h>` functions, include it at the top of your program:

```c
#include <string.h>
```

### 14.2 Common `<string.h>` Functions

Below is a list of key functions with descriptions, syntax, and examples.

#### 1. `strlen()`

- **Description**: Returns the length of a string (excluding the null terminator `\0`).

- **Syntax**: size_t strlen(const char *str);

- Example:

  ```c
  #include <stdio.h>
  #include <string.h>
  
  int main() 
  {
      char str[] = "Hello";
      char len = strlen(str);
      printf("Length of '%s' is %d\n", str, len);
      return 0;
  }
  ```

  - **Output**: Length of 'Hello' is 5

- **Note**: Returns type size_t (an unsigned integer type).

#### 2. `strcpy()`

- **Description**: Copies one string to another, including the null terminator.

- **Syntax**: char *strcpy(char *dest, const char *src);

- Example:

  ```c
  #include <stdio.h>
  #include <string.h>
  
  int main() 
  {
      char dest[20];
      char src[] = "Hello World";
      strcpy(dest, src);
      printf("Copied string: %s\n", dest);
      return 0;
  }
  ```

  - **Output**: Copied string: Hello World

- **Warning**: Ensure dest has enough space to hold src, or buffer overflow may occur.

#### 3. `strncpy()`

- **Description**: Copies up to n characters from src to dest. If src is shorter than n, pads dest with null characters.

- **Syntax**: char *strncpy(char *dest, const char *src, size_t n);

- Example:

  ```c
  #include <stdio.h>
  #include <string.h>
  
  int main() {
      char dest[10];
      char src[] = "Hello";
      strncpy(dest, src, 3);
      dest[3] = '\0'; // Manual null termination
      printf("Copied string: %s\n", dest);
      return 0;
  }
  ```

  - **Output**: Copied string: Hel

- **Note**: Does not automatically null-terminate if src is longer than n.

#### 4. `strcat()`

- **Description**: Concatenates (appends) one string to the end of another.

- **Syntax**: char *strcat(char *dest, const char *src);

- Example:

  ```c
  #include <stdio.h>
  #include <string.h>
  
  int main() 
  {
      char dest[20] = "Hello";
      char src[] = " World";
      strcat(dest, src);
      printf("Concatenated string: %s\n", dest);
      return 0;
  }
  ```

  - **Output**: Concatenated string: Hello World

- **Warning**: dest must have enough space to hold the combined string.

#### 5. `strncat()`

- **Description**: Appends up to n characters from src to dest, ensuring null termination.

- **Syntax**: char *strncat(char *dest, const char *src, size_t n);

- Example:

  ```c
  #include <stdio.h>
  #include <string.h>
  
  int main() 
  {
      char dest[20] = "Hello";
      char src[] = " World";
      strncat(dest, src, 3); // Appends " Wo"
      printf("Concatenated string: %s\n", dest);
      return 0;
  }
  ```
  
  - **Output**: Concatenated string: Hello Wo

#### 6. `strcmp()`

- **Description**: Compares two strings lexicographically. Returns 0 if equal, a negative value if str1 < str2, or a positive value if str1 > str2.

- **Syntax**: int strcmp(const char *str1, const char *str2);

- Example:

  ```c
  #include <stdio.h>
  #include <string.h>
  
  int main() 
  {
      char str1[] = "apple";
      char str2[] = "banana";
      int result = strcmp(str1, str2);
      if (result == 0)
      {
          printf("Strings are equal\n");
      }
      else if (result < 0)
      {
         printf("'%s' is less than '%s'\n", str1, str2);
      } 
      else
      {
         printf("'%s' is greater than '%s'\n", str1, str2);
      }
      return 0;
  }
  ```
  
  - **Output**: apple is less than banana

#### 7. `strncmp()`

- **Description**: Compares up to n characters of two strings.

- **Syntax**: int strncmp(const char *str1, const char *str2, size_t n);

- Example:

  ```c
  #include <stdio.h>
  #include <string.h>
  
  int main() 
  {
      char str1[] = "apple";
      char str2[] = "apricot";
      int result = strncmp(str1, str2, 2); // Compares "ap" vs "ap"
      printf("Result: %d\n", result); // 0 (equal for first 2 chars)
      return 0;
  }
  ```
  

#### 8. `strchr()`

- **Description**: Finds the first occurrence of a character in a string, returning a pointer to it or NULL if not found.

- **Syntax**: char *strchr(const char *str, int c);

- Example:

  ```c
  #include <stdio.h>
  #include <string.h>
  
  int main() 
  {
      char str[] = "Hello World";
      char *ptr = strchr(str, 'W');
      if (ptr)
      {
          printf("Found 'W' at: %s\n", ptr);
      }   
      else
      {
          printf("'W' not found\n");
      }
      return 0;
  }
  ```
  
  - **Output**: Found 'W' at: World

#### 9. `strstr()`

- **Description**: Finds the first occurrence of a substring in a string, returning a pointer to it or NULL if not found.

- **Syntax**: `char *strstr(const char *haystack, const char *needle);`

- Example

  ```c
  #include <stdio.h>
  #include <string.h>
  
  int main() 
  {
      char str[] = "Hello World";
      char *ptr = strstr(str, "Wor");
      if (ptr)
          printf("Found 'Wor' at: %s\n", ptr);
      else
          printf("'Wor' not found\n");
      return 0;
  }
  ```
  
  - **Output**: Found 'Wor' at: World

#### 10. `memset()`

- **Description**: Fills a block of memory with a specified value.

- **Syntax**: `void *memset(void *ptr, int value, size_t n);`

- Example

  ```c
  #include <stdio.h>
  #include <string.h>
  
  int main() 
  {
      char str[10];
      memset(str, 'A', 5); // Fills first 5 bytes with 'A'
      str[5] = '\0'; // Null terminate
      printf("String: %s\n", str);
      return 0;
  }
  ```
  
  - **Output**: String: AAAAA

### 14.3 Best Practices

- **Buffer Safety**: Always ensure destination buffers are large enough to avoid overflows (e.g., use strncpy instead of strcpy when possible).
- **Null Termination**: Functions like strncpy may not add a null terminator—add it manually if needed.
- **Return Values**: Check return values (e.g., NULL from strchr or strstr) to handle errors.
- **Performance**: For small strings, simple loops might be faster than some <string.h> functions due to function call overhead.

### 14.4 Example Program

Here’s a program combining several <string.h> functions:

```c
#include <stdio.h>
#include <string.h>

int main() 
{
    char str1[20] = "Hello";
    char str2[] = " World";
    char buffer[20];

    // Copy and concatenate
    strcpy(buffer, str1);
    strcat(buffer, str2);
    printf("Combined: %s\n", buffer);

    // Compare
    if (strcmp(str1, "Hello") == 0) 
    {
        printf("str1 is 'Hello'\n");
    }

    // Find substring
    char *ptr = strstr(buffer, "Wor");
    if (ptr) 
    {
        printf("Found 'Wor' at: %s\n", ptr);
    }

    // Length
    printf("Length of buffer: %d\n", strlen(buffer));
    return 0;
}
```

- Output: Combined: Hello World str1 is 'Hello' Found 'Wor' at: World Length of buffer: 11


------

## 15. Creating Library Files in C

Libraries in C allow you to bundle reusable code into separate files that can be shared across multiple programs. There are two primary types of libraries: **static libraries** (.a files on Unix-like systems) and **dynamic libraries** (.so files on Unix-like systems, .dll on Windows). This section covers how to create, compile, and use both types, along with their differences and best practices.

### 15.1 Overview of Libraries

- **Static Libraries**: Linked into the executable at compile time, making the program self-contained.
- **Dynamic Libraries**: Loaded at runtime, keeping the executable smaller but requiring the library to be available on the system.

### 15.2 Creating a Static Library

Static libraries are created using the `ar` tool and linked with the program during compilation.

#### Step-by-Step Process

1. Write the Source Code(`my_lib.c`)

   Create a `.c` file with the functions you want to include in the library.

   ```c
   #include "my_lib.h"
   
   void say_hello()
   {
       printf("Hello from the static library!\n");
   }
   
   int add(int a, int b) 
   {
       return a + b;
   }
   ```

2. Create a Header File(`my_lib.h`)

   Define function prototypes in a `.h` file for users of the library.

   ```c
   #ifndef MY_LIB_H
   #define MY_LIB_H
   
   #include <stdio.h>
   
   void say_hello();
   int add(int a, int b);
   
   #endif
   ```

3. Compile the Source to an Object File

   ```bash
$ gcc -c my_lib.c -o my_lib.o
   ```

   - -c: Compile only, don’t link.

4. Create the Static Library

   Use the ar command to archive the object file into a static library.

   ```bash
   $ ar rcs lib_my_lib.a my_lib.o
   ```

   - `r`: Replace existing files in the archive.
   - `c`: Create the archive if it doesn’t exist.
   - `s` Generate an index for faster linking.
   - Naming convention: Library files typically start with lib (e.g., `lib_my_lib.a`).
   
5. Write a Program to Use the Library

   Create a main program that includes the header and calls the library functions.

   ```c
   #include "my_lib.h"
   
   int main() 
   {
       say_hello();
       printf("Sum: %d\n", add(5, 3));
       return 0;
   }
   ```

6. Compile and Link the Program

   Link the static library with your program.

   ```bash
   $ gcc main.c -L. -lmy_lib -o my_program
   ```

   - `-L.`: Look for libraries in the current directory.
   - `-lmy_lib`: Link with `lib_my_lib.a` (omit the lib prefix and .a extension).
   - `-o my_program`: Name the output executable.
   
7. Run the Program

   ```bash
   $ ./my_program
   ```

   Output: Hello from the static library! Sum: 8


### 15.3 Creating a Dynamic Library

Dynamic libraries are created with gcc using the -shared flag and linked at runtime.

#### Step-by-Step Process

1. **Write the Source Code** (`my_lib.c`): Same as above.

2. **Create a Header File** (`my-lib.h`): Same as above.

3. Compile with Position-Independent Code:

   ```bash
   $ gcc -c -fPIC my_lib.c -o my_lib.o
   ```

   Create the Dynamic Library;

   ```bash
   $ gcc -shared -o lib_my_lib.so my_lib.o
   ```

   **Write a Program** (`main.c`): Same as above.

4. Compile and Link:

   ```bash
   $ gcc main.c -L. -lmy_lib -o my_program
   ```

   Set the Library Path:

   ```bash
   $ export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
   ```

5. Run the Program:

   ```bash
   $ ./my_program
   ```

   - Output: Hello from the dynamic library! Sum: 8


### 15.4 Key Differences Between Static and Dynamic Libraries

| Feature                | Static Library (.a)                  | Dynamic Library (.so)           |
| ---------------------- | ------------------------------------ | ------------------------------- |
| **Linking Time**       | Compile time                         | Runtime                         |
| **Executable Size**    | Larger (includes library code)       | Smaller (references library)    |
| **Dependency**         | None after compilation               | Requires library at runtime     |
| **Update Flexibility** | Requires recompilation               | Replace library file            |
| **Performance**        | Slightly faster (no runtime loading) | Slight overhead at startup      |
| **Portability**        | Fully portable executable            | Depends on library availability |

### 15.5 Best Practices

- **Naming**: Always prefix library names with lib (e.g., `lib_my_lib.a`, `lib_my_lib.so`) to follow convention.
- **Header Files**: Use include guards (`#ifndef`, `#define`, `#endif`) to prevent multiple inclusions.
- **Modularity**: Keep library functions focused on specific tasks to improve reusability.
- **Documentation**: Include comments or a README explaining how to use the library.
- **Versioning**: For dynamic libraries, consider versioning (e.g., `lib_my_lib.so.1.0`) to manage updates.
- **Error Handling**: Add error-checking code in library functions for robustness.

### 15.6 Example with Error Handling

Here’s an enhanced version of the library with error handling:

`my_lib.c`:

```c
#include <stdio.h>
#include "my_lib.h"

void say_hello() 
{
    printf("Hello from the library!\n");
}

int add(int a, int b) 
{
    if (a > 0 && b > 0 && a > INT_MAX - b) 
    {
        fprintf(stderr, "Error: Integer overflow detected\n");
        return -1;
    }
    return a + b;
}
```

`my_lib.h`:

```c
#ifndef MY_LIB_H
#define MY_LIB_H

#include <limits.h>

void say_hello();
int add(int a, int b);

#endif
```

`main.c`:

```c
#include "mylib.h"
int main() 
{
    say_hello();
    int result = add(5, 3);
    if (result != -1) {
        printf("Sum: %d\n", result);
    }
    return 0;
}
```

## 16. Comprehensive Example

This section provides a detailed example focusing on functions (Section 8) within a thread-safe counter system implemented as a static library (Section 15). It demonstrates function declarations, definitions, parameters, return values, and recursion, while integrating other core C concepts from this tutorial. The example includes a header file, library source file, and main program to showcase modular programming.

### 16.1 Library Header File: `counter.h`

```c
/*
 * counter.h
 * Created on: Apr 05, 2025
 * Author: Alireza Jahanbakhshi
 * Description: Header file for counter library with function-centric design
 */

/* Include guard (11.1 Directives) */
#ifndef COUNTER_H
#define COUNTER_H

#include <pthread.h>  /* For thread synchronization */

/* Enums (10.2) - Operation types */
enum OperationType
{
    OP_INCREMENT = 0,
    OP_DECREMENT,
    OP_DOUBLE,
    OP_HALF
};

/* Structures (10.1) - Counter structure */
struct Counter
{
    pthread_mutex_t mutex;  /* Mutex for thread safety */
    volatile int value;     /* Volatile (3.4) for thread-safe access */
    int min_value;
    int max_value;
    char name[32];          /* String (7.2) for counter identification */
};

/* Typedef for cleaner usage */
typedef struct Counter Counter;

/* Function Declarations (8.1) - Emphasis on function design */

/* Initialize a counter with given parameters */
void counter_init(Counter* counter, int initial_value, int min_value, int max_value, const char* name);

/* Perform an operation on the counter, returning success status */
int counter_operate(Counter* counter, enum OperationType op);

/* Save counter state to file, returning bytes written */
int save_counter_to_file(Counter* counter);

/* Load counter state from file, returning 1 on success, 0 on failure */
int load_counter_from_file(Counter* counter, const char* name);

/* Get current counter value with thread safety */
int counter_get_value(const Counter* counter);

/* Cleanup counter resources */
void counter_destroy(Counter* counter);

#endif /* COUNTER_H */
```

### 16.2 Library Source File: `counter.c`

```c
/*
 * counter.c
 * Created on: Apr 05, 2025
 * Author: Alireza Jahanbakhshi
 * Description: Implementation of counter library with focus on functions
 */

#include "counter.h"  /* First include: custom library (15) */
#include <stdio.h>
#include <string.h>

/* Preprocessor directive (11.1) */
#define FILENAME "counter_data.txt"

/* External volatile global (3.4 extern, volatile) */
extern volatile int global_operation_count;

/* Static global (3.4 static) - Persistent counter for operations */
static int total_operations = 0;

/* Function Definitions (8.1) - Emphasis on parameters and return values */

/* Initialize counter (8.2 Parameters) */
void counter_init(Counter* counter, int initial_value, int min_value, int max_value, const char* name)
{
    auto int local_init = 0;         /* Auto storage class (3.4) */
    register int temp = initial_value; /* Register (3.4) for speed */
    pthread_mutex_init(&counter->mutex, NULL);
    counter->value = temp + local_init; /* Assignment (5.2) */
    counter->min_value = min_value;
    counter->max_value = max_value;
    strncpy(counter->name, name, sizeof(counter->name) - 1); /* String handling (14) */
    counter->name[sizeof(counter->name) - 1] = '\0';
}

/* Operate on counter (8.3 Return Values) */
int counter_operate(Counter* counter, enum OperationType op)
{
    register int success = 0;       /* Register (3.4) for frequent use */
    static int local_count = 0;     /* Static (3.4) persists across calls */
    register int new_value;         /* Register for arithmetic */
    
    pthread_mutex_lock(&counter->mutex);
    new_value = counter->value;
    
    switch (op)  /* Switch (6.3) */
    {
        case OP_INCREMENT:
            if (new_value < counter->max_value) /* Condition (6.1) */
            {
                new_value++;            /* Arithmetic (5.1) */
                success = 1;
            }
            break;
        case OP_DECREMENT:
            if (new_value > counter->min_value)
            {
                new_value--;
                success = 1;
            }
            break;
        case OP_DOUBLE:
            if (new_value * 2 <= counter->max_value)
            {
                new_value *= 2;
                success = 1;
            }
            break;
        case OP_HALF:
            if (new_value / 2 >= counter->min_value)
            {
                new_value /= 2;
                success = 1;
            }
            break;
    }
    
    if (success)
    {
        counter->value = new_value;
    }
    
    pthread_mutex_unlock(&counter->mutex);
    local_count++;
    global_operation_count++; /* Volatile access */
    total_operations++;
    return success; /* Return status */
}

/* Save to file (12) with return value */
int save_counter_to_file(Counter* counter)
{
    register FILE* fp = fopen(FILENAME, "a"); /* Register (3.4) */
    int bytes_written = 0;
    
    if (fp != NULL) /* Pointer check (9) */
    {
        bytes_written = fprintf(fp, "%s:%d\n", counter->name, counter->value); /* Output (12.4) */
        fclose(fp);
    }
    return bytes_written > 0 ? bytes_written : -1; /* Ternary (6.2) for error handling */
}

/* Load from file (12) with return value */
int load_counter_from_file(Counter* counter, const char* name)
{
    register FILE* fp = fopen(FILENAME, "r"); /* Register (3.4) */
    int success = 0;
    
    if (fp != NULL)
    {
        char line[64]; /* Array (7.1) */
        rewind(fp); /* Reset pointer (12.11) */
        while (fgets(line, sizeof(line), fp) != NULL) /* Read line (12.9) */
        {
            char file_name[32];
            register int file_value;
            if (sscanf(line, "%31[^:]:%d", file_name, &file_value) == 2) /* Read (12.5) */
            {
                if (strcmp(file_name, name) == 0) /* String comparison (14) */
                {
                    counter->value = file_value;
                    success = 1;
                    break;
                }
            }
        }
        fclose(fp);
    }
    return success;
}

/* Get counter value (8.3 Return Values) */
int counter_get_value(const Counter* counter)
{
    register int value; /* Register (3.4) */
    pthread_mutex_lock((pthread_mutex_t*)&counter->mutex); /* Cast for const */
    value = counter->value;
    pthread_mutex_unlock((pthread_mutex_t*)&counter->mutex);
    return value;
}

/* Destroy counter (no return value needed) */
void counter_destroy(Counter* counter)
{
    pthread_mutex_destroy(&counter->mutex);
}
```

### 16.3 Main Program: `main.c`

```c
/*
 * main.c
 * Created on: Apr 05, 2025
 * Author: Alireza Jahanbakhshi
 * Description: Main program demonstrating function usage with counter library
 */

#include "counter.h" /* First include: custom library (15) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

/* Preprocessor (11) */
#define MAX_COUNTERS 5
#define MIN(a,b) ((a) < (b) ? (a) : (b)) /* Parameterized macro (11.7) */
#define VERSION "1.0"

/* External volatile global definition (3.4) */
volatile int global_operation_count = 0;

/* Recursive function (8.4) - Calculate factorial */
int factorial(int n)
{
    register int result; /* Register (3.4) */
    result = (n <= 1) ? 1 : n * factorial(n - 1); /* Recursion with ternary (6.2) */
    return result;
}

/* Thread function (8.2 Parameters) - Perform counter operations */
void* thread_func(void* arg)
{
    Counter* counter = (Counter*)arg; /* Pointer (9) */
    register int i;
    
    for (i = 0; i < 100; i++) /* Loop (6.4) */
    {
        enum OperationType op = (enum OperationType)(rand() % 4);
        if (!counter_operate(counter, op)) /* Use function return value */
        {
            printf("Operation %d failed on %s\n", op, counter->name);
        }
    }
    int bytes = save_counter_to_file(counter);
    if (bytes < 0)
    {
        printf("Failed to save %s\n", counter->name);
    }
    return NULL;
}

/* Main function - Orchestrates program flow */
int main(void)
{
    Counter counters[MAX_COUNTERS]; /* Array (7.1) */
    pthread_t threads[MAX_COUNTERS];
    static const char* names[] = {"counter_one", "counter_two", "counter_three", 
                                 "counter_four", "counter_five"}; /* Static (3.4) */
    auto int i; /* Auto (3.4) */
    register double angle = M_PI / 4; /* Register (3.4) */
    
    /* Mathematical Functions (13) */
    printf("Sine of PI/4: %.2f\n", sin(angle)); /* Output formatting (4.1) */
    
    /* Initialize counters using function */
    for (i = 0; i < MAX_COUNTERS; i++)
    {
        counter_init(&counters[i], 100, 0, 200, names[i]);
        if (!load_counter_from_file(&counters[i], names[i]))
        {
            printf("Failed to load %s, using initial value\n", names[i]);
        }
    }
    
    /* Create threads */
    for (i = 0; i < MAX_COUNTERS; i++)
    {
        pthread_create(&threads[i], NULL, thread_func, &counters[i]);
    }
    
    /* Wait for threads */
    for (i = 0; i < MAX_COUNTERS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
    /* Display results using functions */
    printf("\nCounter Results (Version " VERSION "):\n");
    printf("Global operations: %d\n", global_operation_count);
    
    for (i = 0; i < MAX_COUNTERS; i++)
    {
        register int value = counter_get_value(&counters[i]);
        printf("%s: %d (Factorial: %d)\n", counters[i].name, value, 
               factorial(MIN(value, 10)));
    }
    
    /* User Input (4.2) and String Handling (14) */
    char buffer[32];
    printf("\nEnter a counter name: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    
    for (i = 0; i < MAX_COUNTERS; i++)
    {
        if (strcmp(counters[i].name, buffer) == 0)
        {
            printf("Found %s with value %d\n", buffer, counter_get_value(&counters[i]));
            break;
        }
    }
    
    /* Bitwise Operators (5.5) */
    register unsigned int flags = 0;
    flags |= 1 << 2;
    printf("Flags after setting bit 2: %u\n", flags);
    flags &= ~(1 << 2);
    printf("Flags after clearing bit 2: %u\n", flags);
    
    /* Additional File Handling (12) */
    register FILE* fp = fopen(FILENAME, "r+");
    if (fp != NULL)
    {
        fseek(fp, 0, SEEK_END); /* Move pointer (12.10) */
        fputc('\n', fp); /* Write char (12.6) */
        char c = fgetc(fp); /* Read char (12.7) */
        fputs("End of data", fp); /* Write string (12.8) */
        printf("File position: %ld\n", ftell(fp)); /* Get position (12.12) */
        fclose(fp);
    }
    
    /* Cleanup using function */
    for (i = 0; i < MAX_COUNTERS; i++)
    {
        counter_destroy(&counters[i]);
    }
    
    return 0;
}
```

### 16.4 Compilation and Execution

1. Compile the library:

   ```bash
   $ gcc -c counter.c -o counter.o ar rcs libcounter.a counter.o
   ```

   

2. Compile and link the main program:

   ```bash
   $ gcc main.c -L. -lcounter -pthread -lm -o counter_system
   ```

   

3. Run:

   ```bash
   $ ./counter_system
   ```

   

### 16.5 Sample Output:

```c
Sine of PI/4: 0.71

Counter Results (Version 1.0):
Global operations: 500
counter_one: 145 (Factorial: 3628800)
counter_two: 87 (Factorial: 3628800)
counter_three: 162 (Factorial: 3628800)
counter_four: 93 (Factorial: 3628800)
counter_five: 110 (Factorial: 3628800)

Enter a counter name: counter_one
Found counter_one with value 145
Flags after setting bit 2: 4
Flags after clearing bit 2: 0
File position: 123
```

### 16.6 Concepts Demonstrated with Function Focus

- Functions (8):
  - **Declaration and Definition (8.1)**: All library functions declared in counter.h, defined in counter.c.
  - **Parameters (8.2)**: Multiple parameters in counter_init, counter_operate, etc.
  - **Return Values (8.3)**: Functions like counter_operate, save_counter_to_file, and counter_get_value return meaningful values.
  - **Recursion (8.4)**: factorial function demonstrates recursive calculation.
- Other Key Concepts:
  - **Storage Classes (3.4)**: auto, register, static, extern, volatile
  - **Data Types (3.1)**: int, char, double, etc.
  - **Naming Conventions (3.2)**: Snake case (e.g., counter_one)
  - **Variables and Constants (3.3, 3.5)**: Various declarations and #define
  - **Input/Output (4)**: printf and fgets
  - **Operators (5)**: Arithmetic, assignment, comparison, logical, bitwise
  - **Control Flow (6)**: If-else, ternary, switch, loops
  - **Arrays and Strings (7)**: Counter arrays, string operations
  - **Pointers (9)**: Used in function parameters and file handling
  - **Structures and Enums (10)**: Counter struct, OperationType enum
  - **Preprocessor (11)**: Macros and directives
  - **File Handling (12)**: Full range of file operations
  - **Mathematical Functions (13)**: sin from <math.h>
  - **String.h Library (14)**: strcpy, strcmp, etc.
  - **Library Creation (15)**: Static library implementation

This example emphasizes functions as the core of the program’s design, showcasing their power in modularizing code while integrating other C concepts for a comprehensive demonstration.
