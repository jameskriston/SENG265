import matplotlib.pyplot as plt

# Transformed points from y(t) = x(2t + 1)
rising_segment = [(-1.5, 0), (-1.5, 1), (-1.5, 2), (-1, 2), (-0.5, 2)]
falling_segment = [(-0.5, -2), (0, -1), (0.5, 0)]

# Separate into x and y for plotting
x_rising, y_rising = zip(*rising_segment)
x_falling, y_falling = zip(*falling_segment)
plt.figure(figsize=(8, 5))
plt.plot(x_rising, y_rising, color='blue', label='Rising segment')
plt.plot(x_falling, y_falling, color='red', label='Falling segment')

# Mark points
plt.scatter(x_rising, y_rising, color='blue')
plt.scatter(x_falling, y_falling, color='red')

# Axes and title
plt.title('Graph of y(t) = x(2t + 1)')
plt.xlabel('t')
plt.ylabel('y(t)')
plt.axhline(0, color='black', linewidth=0.5)
plt.axvline(0, color='black', linewidth=0.5)
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

