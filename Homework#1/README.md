# **Homework#1**

## 1. method 1
### machine accuracy with `machar()`

- `machar()` is numerical recipe's function.
- I made `machar_double()` by changing `machar()`'s float type to the double type.
- I created `machar.h` where `machar()`and `machar_double()` are defined
- `machar.cpp` and `machar_double.cpp` file is included too

### **result**
```
machine accuracy of float with machar(): 1.19209e-07
machine accuracy of double with machar_double(): 2.22045e-16
```

## 2. method 2
### machine accuracy with `get_eps()`

- `get_eps_float()` is float type machine accuracy and `get_eps_double()` is double type machine accuracy
- I found machine accuracy by dividing 1 by 2 until 1 + (1/2)^n = 1
  - n of float is 24, n of double is 53

### **result**

```
machine accuracy of float with get_eps_float(): 1.19209e-07
machine accuracy of float with get_eps_double(): 2.22045e-16
```