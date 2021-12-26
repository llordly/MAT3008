# ****Homework#5****

모든 문제의 풀이는 <A href = "https://hconnect.hanyang.ac.kr/2021_MAT3008_11255/2021_mat3008_2017029589/-/blob/master/Homework%235/main.cpp" target = "self" > main.cpp </A>에 존재한다.

각 행렬의 정보는 다음과 같다.
![matrix.png](https://hconnect.hanyang.ac.kr/2021_MAT3008_11255/2021_mat3008_2017029589/-/raw/master/Homework%235/matrix.png)

실제로 첫번째 행렬의 경우 역행렬이 0으로 해가 존재하지 않거나 무수히 많다.

## 1. Gauss-Jordan Elimination(gaussj())

- `Gauss-jordan` 방법을 사용한 `gaussj()`함수를 이용해서 해를 구한 것은 다음과 같다.
- `Gaussj(A, b)`로 호출하며, 해는 `b`에 담긴다.

### result
- lineq1.dat
```
gaussj : root of Ax = b
x: [1.666667, -1.666667, -0.000000, -0.666667]
```
- lineq2.dat
```
gaussj : root of Ax = b
x: [-2.873566, -0.612357, 0.976277, 0.635819, -0.553441]
```
- lineq3.dat
```
gaussj : root of Ax = b
x: [-0.326608, 1.532293, -1.044825, -1.587448, 2.928481, -2.218931]

```


## 2. LU decomposition(ludcmp())

- `LU decomposition` 방법을 사용한 `ludcmp()`함수를 사용해서 해를 구했다.
- `ludcmp`를 통해 upper triangle을 구한 후, `lubksb()`를 사용해서 `upper triangle`과 `b`를 back substitution해주면 해를 구할 수 있고, 이 해는 `b`에 담긴다.


### result
- lineq1.dat
```
LU decomposition : root of Ax = b
x: [1.900000, -1.200000, -0.700000, -0.900000]
```
- lineq2.dat
```
LU decomposition : root of Ax = b
x: [-2.873566, -0.612357, 0.976277, 0.635819, -0.553441]
```
- lineq3.dat
```
LU decomposition : root of Ax = b
x: [-0.326608, 1.532293, -1.044825, -1.587448, 2.928481, -2.218931]

```

## 3. Singular Value Decomposition(svdcmp())

- `Singular Value Decomposition` 방법을 사용한 `svdcmp()`함수를 사용해서 해를 구했다.
- `Svdcmp`를 통해 `u, w, v`를 구하고 `svbksb(u, w, v, b, x)`를 사용해서 `x`에 해를 담는다.


### result
- lineq1.dat
```
Singular Value Decomposition : root of Ax = b
x: [1.733333, -1.533333, -0.200000, -0.733333]

```
- lineq2.dat
```
Singular Value Decomposition : root of Ax = b
x: [-2.873566, -0.612357, 0.976277, 0.635819, -0.553441]

```
- lineq3.dat
```
Singular Value Decomposition : root of Ax = b
x: [-0.326608, 1.532293, -1.044825, -1.587448, 2.928481, -2.218931]

```


## 4. Iterative Improvement(mprove())

- `Iterative improvement` 방법을 사용한 `mprove()`함수를 사용해서 해를 구했다.
- 우선 `lu decomposition`을 통해 해를 구한다. 
  - 이 해를 오차가 있는 해라고 보고, `mprove` 함수를 적용해서 `delta x`를 구한다.
  - 오차가 있는 해에서 `delta x`를 빼서 결과 값을 구한다.


### result
- lineq1.dat
```
Iterative Improvement : root of Ax = b
x: [1.250000, -2.500000, 1.250000, -0.250000]

```
- lineq2.dat
```
Iterative Improvement : root of Ax = b
x: [-2.873566, -0.612357, 0.976277, 0.635819, -0.553441]

```
- lineq3.dat
```
Iterative Improvement : root of Ax = b
x: [-0.326608, 1.532293, -1.044825, -1.587448, 2.928481, -2.218931]

```

## 5. Inverse & Determinant

- 우선 `Inverse matrix`는 `gauss Jordan elimination` 함수의 결과값으로 `A`에 담긴 값이기 때문에 `guass()`함수를 호출한 후 `A`에 담긴 값을 출력하도록 했다.

### result(Inverse)
- lineq1.dat
```
Inverse Matrix
6.0048e+15 2.2518e+15 -2.2518e+15 -7.506e+14 
1.20096e+16 4.5036e+15 -4.5036e+15 -1.5012e+15 
-1.80144e+16 -6.7554e+15 6.7554e+15 2.2518e+15 
-6.0048e+15 -2.2518e+15 2.2518e+15 7.506e+14 
```
- lineq2.dat
```
Inverse Matrix
0.354536 0.766945 0.207769 -0.595412 0.253128 
0.0354536 0.126694 0.195777 -0.159541 0.0503128 
-0.138686 -0.0985401 -0.0967153 0.124088 0.0164234 
-0.0521376 -0.303962 -0.0232013 0.234619 -0.0445777 
0.149114 0.459333 0.0513556 -0.171011 0.0424922 
```
- lineq3.dat
```
Inverse Matrix
-0.162205 0.122801 0.0240679 -0.0164308 -0.0228397 0.0461324 
0.169407 -0.0411167 0.228313 -0.087624 0.180306 -0.395655 
-0.0116364 0.122745 -0.117407 -0.180981 0.0159104 0.186766 
0.105669 -0.0517256 -0.108916 0.299774 0.000858666 -0.190541 
-0.053026 -0.0423615 0.160508 -0.224034 0.161811 0.0150242 
-0.0623407 -0.0646943 -0.234216 0.351126 -0.364828 0.434633
```

### result(Determinant)

- `Determinant`는 upper of lower triangle에서 대각 성분의 곱으로 표현할 수 있다.
- `LU decomposition`의 결과로 `A`행렬이 triangle matrix로 만들어지면 대각성분의 곱을 `determinant`로 return하도록 했다.

- lineq1.dat
```
Determinant: -4.44089e-15
```
- lineq2.dat
```
Determinant: 3836
```
- lineq3.dat
```
Determinant: 16178.4
```

## 6. Conclusion

- `Lineq1.dat`는 실제로 `determinant`가 0으로 역행렬이 존재하지 않는다.
- `Deternimant`값을 보면 0에 굉장히 근사한 값으로 표현된다. 그래서 해가 무수히 많거나 없기 때문에 해를 구할 수 없다.
- 하지만 우리가 사용한 4가지 방법이 모두 해를 구했고, 각자 다른 값을 보여줬다.
- 즉 역행렬이 존재하지 않을 경우 해를 정확하게 찾지 못한다는 단점이 존재한다.
- 나머지 경우엔 문제없이 해를 정확하게 찾았다.

