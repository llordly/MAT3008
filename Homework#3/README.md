# ****Homework#3****

  

## 1. Find the roots of the Bessel function

모든 코드는 <A href = "https://github.com/llordly/MAT3008/blob/master/Homework%233/main.cpp" target = "self" > main.cpp </A>에 구현되어있다.

<img src="https://github.com/llordly/MAT3008/blob/master/Homework%233/result.png?raw=true" alt="result.png" style="zoom:50%;" />

각 method에 대한 결과와 걸린 시간을 `ms`단위로  표현했다.
`zbrak`함수를 사용해서 root가 존재하는 구간을 `xb1` `xb2` vector에 담고 각 method에 해당하는 함수를 사용해서 root를 구했다.




## 2. Muller method

<A href = "https://github.com/llordly/MAT3008/blob/master/Homework%233/main.cpp" target = "self" > main.cpp </A> 에 `muller` 함수를 같이 작성했다.
<img src="https://github.com/llordly/MAT3008/blob/master/Homework%233/muller.png?raw=true" style="zoom:50%;" />

`p0`, `p1`, `p2`를 공식에 따라 계속 갱신해나가고, `relative error`가 `xacc`보다 작아질 때의 `p3`를 root로 반환하도록 했다.

## 3. Convergence speed

|Method|Convergence Speed|
|:---:|:---:|
|Bisection|**14ms**|
|Linear Interpolation|7ms|
|Secant|6ms|
|Newton-Raphson|7ms|
|Newton with bracketing|5ms|
|Muller|6ms|
method의 실행 전 후를 기점으로 `clock()`를 통해 시간을 측정했다.
`Bisection method`를 제외한 나머지는 거의 다 `5~6ms`로 비슷한 수렴 속도를 보여주었고 `Bisection method`만 `14ms`로 비교적 느린 수렴 속도를 보여주었다.

## 4. Solve problem using rtsafe

모든 함수는 https://www.wolframalpha.com 의 결과와 비교했다.

### 1)
- $$
  f(x) = 10e^xsin(2\pi x) - 2 = 0 \;on\;[0.1, 1]
  \\
  f'(x) = 10e^{-x} * (2\pi cos(2\pi x) - sin(2\pi x))
  $$

<img src="https://github.com/llordly/MAT3008/blob/master/Homework%233/func1.png?raw=true" alt="func1" style="zoom:30%;" />

#### result
```
func1 in [0.1, 1]
1'th root: 0.4492608307
```

### 2)
- $$
  f(x) =  x^2 - 2xe^{-2x} + e^{-2x} = 0\; on\; [0, 1]
  \\
  f''(x) = 2e^{-2x}\, *\, (e^x + 1)\, *\, (e^x * x - 1)
  $$

<img src="https://github.com/llordly/MAT3008/blob/master/Homework%233/func2.png?raw=true" alt="func2" style="zoom:30%;" />

#### result
```
func2 in [0, 1]
1'th root: 0.5671432872
2'th root: 0.5671432927
```
### 
- $$
  f(x) = cos(x + \sqrt{2}) + x(\frac{x}{2} + \sqrt{2}) = 0\; on\; [-2, 1]
  \\
  f'(x) = x - sin(x + \sqrt{2}) + \sqrt{2}
  $$

<img src="https://github.com/llordly/MAT3008/blob/master/Homework%233/func3.png?raw=true" alt="func3" style="zoom:33%;" />

#### result
```
func3 in [-2, -1]
1'th root: 0.4324731422
2'th root: 1.570796327
```
### Interesting nonlinear equation I want to solve
- $$
  f(x) = cos(x)ln(x) + sin(2x)
  \\
  f'(x) = \frac{cos(x)}{x} + 2cos(2x) - ln(x)sin(x)
  $$

<img src="https://github.com/llordly/MAT3008/blob/master/Homework%233/func4.png?raw=true" alt="func4" style="zoom:33%;" />

#### result
```
func4 in [0, 2]
1'th root: 0.4324731422
2'th root: 1.570796327
```
