#  <center>Homework#9</center>

**컴퓨터소프트웨어학부 2017029589 류지범**

##  #0 

- 소스코드는 <A href = "https://hconnect.hanyang.ac.kr/2021_MAT3008_11255/2021_mat3008_2017029589/-/blob/master/Homework%239/main.cpp" target = "self" > main.cpp </A>에 존재한다.
- `nr.h`를 사용했다.

## #1 General linear least-square

- Linear data Fitting은 `General linear least-square`를 통해서 한다.

- 우리가 구해야할 식은 다음과 같고, 행렬로 표현할 수 있다.
  - <img src="https://github.com/llordly/MAT3008/blob/master/Homework%239/2.png?raw=true" style="zoom:50%;" />
  
- `General linear least-square`를 이용하면 다음의 식을 계산해서 `c`를 구하면 된다.
  - <img src="https://github.com/llordly/MAT3008/blob/master/Homework%239/1.png?raw=true" style="zoom:50%;" />
  - 이때 J는 위의 행렬식을 참고하면 다음과 같이 표현할 수 있다.
  - <img src="https://github.com/llordly/MAT3008/blob/master/Homework%239/3.png?raw=true" style="zoom:50%;" />

- `x'`의 식을 구하는 함수는 다음과 같다. `J^T * J`를 구하고 `J^T * y`를 구한 후 `gaussj` 함수를 이용해서 해를 구한다.

  - ```c++
    void cal_x(vector<vector<double>> J, vector<double> x) {
        Mat_IO_DP A(3, 3);
        Mat_IO_DP b(3, 1);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                DP temp = 0;
                for (int k = 0; k < J.size(); ++k) {
                    temp += J[k][i] * J[k][j];
                }
                A[i][j] = temp;
            }
        }
        
        for (int i = 0; i < 3; ++i) {
            DP temp = 0;
            for (int j = 0; j < J.size(); ++j) {
                temp += J[j][i] * x[j];
            }
            b[i][0] = temp;
        }
        
        gaussj(A, b);
    ```

- `y'`를 구하는 함수는 `x'`을 구하는 것과 동일하다.

## #2 Result

- 결과는 다음과 같다.
- <img src="https://github.com/llordly/MAT3008/blob/master/Homework%239/result.png?raw=true" alt="result" style="zoom:80%;" />
