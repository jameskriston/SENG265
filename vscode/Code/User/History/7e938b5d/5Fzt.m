
z= 1+1i;
x=linspace(-10,10,100);
f=(1./(z .*x +1));

fmagnitude = abs(f);
farg = angle(f);

figure;


subplot(2,1,1);
plot(x,fmagnitude,'Linewidth', 1);
grid on;
title ('Graph of |f(x)|');
xlabel('x');
ylabel('magnitude');

subplot(2,1,1);
plot(x,farg, 'Linewidth',1);
grid on;
title('arg of f(x)');
xlabel('x');
ylabel('phase in radians');

