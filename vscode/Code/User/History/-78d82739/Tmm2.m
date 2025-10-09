disp('Testing temperature conversion table on values -50C to +50C with steps of 10');
    temperature();

disp('Testing basic unitstep function on values: -1, 0, 1, 10');

disp(unitstepfunction(-1));
disp(unitstepfunction(0));
disp(unitstepfunction(1));
disp(unitstepfunction(10));

disp('Testing unoptimized unitstep on the array [100,-5,-2,0,1,5,100]');

disp(badunitstep([100,-5,-2,0,1,5,100]));
disp('Testing optimized (2 line) unitstep on the array [100,-5,-2,0,1,5,100]');

disp(betterunitstep([100,-5,-2,0,1,5,100]));

A = -2 + 4 * rand(3, 3);
disp('This is 3x3 matrix A of numbers between -2 and +2');
disp(A);
disp('Outputting function x0 3.201a) f(t) on matrix A');
disp(funcx0(A));
disp('Outputting function x1 3.201f f(t) on matrix A' );
disp(funcx1(A));

function value = unitstepfunction(t) % a not so efficient way of programming a unit step function
   value = (t>=0);
end

function array0 = badunitstep(t)
    for i = 1:length(t)
        array0(i) = (t(i)>=0);
    end
end


function array1 = betterunitstep(t)
    array1 = (t>=0);
end

function x0 = funcx0(t) 

    x0 = (((t.^2)-1)./((t.^2)+1)).*exp(-(abs(t/10))).*cos(t/(2*pi));
  
end

function x1 = funcx1(t)
   x1 = zeros(size(t));
   x1(t<0) = exp(t(t<0));
   x1(t>=0 & t<1) = 1;
   x1(t>=1) = exp(1-t(t>=1));
  
end

 function temperature() 
    celsius = -50;10;50;  
    farenheit = celsius*(9/5)+32;
    kelvin = celsius + 273.15;

    temptable = table(celsius',farenheit',kelvin', 'VariableNames',{'Celsius','Farenheit','Kelvin'});
    disp(temptable);
 end