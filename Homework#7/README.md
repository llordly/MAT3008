#  <center>Homework#7</center>

**컴퓨터소프트웨어학부 2017029589 류지범**

##  #0

- 11 * 11 Symmetric Matrix를 Gaussian distribution을 이용해서 Random Generate한다.
- NR in C의 `jacobi()`를 이용해서 `Eigen values`와 `Eigen vectors`를 구한다.
- NR in C의 `eigsrt()`를 이용해서 내림차순으로 `Eigen values`와 `Eigen vectors`를 정렬한다.

## #1

- mean은 0.0으로, standard deviation은 1.0으로 하는 random number를 generate해서 matrix A에 symmetry하게 넣어준다.

  ```c++
    for (int i = 0; i < n; ++i) {
          for (int j = i; j < n; ++j) {
              A[i][j] = A[j][i] = gasdev(idum) * s + m;
          }
      }
  ```

- `jacobi()`와 `eigsrt()`를 사용해서 결과값을 만든다.

  ```c++
  jacobi(A, d, v, nroot);
  eigsrt(d, v);
  ```

###  result

<img src="https://hconnect.hanyang.ac.kr/2021_MAT3008_11255/2021_mat3008_2017029589/-/raw/master/Homework%237/homework%237.png" />