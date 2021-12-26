# <center>Homework#6</center>

**컴퓨터소프트웨어학부 2017029589 류지범**



## #0 Intro

- Random Number Generation은 <A href = "https://hconnect.hanyang.ac.kr/2021_MAT3008_11255/2021_mat3008_2017029589/-/blob/master/Homework%236/main.cpp" target = "self" > main.cpp </A>에서 했다.
- histogram은 <A href = "https://hconnect.hanyang.ac.kr/2021_MAT3008_11255/2021_mat3008_2017029589/-/blob/master/Homework%236/draw_histogram.py" target = "self" > draw_histogram.py </A>로 그렸다.

- Random Number Generation의 결과는 uniform_distribution_n.txt, gauss_distribution_n.txt (n은 sample의 수) 로 저장되도록 했고, python에서 이 파일들을 읽어서 histogram을 그리도록 했다.

## #1 Uniform Distribution

- `NR`의 `ran1` function을 사용해서 Random Number Generate를 했다.

- Uniform Distribution이므로 다음의 식이 성립한다.
  $$
  F(x) = \frac{x - a}{b - a}
  $$

  $$
  x = F(x) * (b - a) + a
  $$

- 그래서 다음과 같이 작성했다.

```c++
for (int j = 0; j < sample; ++j) {
            uni << ran1(idum) * (b - a) + a << "\n";
        }
```

### result

<img src="https://hconnect.hanyang.ac.kr/2021_MAT3008_11255/2021_mat3008_2017029589/-/raw/master/Homework%236/uniform_distribution.png" style="zoom:70%;" />



## #2 Gauss Distribution(Standard normal Distribution)

- `NR`의 `gasdev` function을 사용해서 Random Number Generate를 했다.

- Standard normal Distribution이므로 다음의 식이 성립한다.
  $$
  Z = \frac{X - \mu}{\sigma}
  $$

  $$
  X = Z\sigma + \mu
  $$

- 그래서 다음과 같이 작성했다.

```c++
for (int j = 0; j <sample; ++j) {
            gas << gasdev(idum) * s + m << "\n";
        }
```

### result

<img src="https://hconnect.hanyang.ac.kr/2021_MAT3008_11255/2021_mat3008_2017029589/-/raw/master/Homework%236/gauss_distribution.png" style="zoom:70%;" />



## #3 Conclusion

- 두 결과를 함께 나타내면 다음과 같다.<img src="https://hconnect.hanyang.ac.kr/2021_MAT3008_11255/2021_mat3008_2017029589/-/raw/master/Homework%236/distribution.png" style="zoom:80%;" />