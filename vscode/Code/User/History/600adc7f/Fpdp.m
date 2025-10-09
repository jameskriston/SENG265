t = linspace(-1, 4, 1000);  % Covering range of interest

% Define x(tau)
x = @(tau) (tau >= 0 & tau < 1) .* tau + ...
           (tau >= 1 & tau < 2) .* (2 - tau);

% Define h(tau)
h = @(tau) (tau > -1 & tau < 0) .* (tau + 1) + ...
           (tau > 0 & tau < 1) .* (tau - 1);

% Output y(t) = x * h
y = zeros(size(t));

% Perform convolution numerically
for i = 1:length(t)
    ti = t(i);
    integrand = @(tau) x(tau) .* h(ti - tau);
    y(i) = integral(integrand, -10, 10);  % Use wide enough limits
end

% Plot the result
figure;
plot(t, y, 'LineWidth', 2);
xlabel('t');
ylabel('y(t) = (x * h)(t)');
title('Convolution of x(t) and h(t)');
grid on;