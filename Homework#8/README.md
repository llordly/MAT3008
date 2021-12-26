#  <center>Homework#8</center>

**컴퓨터소프트웨어학부 2017029589 류지범**

##  #0 Environment & execute

- `python3.9`로 작성했다.
- 필요한 묘듈은 `numpy`와 `pillow`이다.
- n과 m을 공백을 기준으로 입력하면 result.jpg가 생성된다.
  - python3 main.py n m

## #1 Bilinear Interpolation

- `Bilinear Interpolation`을 그림으로 표현하면 다음과 같다.

<img src="https://github.com/llordly/MAT3008/blob/master/Homework%238/bi_linear.jpeg?raw=true" alt="bi_linear" style="zoom:40%;" />

- 원본 크기와 resize된 크기의 비율을 구해서 resize될 이미지의 좌표를 구한다.

- 구한 좌표를 내림하여 정수로 만들어준 것이 `[x, y]`가 되며, `(x', y')`과의 차이가 dx, `dy`가 된다.

- 각각에 해당하는 면적의 색을 합친 것이 해당 픽셀을 표현하는 색이 된다.

  - 이를 식으로 나타내면 다음과 같다.

  - ```python
    dx * dy * [x + 1, y + 1] + (1 - dx) * dy * [x, y + 1] + dx * (1 - dy) * [x + 1, y] + (1 - dx) * (1 - dy) * [x, y]
    ```

## #2 Result

- 원본 사진 (1343 * 1080, 2021 Mr.O Classic Physique Champ)
  - <img src="https://github.com/llordly/MAT3008/blob/master/Homework%238/chris.jpg?raw=true" alt="chris" style="zoom:40%;" />
- 1920 * 1080으로 만들기 위해 n에 1080, m에 1920을 준 결과는 다음과 같다.
  - <img src="https://github.com/llordly/MAT3008/blob/master/Homework%238/result.jpg?raw=true" alt="result" style="zoom:30%;" />

- 100 * 100으로 만들기 위해 n에 100, m에 100을 준 결과는 다음과 같다.
  - <img src="https://github.com/llordly/MAT3008/blob/master/Homework%238/result100.jpg?raw=true" alt="result" style="zoom:100%;" />
